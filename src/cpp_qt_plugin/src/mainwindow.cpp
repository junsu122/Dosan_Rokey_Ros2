#include "./qt_gui.h"
#include <QApplication>
#include <QClipboard>
#include <QString>
#include <QPainter>
#include <QTimer>
#undef slots                // Qt과 매크로 slots 비활성화
#include <pybind11/embed.h>
#define slots Q_SLOTS       // Qt의 slots 매크로를 다시 정의
#include <algorithm>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>

namespace py = pybind11;
py::scoped_interpreter guard{};

using namespace std;

#define ACC 60
#define VEL 60
#define ON 1
#define OFF 0


class PlotWidget : public QWidget {

public:
    explicit PlotWidget(QWidget* parent = nullptr)
        : QWidget(parent), timeStep(0) {
        data.fill(0.0);
    }

    void addDataPoint(const std::array<double, 6>& newData) {
        data = newData;
        timeStep++;
        update();
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        Q_UNUSED(event);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        painter.fillRect(this->rect(), Qt::white);

        painter.setPen(Qt::black);
        int plotWidth = 300;
        painter.drawLine(40, height() - 40, 40 + plotWidth, height() - 40);
        painter.drawLine(40, height() - 40, 40, 20);

        int originX = 40;
        int originY = height() - 40;
        QStringList labels = {"joint1", "joint2", "joint3", "joint4", "joint5", "joint6"};
        int numLabels = labels.size();
        for (int i = 0; i < numLabels; ++i) {
            int x = originX + static_cast<int>((plotWidth - 20) * i / (numLabels - 1));
            int y = originY + 20;
            painter.drawText(QPointF(x - 10, y), labels[i]);
        }

        painter.setPen(Qt::blue);

        for (size_t i = 0; i < data.size(); ++i) {
            int x = 40 + static_cast<int>((plotWidth - 20) * i / (data.size() - 1));
            int y = height() - 40 - static_cast<int>((height() - 60) * data[i] / 100.0);
            painter.drawEllipse(QPoint(x, y), 5, 5);
            if (i > 0) {
                int prevX = 40 + static_cast<int>((plotWidth - 20) * (i - 1) / (data.size() - 1));
                int prevY = height() - 40 - static_cast<int>((height() - 60) * data[i - 1] / 100.0);
                painter.drawLine(prevX, prevY, x, y);
            }
        }
    }

private:
    std::array<double, 6> data;
    int timeStep;
};


