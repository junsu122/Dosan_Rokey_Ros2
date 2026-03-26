/********************************************************************************
** Form generated from reading UI file 'qt_gui.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef QT_GUI_H
#define QT_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QGridLayout *labelGrid;
    QLabel *cartesianPositionLabel;
    QLabel *jointPositionLabel;
    QGridLayout *jointCartesianControlGrid;
    QLabel *jointLabelHeader;
    QLabel *statusLabelHeader;
    QLabel *valueLabelHeader;
    QLabel *jointLabel1;
    QLineEdit *jointstatus1;
    QLineEdit *jointvalue1;
    QPushButton *incrementJoint1;
    QPushButton *decrementJoint1;
    QLabel *jointLabel2;
    QLineEdit *jointstatus2;
    QLineEdit *jointvalue2;
    QPushButton *incrementJoint2;
    QPushButton *decrementJoint2;
    QLabel *jointLabel3;
    QLineEdit *jointstatus3;
    QLineEdit *jointvalue3;
    QPushButton *incrementJoint3;
    QPushButton *decrementJoint3;
    QLabel *jointLabel4;
    QLineEdit *jointstatus4;
    QLineEdit *jointvalue4;
    QPushButton *incrementJoint4;
    QPushButton *decrementJoint4;
    QLabel *jointLabel5;
    QLineEdit *jointstatus5;
    QLineEdit *jointvalue5;
    QPushButton *incrementJoint5;
    QPushButton *decrementJoint5;
    QLabel *jointLabel6;
    QLineEdit *jointstatus6;
    QLineEdit *jointvalue6;
    QPushButton *incrementJoint6;
    QPushButton *decrementJoint6;
    QLabel *cartesianLabelHeader;
    QLabel *cartesianstatusLabelHeader;
    QLabel *cartesianvalueLabelHeader;
    QLabel *cartesianLabelX;
    QLineEdit *cartesianstatusX;
    QLineEdit *cartesianvalueX;
    QPushButton *incrementCartesianX;
    QPushButton *decrementCartesianX;
    QLabel *cartesianLabelY;
    QLineEdit *cartesianstatusY;
    QLineEdit *cartesianvalueY;
    QPushButton *incrementCartesianY;
    QPushButton *decrementCartesianY;
    QLabel *cartesianLabelZ;
    QLineEdit *cartesianstatusZ;
    QLineEdit *cartesianvalueZ;
    QPushButton *incrementCartesianZ;
    QPushButton *decrementCartesianZ;
    QLabel *cartesianLabelRx;
    QLineEdit *cartesianstatusRx;
    QLineEdit *cartesianvalueRx;
    QPushButton *incrementCartesianRx;
    QPushButton *decrementCartesianRx;
    QLabel *cartesianLabelRy;
    QLineEdit *cartesianstatusRy;
    QLineEdit *cartesianvalueRy;
    QPushButton *incrementCartesianRy;
    QPushButton *decrementCartesianRy;
    QLabel *cartesianLabelRz;
    QLineEdit *cartesianstatusRz;
    QLineEdit *cartesianvalueRz;
    QPushButton *incrementCartesianRz;
    QPushButton *decrementCartesianRz;
    QLabel *labelJointIncrement;
    QLabel *labelCartesianIncrement;
    QLabel *labelJointDecrement;
    QLabel *labelCartesianDecrement;
    QHBoxLayout *controlCommandLayout;
    QLabel *controlLabel;
    QPushButton *moveJoint;
    QPushButton *moveCartesian;
    QPushButton *grip;
    QPushButton *release;
    QPushButton *reset;
    QPushButton *copy;
    QGridLayout *sliderGrid;
    QLCDNumber *lcdAcc;
    QHBoxLayout *velSliderHLayout;
    QLabel *velMinLabel;
    QSlider *velSlider;
    QLabel *velMaxLabel;
    QHBoxLayout *accSliderHLayout;
    QLabel *accMinLabel;
    QSlider *accSlider;
    QLabel *accMaxLabel;
    QLCDNumber *lcdVel;
    QLabel *labelAcc;
    QLabel *labelVel;
    QScrollArea *plotScrollArea;
    QWidget *scrollAreaWidgetContents;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(696, 400);
        horizontalLayout = new QHBoxLayout(MainWindow);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labelGrid = new QGridLayout();
        labelGrid->setObjectName(QString::fromUtf8("labelGrid"));
        labelGrid->setSizeConstraint(QLayout::SetFixedSize);
        labelGrid->setContentsMargins(1, 1, 1, 1);
        cartesianPositionLabel = new QLabel(MainWindow);
        cartesianPositionLabel->setObjectName(QString::fromUtf8("cartesianPositionLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cartesianPositionLabel->sizePolicy().hasHeightForWidth());
        cartesianPositionLabel->setSizePolicy(sizePolicy);
        cartesianPositionLabel->setAlignment(Qt::AlignCenter);

        labelGrid->addWidget(cartesianPositionLabel, 1, 5, 1, 1);

        jointPositionLabel = new QLabel(MainWindow);
        jointPositionLabel->setObjectName(QString::fromUtf8("jointPositionLabel"));
        sizePolicy.setHeightForWidth(jointPositionLabel->sizePolicy().hasHeightForWidth());
        jointPositionLabel->setSizePolicy(sizePolicy);
        jointPositionLabel->setAlignment(Qt::AlignCenter);

        labelGrid->addWidget(jointPositionLabel, 1, 0, 1, 1);


        verticalLayout->addLayout(labelGrid);

        jointCartesianControlGrid = new QGridLayout();
        jointCartesianControlGrid->setObjectName(QString::fromUtf8("jointCartesianControlGrid"));
        jointCartesianControlGrid->setSizeConstraint(QLayout::SetFixedSize);
        jointCartesianControlGrid->setContentsMargins(1, 1, 1, 1);
        jointLabelHeader = new QLabel(MainWindow);
        jointLabelHeader->setObjectName(QString::fromUtf8("jointLabelHeader"));
        jointLabelHeader->setAlignment(Qt::AlignCenter);

        jointCartesianControlGrid->addWidget(jointLabelHeader, 1, 0, 1, 1);

        statusLabelHeader = new QLabel(MainWindow);
        statusLabelHeader->setObjectName(QString::fromUtf8("statusLabelHeader"));
        statusLabelHeader->setAlignment(Qt::AlignCenter);

        jointCartesianControlGrid->addWidget(statusLabelHeader, 1, 1, 1, 1);

        valueLabelHeader = new QLabel(MainWindow);
        valueLabelHeader->setObjectName(QString::fromUtf8("valueLabelHeader"));
        valueLabelHeader->setAlignment(Qt::AlignCenter);

        jointCartesianControlGrid->addWidget(valueLabelHeader, 1, 2, 1, 1);

        jointLabel1 = new QLabel(MainWindow);
        jointLabel1->setObjectName(QString::fromUtf8("jointLabel1"));
        jointLabel1->setAlignment(Qt::AlignCenter);
        jointLabel1->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(jointLabel1, 2, 0, 1, 1);

        jointstatus1 = new QLineEdit(MainWindow);
        jointstatus1->setObjectName(QString::fromUtf8("jointstatus1"));
        jointstatus1->setReadOnly(true);
        jointstatus1->setProperty("fixedWidth", QVariant(80));

        jointCartesianControlGrid->addWidget(jointstatus1, 2, 1, 1, 1);

        jointvalue1 = new QLineEdit(MainWindow);
        jointvalue1->setObjectName(QString::fromUtf8("jointvalue1"));
        jointvalue1->setProperty("fixedWidth", QVariant(80));

        jointCartesianControlGrid->addWidget(jointvalue1, 2, 2, 1, 1);

        incrementJoint1 = new QPushButton(MainWindow);
        incrementJoint1->setObjectName(QString::fromUtf8("incrementJoint1"));
        incrementJoint1->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(incrementJoint1, 2, 3, 1, 1);

        decrementJoint1 = new QPushButton(MainWindow);
        decrementJoint1->setObjectName(QString::fromUtf8("decrementJoint1"));
        decrementJoint1->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(decrementJoint1, 2, 4, 1, 1);

        jointLabel2 = new QLabel(MainWindow);
        jointLabel2->setObjectName(QString::fromUtf8("jointLabel2"));
        jointLabel2->setAlignment(Qt::AlignCenter);

        jointCartesianControlGrid->addWidget(jointLabel2, 3, 0, 1, 1);

        jointstatus2 = new QLineEdit(MainWindow);
        jointstatus2->setObjectName(QString::fromUtf8("jointstatus2"));
        jointstatus2->setReadOnly(true);
        jointstatus2->setProperty("fixedWidth", QVariant(80));

        jointCartesianControlGrid->addWidget(jointstatus2, 3, 1, 1, 1);

        jointvalue2 = new QLineEdit(MainWindow);
        jointvalue2->setObjectName(QString::fromUtf8("jointvalue2"));
        jointvalue2->setProperty("fixedWidth", QVariant(80));

        jointCartesianControlGrid->addWidget(jointvalue2, 3, 2, 1, 1);

        incrementJoint2 = new QPushButton(MainWindow);
        incrementJoint2->setObjectName(QString::fromUtf8("incrementJoint2"));
        incrementJoint2->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(incrementJoint2, 3, 3, 1, 1);

        decrementJoint2 = new QPushButton(MainWindow);
        decrementJoint2->setObjectName(QString::fromUtf8("decrementJoint2"));
        decrementJoint2->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(decrementJoint2, 3, 4, 1, 1);

        jointLabel3 = new QLabel(MainWindow);
        jointLabel3->setObjectName(QString::fromUtf8("jointLabel3"));
        jointLabel3->setAlignment(Qt::AlignCenter);

        jointCartesianControlGrid->addWidget(jointLabel3, 4, 0, 1, 1);

        jointstatus3 = new QLineEdit(MainWindow);
        jointstatus3->setObjectName(QString::fromUtf8("jointstatus3"));
        jointstatus3->setReadOnly(true);
        jointstatus3->setProperty("fixedWidth", QVariant(80));

        jointCartesianControlGrid->addWidget(jointstatus3, 4, 1, 1, 1);

        jointvalue3 = new QLineEdit(MainWindow);
        jointvalue3->setObjectName(QString::fromUtf8("jointvalue3"));
        jointvalue3->setProperty("fixedWidth", QVariant(80));

        jointCartesianControlGrid->addWidget(jointvalue3, 4, 2, 1, 1);

        incrementJoint3 = new QPushButton(MainWindow);
        incrementJoint3->setObjectName(QString::fromUtf8("incrementJoint3"));
        incrementJoint3->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(incrementJoint3, 4, 3, 1, 1);

        decrementJoint3 = new QPushButton(MainWindow);
        decrementJoint3->setObjectName(QString::fromUtf8("decrementJoint3"));
        decrementJoint3->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(decrementJoint3, 4, 4, 1, 1);

        jointLabel4 = new QLabel(MainWindow);
        jointLabel4->setObjectName(QString::fromUtf8("jointLabel4"));
        jointLabel4->setAlignment(Qt::AlignCenter);
        jointLabel4->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(jointLabel4, 5, 0, 1, 1);

        jointstatus4 = new QLineEdit(MainWindow);
        jointstatus4->setObjectName(QString::fromUtf8("jointstatus4"));
        jointstatus4->setReadOnly(true);
        jointstatus4->setProperty("fixedWidth", QVariant(80));

        jointCartesianControlGrid->addWidget(jointstatus4, 5, 1, 1, 1);

        jointvalue4 = new QLineEdit(MainWindow);
        jointvalue4->setObjectName(QString::fromUtf8("jointvalue4"));
        jointvalue4->setProperty("fixedWidth", QVariant(80));

        jointCartesianControlGrid->addWidget(jointvalue4, 5, 2, 1, 1);

        incrementJoint4 = new QPushButton(MainWindow);
        incrementJoint4->setObjectName(QString::fromUtf8("incrementJoint4"));
        incrementJoint4->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(incrementJoint4, 5, 3, 1, 1);

        decrementJoint4 = new QPushButton(MainWindow);
        decrementJoint4->setObjectName(QString::fromUtf8("decrementJoint4"));
        decrementJoint4->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(decrementJoint4, 5, 4, 1, 1);

        jointLabel5 = new QLabel(MainWindow);
        jointLabel5->setObjectName(QString::fromUtf8("jointLabel5"));
        jointLabel5->setAlignment(Qt::AlignCenter);
        jointLabel5->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(jointLabel5, 6, 0, 1, 1);

        jointstatus5 = new QLineEdit(MainWindow);
        jointstatus5->setObjectName(QString::fromUtf8("jointstatus5"));
        jointstatus5->setReadOnly(true);
        jointstatus5->setProperty("fixedWidth", QVariant(80));

        jointCartesianControlGrid->addWidget(jointstatus5, 6, 1, 1, 1);

        jointvalue5 = new QLineEdit(MainWindow);
        jointvalue5->setObjectName(QString::fromUtf8("jointvalue5"));
        jointvalue5->setProperty("fixedWidth", QVariant(80));

        jointCartesianControlGrid->addWidget(jointvalue5, 6, 2, 1, 1);

        incrementJoint5 = new QPushButton(MainWindow);
        incrementJoint5->setObjectName(QString::fromUtf8("incrementJoint5"));
        incrementJoint5->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(incrementJoint5, 6, 3, 1, 1);

        decrementJoint5 = new QPushButton(MainWindow);
        decrementJoint5->setObjectName(QString::fromUtf8("decrementJoint5"));
        decrementJoint5->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(decrementJoint5, 6, 4, 1, 1);

        jointLabel6 = new QLabel(MainWindow);
        jointLabel6->setObjectName(QString::fromUtf8("jointLabel6"));
        jointLabel6->setAlignment(Qt::AlignCenter);
        jointLabel6->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(jointLabel6, 7, 0, 1, 1);

        jointstatus6 = new QLineEdit(MainWindow);
        jointstatus6->setObjectName(QString::fromUtf8("jointstatus6"));
        jointstatus6->setReadOnly(true);
        jointstatus6->setProperty("fixedWidth", QVariant(80));

        jointCartesianControlGrid->addWidget(jointstatus6, 7, 1, 1, 1);

        jointvalue6 = new QLineEdit(MainWindow);
        jointvalue6->setObjectName(QString::fromUtf8("jointvalue6"));
        jointvalue6->setProperty("fixedWidth", QVariant(80));

        jointCartesianControlGrid->addWidget(jointvalue6, 7, 2, 1, 1);

        incrementJoint6 = new QPushButton(MainWindow);
        incrementJoint6->setObjectName(QString::fromUtf8("incrementJoint6"));
        incrementJoint6->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(incrementJoint6, 7, 3, 1, 1);

        decrementJoint6 = new QPushButton(MainWindow);
        decrementJoint6->setObjectName(QString::fromUtf8("decrementJoint6"));
        decrementJoint6->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(decrementJoint6, 7, 4, 1, 1);

        cartesianLabelHeader = new QLabel(MainWindow);
        cartesianLabelHeader->setObjectName(QString::fromUtf8("cartesianLabelHeader"));
        cartesianLabelHeader->setAlignment(Qt::AlignCenter);

        jointCartesianControlGrid->addWidget(cartesianLabelHeader, 1, 5, 1, 1);

        cartesianstatusLabelHeader = new QLabel(MainWindow);
        cartesianstatusLabelHeader->setObjectName(QString::fromUtf8("cartesianstatusLabelHeader"));
        cartesianstatusLabelHeader->setAlignment(Qt::AlignCenter);

        jointCartesianControlGrid->addWidget(cartesianstatusLabelHeader, 1, 6, 1, 1);

        cartesianvalueLabelHeader = new QLabel(MainWindow);
        cartesianvalueLabelHeader->setObjectName(QString::fromUtf8("cartesianvalueLabelHeader"));
        cartesianvalueLabelHeader->setAlignment(Qt::AlignCenter);

        jointCartesianControlGrid->addWidget(cartesianvalueLabelHeader, 1, 7, 1, 1);

        cartesianLabelX = new QLabel(MainWindow);
        cartesianLabelX->setObjectName(QString::fromUtf8("cartesianLabelX"));
        cartesianLabelX->setAlignment(Qt::AlignCenter);
        cartesianLabelX->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(cartesianLabelX, 2, 5, 1, 1);

        cartesianstatusX = new QLineEdit(MainWindow);
        cartesianstatusX->setObjectName(QString::fromUtf8("cartesianstatusX"));
        cartesianstatusX->setReadOnly(true);
        cartesianstatusX->setProperty("fixedWidth", QVariant(80));

        jointCartesianControlGrid->addWidget(cartesianstatusX, 2, 6, 1, 1);

        cartesianvalueX = new QLineEdit(MainWindow);
        cartesianvalueX->setObjectName(QString::fromUtf8("cartesianvalueX"));
        cartesianvalueX->setProperty("fixedWidth", QVariant(80));

        jointCartesianControlGrid->addWidget(cartesianvalueX, 2, 7, 1, 1);

        incrementCartesianX = new QPushButton(MainWindow);
        incrementCartesianX->setObjectName(QString::fromUtf8("incrementCartesianX"));
        incrementCartesianX->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(incrementCartesianX, 2, 8, 1, 1);

        decrementCartesianX = new QPushButton(MainWindow);
        decrementCartesianX->setObjectName(QString::fromUtf8("decrementCartesianX"));
        decrementCartesianX->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(decrementCartesianX, 2, 9, 1, 1);

        cartesianLabelY = new QLabel(MainWindow);
        cartesianLabelY->setObjectName(QString::fromUtf8("cartesianLabelY"));
        cartesianLabelY->setAlignment(Qt::AlignCenter);
        cartesianLabelY->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(cartesianLabelY, 3, 5, 1, 1);

        cartesianstatusY = new QLineEdit(MainWindow);
        cartesianstatusY->setObjectName(QString::fromUtf8("cartesianstatusY"));
        cartesianstatusY->setReadOnly(true);
        cartesianstatusY->setProperty("fixedWidth", QVariant(80));

        jointCartesianControlGrid->addWidget(cartesianstatusY, 3, 6, 1, 1);

        cartesianvalueY = new QLineEdit(MainWindow);
        cartesianvalueY->setObjectName(QString::fromUtf8("cartesianvalueY"));
        cartesianvalueY->setProperty("fixedWidth", QVariant(80));

        jointCartesianControlGrid->addWidget(cartesianvalueY, 3, 7, 1, 1);

        incrementCartesianY = new QPushButton(MainWindow);
        incrementCartesianY->setObjectName(QString::fromUtf8("incrementCartesianY"));
        incrementCartesianY->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(incrementCartesianY, 3, 8, 1, 1);

        decrementCartesianY = new QPushButton(MainWindow);
        decrementCartesianY->setObjectName(QString::fromUtf8("decrementCartesianY"));
        decrementCartesianY->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(decrementCartesianY, 3, 9, 1, 1);

        cartesianLabelZ = new QLabel(MainWindow);
        cartesianLabelZ->setObjectName(QString::fromUtf8("cartesianLabelZ"));
        cartesianLabelZ->setAlignment(Qt::AlignCenter);
        cartesianLabelZ->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(cartesianLabelZ, 4, 5, 1, 1);

        cartesianstatusZ = new QLineEdit(MainWindow);
        cartesianstatusZ->setObjectName(QString::fromUtf8("cartesianstatusZ"));
        cartesianstatusZ->setReadOnly(true);
        cartesianstatusZ->setProperty("fixedWidth", QVariant(80));

        jointCartesianControlGrid->addWidget(cartesianstatusZ, 4, 6, 1, 1);

        cartesianvalueZ = new QLineEdit(MainWindow);
        cartesianvalueZ->setObjectName(QString::fromUtf8("cartesianvalueZ"));
        cartesianvalueZ->setProperty("fixedWidth", QVariant(80));

        jointCartesianControlGrid->addWidget(cartesianvalueZ, 4, 7, 1, 1);

        incrementCartesianZ = new QPushButton(MainWindow);
        incrementCartesianZ->setObjectName(QString::fromUtf8("incrementCartesianZ"));
        incrementCartesianZ->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(incrementCartesianZ, 4, 8, 1, 1);

        decrementCartesianZ = new QPushButton(MainWindow);
        decrementCartesianZ->setObjectName(QString::fromUtf8("decrementCartesianZ"));
        decrementCartesianZ->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(decrementCartesianZ, 4, 9, 1, 1);

        cartesianLabelRx = new QLabel(MainWindow);
        cartesianLabelRx->setObjectName(QString::fromUtf8("cartesianLabelRx"));
        cartesianLabelRx->setAlignment(Qt::AlignCenter);
        cartesianLabelRx->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(cartesianLabelRx, 5, 5, 1, 1);

        cartesianstatusRx = new QLineEdit(MainWindow);
        cartesianstatusRx->setObjectName(QString::fromUtf8("cartesianstatusRx"));
        cartesianstatusRx->setReadOnly(true);
        cartesianstatusRx->setProperty("fixedWidth", QVariant(80));

        jointCartesianControlGrid->addWidget(cartesianstatusRx, 5, 6, 1, 1);

        cartesianvalueRx = new QLineEdit(MainWindow);
        cartesianvalueRx->setObjectName(QString::fromUtf8("cartesianvalueRx"));
        cartesianvalueRx->setProperty("fixedWidth", QVariant(80));

        jointCartesianControlGrid->addWidget(cartesianvalueRx, 5, 7, 1, 1);

        incrementCartesianRx = new QPushButton(MainWindow);
        incrementCartesianRx->setObjectName(QString::fromUtf8("incrementCartesianRx"));
        incrementCartesianRx->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(incrementCartesianRx, 5, 8, 1, 1);

        decrementCartesianRx = new QPushButton(MainWindow);
        decrementCartesianRx->setObjectName(QString::fromUtf8("decrementCartesianRx"));
        decrementCartesianRx->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(decrementCartesianRx, 5, 9, 1, 1);

        cartesianLabelRy = new QLabel(MainWindow);
        cartesianLabelRy->setObjectName(QString::fromUtf8("cartesianLabelRy"));
        cartesianLabelRy->setAlignment(Qt::AlignCenter);
        cartesianLabelRy->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(cartesianLabelRy, 6, 5, 1, 1);

        cartesianstatusRy = new QLineEdit(MainWindow);
        cartesianstatusRy->setObjectName(QString::fromUtf8("cartesianstatusRy"));
        cartesianstatusRy->setReadOnly(true);
        cartesianstatusRy->setProperty("fixedWidth", QVariant(80));

        jointCartesianControlGrid->addWidget(cartesianstatusRy, 6, 6, 1, 1);

        cartesianvalueRy = new QLineEdit(MainWindow);
        cartesianvalueRy->setObjectName(QString::fromUtf8("cartesianvalueRy"));
        cartesianvalueRy->setProperty("fixedWidth", QVariant(80));

        jointCartesianControlGrid->addWidget(cartesianvalueRy, 6, 7, 1, 1);

        incrementCartesianRy = new QPushButton(MainWindow);
        incrementCartesianRy->setObjectName(QString::fromUtf8("incrementCartesianRy"));
        incrementCartesianRy->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(incrementCartesianRy, 6, 8, 1, 1);

        decrementCartesianRy = new QPushButton(MainWindow);
        decrementCartesianRy->setObjectName(QString::fromUtf8("decrementCartesianRy"));
        decrementCartesianRy->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(decrementCartesianRy, 6, 9, 1, 1);

        cartesianLabelRz = new QLabel(MainWindow);
        cartesianLabelRz->setObjectName(QString::fromUtf8("cartesianLabelRz"));
        cartesianLabelRz->setAlignment(Qt::AlignCenter);
        cartesianLabelRz->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(cartesianLabelRz, 7, 5, 1, 1);

        cartesianstatusRz = new QLineEdit(MainWindow);
        cartesianstatusRz->setObjectName(QString::fromUtf8("cartesianstatusRz"));
        cartesianstatusRz->setReadOnly(true);
        cartesianstatusRz->setProperty("fixedWidth", QVariant(80));

        jointCartesianControlGrid->addWidget(cartesianstatusRz, 7, 6, 1, 1);

        cartesianvalueRz = new QLineEdit(MainWindow);
        cartesianvalueRz->setObjectName(QString::fromUtf8("cartesianvalueRz"));
        cartesianvalueRz->setProperty("fixedWidth", QVariant(80));

        jointCartesianControlGrid->addWidget(cartesianvalueRz, 7, 7, 1, 1);

        incrementCartesianRz = new QPushButton(MainWindow);
        incrementCartesianRz->setObjectName(QString::fromUtf8("incrementCartesianRz"));
        incrementCartesianRz->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(incrementCartesianRz, 7, 8, 1, 1);

        decrementCartesianRz = new QPushButton(MainWindow);
        decrementCartesianRz->setObjectName(QString::fromUtf8("decrementCartesianRz"));
        decrementCartesianRz->setProperty("fixedWidth", QVariant(35));

        jointCartesianControlGrid->addWidget(decrementCartesianRz, 7, 9, 1, 1);

        labelJointIncrement = new QLabel(MainWindow);
        labelJointIncrement->setObjectName(QString::fromUtf8("labelJointIncrement"));
        labelJointIncrement->setAlignment(Qt::AlignCenter);

        jointCartesianControlGrid->addWidget(labelJointIncrement, 1, 3, 1, 1);

        labelCartesianIncrement = new QLabel(MainWindow);
        labelCartesianIncrement->setObjectName(QString::fromUtf8("labelCartesianIncrement"));
        labelCartesianIncrement->setAlignment(Qt::AlignCenter);

        jointCartesianControlGrid->addWidget(labelCartesianIncrement, 1, 8, 1, 1);

        labelJointDecrement = new QLabel(MainWindow);
        labelJointDecrement->setObjectName(QString::fromUtf8("labelJointDecrement"));
        labelJointDecrement->setAlignment(Qt::AlignCenter);

        jointCartesianControlGrid->addWidget(labelJointDecrement, 1, 4, 1, 1);

        labelCartesianDecrement = new QLabel(MainWindow);
        labelCartesianDecrement->setObjectName(QString::fromUtf8("labelCartesianDecrement"));
        labelCartesianDecrement->setAlignment(Qt::AlignCenter);

        jointCartesianControlGrid->addWidget(labelCartesianDecrement, 1, 9, 1, 1);


        verticalLayout->addLayout(jointCartesianControlGrid);

        controlCommandLayout = new QHBoxLayout();
        controlCommandLayout->setObjectName(QString::fromUtf8("controlCommandLayout"));
        controlCommandLayout->setSizeConstraint(QLayout::SetFixedSize);
        controlCommandLayout->setContentsMargins(5, 20, 5, 5);
        controlLabel = new QLabel(MainWindow);
        controlLabel->setObjectName(QString::fromUtf8("controlLabel"));

        controlCommandLayout->addWidget(controlLabel);

        moveJoint = new QPushButton(MainWindow);
        moveJoint->setObjectName(QString::fromUtf8("moveJoint"));

        controlCommandLayout->addWidget(moveJoint);

        moveCartesian = new QPushButton(MainWindow);
        moveCartesian->setObjectName(QString::fromUtf8("moveCartesian"));

        controlCommandLayout->addWidget(moveCartesian);

        grip = new QPushButton(MainWindow);
        grip->setObjectName(QString::fromUtf8("grip"));

        controlCommandLayout->addWidget(grip);

        release = new QPushButton(MainWindow);
        release->setObjectName(QString::fromUtf8("release"));

        controlCommandLayout->addWidget(release);

        reset = new QPushButton(MainWindow);
        reset->setObjectName(QString::fromUtf8("reset"));

        controlCommandLayout->addWidget(reset);

        copy = new QPushButton(MainWindow);
        copy->setObjectName(QString::fromUtf8("copy"));

        controlCommandLayout->addWidget(copy);


        verticalLayout->addLayout(controlCommandLayout);

        sliderGrid = new QGridLayout();
        sliderGrid->setObjectName(QString::fromUtf8("sliderGrid"));
        sliderGrid->setSizeConstraint(QLayout::SetFixedSize);
        sliderGrid->setContentsMargins(1, 1, 1, 1);
        lcdAcc = new QLCDNumber(MainWindow);
        lcdAcc->setObjectName(QString::fromUtf8("lcdAcc"));
        lcdAcc->setFrameShape(QFrame::NoFrame);
        lcdAcc->setProperty("value", QVariant(10.000000000000000));

        sliderGrid->addWidget(lcdAcc, 0, 4, 1, 1);

        velSliderHLayout = new QHBoxLayout();
        velSliderHLayout->setObjectName(QString::fromUtf8("velSliderHLayout"));
        velSliderHLayout->setSizeConstraint(QLayout::SetFixedSize);
        velMinLabel = new QLabel(MainWindow);
        velMinLabel->setObjectName(QString::fromUtf8("velMinLabel"));

        velSliderHLayout->addWidget(velMinLabel);

        velSlider = new QSlider(MainWindow);
        velSlider->setObjectName(QString::fromUtf8("velSlider"));
        velSlider->setMinimum(10);
        velSlider->setMaximum(60);
        velSlider->setOrientation(Qt::Horizontal);

        velSliderHLayout->addWidget(velSlider);

        velMaxLabel = new QLabel(MainWindow);
        velMaxLabel->setObjectName(QString::fromUtf8("velMaxLabel"));

        velSliderHLayout->addWidget(velMaxLabel);


        sliderGrid->addLayout(velSliderHLayout, 0, 2, 1, 1);

        accSliderHLayout = new QHBoxLayout();
        accSliderHLayout->setObjectName(QString::fromUtf8("accSliderHLayout"));
        accSliderHLayout->setSizeConstraint(QLayout::SetFixedSize);
        accMinLabel = new QLabel(MainWindow);
        accMinLabel->setObjectName(QString::fromUtf8("accMinLabel"));

        accSliderHLayout->addWidget(accMinLabel);

        accSlider = new QSlider(MainWindow);
        accSlider->setObjectName(QString::fromUtf8("accSlider"));
        accSlider->setMinimum(10);
        accSlider->setMaximum(60);
        accSlider->setOrientation(Qt::Horizontal);

        accSliderHLayout->addWidget(accSlider);

        accMaxLabel = new QLabel(MainWindow);
        accMaxLabel->setObjectName(QString::fromUtf8("accMaxLabel"));

        accSliderHLayout->addWidget(accMaxLabel);


        sliderGrid->addLayout(accSliderHLayout, 0, 5, 1, 1);

        lcdVel = new QLCDNumber(MainWindow);
        lcdVel->setObjectName(QString::fromUtf8("lcdVel"));
        lcdVel->setFrameShape(QFrame::NoFrame);
        lcdVel->setProperty("value", QVariant(10.000000000000000));

        sliderGrid->addWidget(lcdVel, 0, 1, 1, 1);

        labelAcc = new QLabel(MainWindow);
        labelAcc->setObjectName(QString::fromUtf8("labelAcc"));
        labelAcc->setFrameShape(QFrame::Box);
        labelAcc->setAlignment(Qt::AlignCenter);
        labelAcc->setMargin(5);

        sliderGrid->addWidget(labelAcc, 0, 3, 1, 1);

        labelVel = new QLabel(MainWindow);
        labelVel->setObjectName(QString::fromUtf8("labelVel"));
        labelVel->setFrameShape(QFrame::Box);
        labelVel->setAlignment(Qt::AlignCenter);
        labelVel->setWordWrap(false);
        labelVel->setMargin(5);

        sliderGrid->addWidget(labelVel, 0, 0, 1, 1);


        verticalLayout->addLayout(sliderGrid);


        horizontalLayout->addLayout(verticalLayout);

        plotScrollArea = new QScrollArea(MainWindow);
        plotScrollArea->setObjectName(QString::fromUtf8("plotScrollArea"));
        plotScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        plotScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        plotScrollArea->setWidgetResizable(true);
        plotScrollArea->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 54, 380));
        plotScrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout->addWidget(plotScrollArea);


        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Rokey", nullptr));
        cartesianPositionLabel->setText(QCoreApplication::translate("MainWindow", "Cartesian Positions", nullptr));
        jointPositionLabel->setText(QCoreApplication::translate("MainWindow", "Joint Positions", nullptr));
        jointLabelHeader->setText(QCoreApplication::translate("MainWindow", "Joint", nullptr));
        statusLabelHeader->setText(QCoreApplication::translate("MainWindow", "status", nullptr));
        valueLabelHeader->setText(QCoreApplication::translate("MainWindow", "value", nullptr));
        jointLabel1->setText(QCoreApplication::translate("MainWindow", "J1", nullptr));
        incrementJoint1->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        decrementJoint1->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        jointLabel2->setText(QCoreApplication::translate("MainWindow", "J2", nullptr));
        incrementJoint2->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        decrementJoint2->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        jointLabel3->setText(QCoreApplication::translate("MainWindow", "J3", nullptr));
        incrementJoint3->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        decrementJoint3->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        jointLabel4->setText(QCoreApplication::translate("MainWindow", "J4", nullptr));
        incrementJoint4->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        decrementJoint4->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        jointLabel5->setText(QCoreApplication::translate("MainWindow", "J5", nullptr));
        incrementJoint5->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        decrementJoint5->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        jointLabel6->setText(QCoreApplication::translate("MainWindow", "J6", nullptr));
        incrementJoint6->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        decrementJoint6->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        cartesianLabelHeader->setText(QCoreApplication::translate("MainWindow", "Axis", nullptr));
        cartesianstatusLabelHeader->setText(QCoreApplication::translate("MainWindow", "status", nullptr));
        cartesianvalueLabelHeader->setText(QCoreApplication::translate("MainWindow", "value", nullptr));
        cartesianLabelX->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        incrementCartesianX->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        decrementCartesianX->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        cartesianLabelY->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        incrementCartesianY->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        decrementCartesianY->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        cartesianLabelZ->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        incrementCartesianZ->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        decrementCartesianZ->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        cartesianLabelRx->setText(QCoreApplication::translate("MainWindow", "Rx", nullptr));
        incrementCartesianRx->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        decrementCartesianRx->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        cartesianLabelRy->setText(QCoreApplication::translate("MainWindow", "Ry", nullptr));
        incrementCartesianRy->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        decrementCartesianRy->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        cartesianLabelRz->setText(QCoreApplication::translate("MainWindow", "Rz", nullptr));
        incrementCartesianRz->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        decrementCartesianRz->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        labelJointIncrement->setText(QCoreApplication::translate("MainWindow", "increment", nullptr));
        labelCartesianIncrement->setText(QCoreApplication::translate("MainWindow", "increment", nullptr));
        labelJointDecrement->setText(QCoreApplication::translate("MainWindow", "decrement", nullptr));
        labelCartesianDecrement->setText(QCoreApplication::translate("MainWindow", "decrement", nullptr));
        controlLabel->setText(QCoreApplication::translate("MainWindow", "Control Commands", nullptr));
        moveJoint->setText(QCoreApplication::translate("MainWindow", "Move_J", nullptr));
        moveCartesian->setText(QCoreApplication::translate("MainWindow", "Move_L", nullptr));
        grip->setText(QCoreApplication::translate("MainWindow", "Grip", nullptr));
        release->setText(QCoreApplication::translate("MainWindow", "Release", nullptr));
        reset->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        copy->setText(QCoreApplication::translate("MainWindow", "Copy", nullptr));
        velMinLabel->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        velMaxLabel->setText(QCoreApplication::translate("MainWindow", "60", nullptr));
        accMinLabel->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        accMaxLabel->setText(QCoreApplication::translate("MainWindow", "60", nullptr));
        labelAcc->setText(QCoreApplication::translate("MainWindow", "ACC", nullptr));
        labelVel->setText(QCoreApplication::translate("MainWindow", "VEL", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // QT_GUI_H
