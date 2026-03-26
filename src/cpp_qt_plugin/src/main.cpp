// pip install pybind11
#include "./mainwindow.cpp"
#include <QApplication>
#include <pybind11/embed.h>
#include <memory>
#include <rclcpp/rclcpp.hpp>

namespace py = pybind11;

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    QApplication app(argc, argv);

    auto qt_node = rclcpp::Node::make_shared("qt_visualizer_node");

    MainWindow mainWindow(qt_node);
    mainWindow.show();

    auto executor = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
    executor->add_node(qt_node);

    std::thread rosThread([&]() { executor->spin(); });

    int ret = app.exec();

    rclcpp::shutdown();
    rosThread.join();

    return ret;
}