class Q_DECL_HIDDEN MainWindow : public QWidget {
    
public:
    explicit MainWindow(rclcpp::Node::SharedPtr node, QWidget *parent = nullptr)
        : QWidget(parent), node_(node) {
        ui.setupUi(this);

        QVBoxLayout* plotLayout = new QVBoxLayout(ui.plotScrollArea->widget());
        plotLayout->setAlignment(Qt::AlignTop);

        plotWidget = new PlotWidget(this);
        plotWidget->setMinimumSize(300, 300);
        plotLayout->addWidget(plotWidget);

        //plotWidget2 = new PlotWidget(this);
        //plotWidget2->setMinimumSize(300, 300);
        //plotLayout->addWidget(plotWidget2);

        ui.plotScrollArea->setFixedSize(400, 300);
        //ui.scrollArea->widget()->setMinimumSize(780, 580);
        ui.plotScrollArea->widget()->setLayout(plotLayout);
        ui.plotScrollArea->setWidgetResizable(true);

        try {
            py::module dr_init = py::module::import("DR_init");
            py::module rclpy = py::module::import("rclpy");
            rclpy.attr("init")();
            string robot_id = "dsr01";
            string robot_model = "m0609";
            py::object dsr_node = rclpy.attr("create_node")(
                "dsr_rokey_basic_py",
                py::arg("namespace") = robot_id);

            dr_init.attr("__dsr__id") = robot_id;
            dr_init.attr("__dsr__model") = robot_model;
            dr_init.attr("__dsr__node") = dsr_node;
            cout << "Python 모듈 DR_init 설정 완료" << endl;
        } catch (const exception &e) {
            cerr << "main.cpp Python 호출 중 예외 발생: " << e.what() << endl;
            rclcpp::shutdown();
        }

        try {
            py::module dsr_robot2 = py::module::import("DSR_ROBOT2");
            amovej = dsr_robot2.attr("amovej");
            amovel = dsr_robot2.attr("amovel");
            get_current_posx = dsr_robot2.attr("get_current_posx");
            get_current_posj = dsr_robot2.attr("get_current_posj");
            set_digital_output = dsr_robot2.attr("set_digital_output");
            get_digital_input = dsr_robot2.attr("get_digital_input");
            wait = dsr_robot2.attr("wait");
            DR_BASE = dsr_robot2.attr("DR_BASE");
            cout << "Python 모듈 DSR_ROBOT2 설정 완료" << endl;
        } catch (const py::error_already_set& e) {
            cerr << "Python 호출 중 예외 발생: " << e.what() << endl;
        }

        initializeArrays();

        connect(ui.moveJoint, &QPushButton::clicked, this, &MainWindow::onMoveJoint);
        connect(ui.moveCartesian, &QPushButton::clicked, this, &MainWindow::onMoveCartesian);
        connect(ui.grip, &QPushButton::clicked, this, &MainWindow::onGrip);
        connect(ui.release, &QPushButton::clicked, this, &MainWindow::onRelease);
        connect(ui.reset, &QPushButton::clicked, this, &MainWindow::onReset);
        connect(ui.copy, &QPushButton::clicked, this, &MainWindow::onCopy);
        connect(ui.velSlider, &QSlider::valueChanged, this, &MainWindow::updateVel);
        connect(ui.accSlider, &QSlider::valueChanged, this, &MainWindow::updateAcc);

        for (int i = 0; i < 6; ++i) {
            connect(incrementJoint[i], &QPushButton::clicked, this, [this, i]() {
                modifyJointValue(i, 1.0);
            });
            connect(decrementJoint[i], &QPushButton::clicked, this, [this, i]() {
                modifyJointValue(i, -1.0);
            });
        }
        for (int i = 0; i < 6; ++i) {
            connect(incrementCartesian[i], &QPushButton::clicked, this, [this, i]() {
                modifyCartesianValue(i, 1.0);
            });
        connect(decrementCartesian[i], &QPushButton::clicked, this, [this, i]() {
                modifyCartesianValue(i, -1.0);
            });
        }

        subscription_joint = node_->create_subscription<std_msgs::msg::Float64MultiArray>(
            "/dsr01/msg/joint_state", 10,
            [this](const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
                array<double, 6> newData = {0};
                size_t dataCount = std::min(msg->data.size(), static_cast<size_t>(6));
                for (size_t i = 0; i < dataCount; ++i) {
                    newData[i] = msg->data[i];
                }
                plotWidget->addDataPoint(newData);
                updateJointStates(newData);

            });
        subscription_cartesian = node_->create_subscription<std_msgs::msg::Float64MultiArray>(
            "/dsr01/msg/current_posx", 10,
            [this](const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
                updateCartesianStates(msg);

            });
        initSlider();
        clearLCD();
    }


private slots:
    void updateVel(int value) {
        vel = value;
        ui.lcdVel->display(vel);
    }

    void updateAcc(int value) {
        acc = value;
        ui.lcdAcc->display(acc);
    }

    void onGrip() {
        set_digital_output(1, ON);
        set_digital_output(2, OFF);
        waitDigitalInput(1);
    }

    void onRelease() {
        set_digital_output(2, ON);
        set_digital_output(1, OFF);
        waitDigitalInput(2);
    }

    void onReset() {
        moveJoint(this->initJointPosArr, vel, acc);
        clearValues();
        clearLCD();
        initSlider();
    }

    void onCopy() {
        QString clipboardData;

        for (int i = 0; i < 6; i++) {
            clipboardData += QString("j%1: ").arg(i + 1) + jointStatus[i]->text();
            clipboardData += (i < 5) ? ", " : "\n";
        }

        clipboardData += "x: " + cartesianStatus[0]->text() + ", ";
        clipboardData += "y: " + cartesianStatus[1]->text() + ", ";
        clipboardData += "z: " + cartesianStatus[2]->text() + ", ";
        clipboardData += "Rx: " + cartesianStatus[3]->text() + ", ";
        clipboardData += "Ry: " + cartesianStatus[4]->text() + ", ";
        clipboardData += "Rz: " + cartesianStatus[5]->text() + "\n";

        // Copy to clipboard
        QClipboard *clipboard = QGuiApplication::clipboard();
        clipboard->setText(clipboardData);
    }

    void onMoveJoint() {
        array<double, 6> jointArr;
        for (int i = 0; i < 6; i++) {
            if (jointValue[i] == nullptr) {
                jointArr[i] = jointStatus[i]->text().toDouble();
            } else {
                jointArr[i] = jointValue[i]->text().toDouble();
            }
        }
        moveJoint(jointArr, vel, acc);
    }

    void onMoveCartesian() {
        array<double, 6> cartesianArr;
        for (int i = 0; i < 6; i++) {
            if (cartesianValue[i] == nullptr) {
                cartesianArr[i] = cartesianStatus[i]->text().toDouble();
            } else {
                cartesianArr[i] = cartesianValue[i]->text().toDouble();
            }
        }
        moveLinear(cartesianArr, vel, acc);
    }

    void modifyJointValue(int idx, double step) {
        double currentValue = jointStatus[idx]->text().toDouble();
        double newValue = currentValue + step;

        jointStatus[idx]->setText(QString::number(newValue, 'f', 2));

        std::array<double, 6> jointPositions;
        for (int i = 0; i < 6; ++i) {
            jointPositions[i] = jointStatus[i]->text().toDouble();
        }
        moveJoint(jointPositions, vel, acc);
    }

    void modifyCartesianValue(int idx, double step) {
        double currentValue = cartesianStatus[idx]->text().toDouble();
        double newValue = currentValue + step;

        cartesianStatus[idx]->setText(QString::number(newValue, 'f', 2));

        std::array<double, 6> cartesianPositions;
        for (int i = 0; i < 6; ++i) {
            cartesianPositions[i] = cartesianStatus[i]->text().toDouble();
        }
        moveLinear(cartesianPositions, vel, acc);
    }

private:
    py::object amovej;
    py::object amovel;
    py::object get_current_posx;
    py::object get_current_posj;
    py::object set_digital_output;
    py::object get_digital_input;
    py::object wait;
    py::object DR_BASE;
    std::mutex mutex_;
    int vel = VEL;
    int acc = ACC;
    array<double, 6> initJointPosArr = {0, 0, 0, 0, 0, 0};

    void initSlider() {
        ui.velSlider->setValue(VEL);
        ui.accSlider->setValue(ACC);
    }

    void clearLCD() {
        vel = VEL;
        acc = ACC;
        ui.lcdVel->display(vel);
        ui.lcdAcc->display(acc);
    }

    void clearValues() {
        for (int i = 0; i < 6; i++) {
            jointValue[i]->setText("0.0");
            cartesianValue[i]->setText("0.0");
        }
    }

    void moveJoint(array<double, 6> jointArr, double vel = VEL, double acc = ACC) {
        py::list movej_list;
        for (int i = 0; i < 6; i++) {
            movej_list.append(jointArr[i]);
        }
        this->amovej(movej_list,
              py::arg("vel") = vel,
              py::arg("acc") = acc);
    }

    void moveLinear(array<double, 6> cartesianArr, double vel = VEL, double acc = ACC, py::object ref = py::none()) {
        if (ref.is_none()) {
            ref = DR_BASE;
        }
        py::list movel_list;
        for (const auto& position : cartesianArr) {
            movel_list.append(position);
        }
        amovel(movel_list,
            py::arg("vel") = vel,
            py::arg("acc") = acc,
            py::arg("ref") = ref);
    }

    array<double, 6> getCartesianValues() {
        py::tuple tmp = get_current_posx();
        cout << "1" << endl;
        py::tuple posx_list = tmp[0];
        cout << "2" << endl;
        std::array<double, 6> cartesian_values;
        for (size_t i = 0; i < 6; ++i) {
            cartesian_values[i] = posx_list[i].cast<double>();
        }
        return cartesian_values;
    }

    array<double, 6> getJointValues() {
        py::list posj_list = get_current_posj();
        std::array<double, 6> joint_values;
        for (size_t i = 0; i < 6; ++i) {
            joint_values[i] = posj_list[i].cast<double>();
        }
        return joint_values;
    }

    void waitDigitalInput(int sigNum) {
        while (!get_digital_input(sigNum)) {
            wait(0.5);
        }
    }


    // Initialize arrays
    void initializeArrays() {
        // Buttons
        incrementJoint[0] = ui.incrementJoint1;
        incrementJoint[1] = ui.incrementJoint2;
        incrementJoint[2] = ui.incrementJoint3;
        incrementJoint[3] = ui.incrementJoint4;
        incrementJoint[4] = ui.incrementJoint5;
        incrementJoint[5] = ui.incrementJoint6;

        decrementJoint[0] = ui.decrementJoint1;
        decrementJoint[1] = ui.decrementJoint2;
        decrementJoint[2] = ui.decrementJoint3;
        decrementJoint[3] = ui.decrementJoint4;
        decrementJoint[4] = ui.decrementJoint5;
        decrementJoint[5] = ui.decrementJoint6;

        incrementCartesian[0] = ui.incrementCartesianX;
        incrementCartesian[1] = ui.incrementCartesianY;
        incrementCartesian[2] = ui.incrementCartesianZ;
        incrementCartesian[3] = ui.incrementCartesianRx;
        incrementCartesian[4] = ui.incrementCartesianRy;
        incrementCartesian[5] = ui.incrementCartesianRz;

        decrementCartesian[0] = ui.decrementCartesianX;
        decrementCartesian[1] = ui.decrementCartesianY;
        decrementCartesian[2] = ui.decrementCartesianZ;
        decrementCartesian[3] = ui.decrementCartesianRx;
        decrementCartesian[4] = ui.decrementCartesianRy;
        decrementCartesian[5] = ui.decrementCartesianRz;

        // Labels
        jointLabel[0] = ui.jointLabel1;
        jointLabel[1] = ui.jointLabel2;
        jointLabel[2] = ui.jointLabel3;
        jointLabel[3] = ui.jointLabel4;
        jointLabel[4] = ui.jointLabel5;
        jointLabel[5] = ui.jointLabel6;

        cartesianLabel[0] = ui.cartesianLabelX;
        cartesianLabel[1] = ui.cartesianLabelY;
        cartesianLabel[2] = ui.cartesianLabelZ;
        cartesianLabel[3] = ui.cartesianLabelRx;
        cartesianLabel[4] = ui.cartesianLabelRy;
        cartesianLabel[5] = ui.cartesianLabelRz;

        // LineEdits
        jointStatus[0] = ui.jointstatus1;
        jointStatus[1] = ui.jointstatus2;
        jointStatus[2] = ui.jointstatus3;
        jointStatus[3] = ui.jointstatus4;
        jointStatus[4] = ui.jointstatus5;
        jointStatus[5] = ui.jointstatus6;

        jointValue[0] = ui.jointvalue1;
        jointValue[1] = ui.jointvalue2;
        jointValue[2] = ui.jointvalue3;
        jointValue[3] = ui.jointvalue4;
        jointValue[4] = ui.jointvalue5;
        jointValue[5] = ui.jointvalue6;

        cartesianStatus[0] = ui.cartesianstatusX;
        cartesianStatus[1] = ui.cartesianstatusY;
        cartesianStatus[2] = ui.cartesianstatusZ;
        cartesianStatus[3] = ui.cartesianstatusRx;
        cartesianStatus[4] = ui.cartesianstatusRy;
        cartesianStatus[5] = ui.cartesianstatusRz;

        cartesianValue[0] = ui.cartesianvalueX;
        cartesianValue[1] = ui.cartesianvalueY;
        cartesianValue[2] = ui.cartesianvalueZ;
        cartesianValue[3] = ui.cartesianvalueRx;
        cartesianValue[4] = ui.cartesianvalueRy;
        cartesianValue[5] = ui.cartesianvalueRz;
    }

    void updateJointStates(const array<double, 6> jointData) {
        size_t jointCount = jointData.size();
        for (size_t i = 0; i < jointCount; ++i) {
            jointStatus[i]->setText(QString::number(jointData[i], 'f', 2));
        }
    }

    void updateCartesianStates(const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
        size_t cartesianCount = min(msg->data.size(), static_cast<size_t>(6));
        for (size_t i = 0; i < cartesianCount; ++i) {
            cartesianStatus[i]->setText(QString::number(msg->data[i], 'f', 2));
        }
    }

    PlotWidget* plotWidget;
    //PlotWidget* plotWidget2;
    Ui::MainWindow ui;
    rclcpp::Node::SharedPtr node_;
    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscription_joint;
    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr subscription_cartesian;

    QPushButton* incrementJoint[6];
    QPushButton* decrementJoint[6];
    QPushButton* incrementCartesian[6];
    QPushButton* decrementCartesian[6];
    QLabel* jointLabel[6];
    QLabel* cartesianLabel[6];
    QLineEdit* jointStatus[6];
    QLineEdit* jointValue[6];
    QLineEdit* cartesianStatus[6];
    QLineEdit* cartesianValue[6];
};
