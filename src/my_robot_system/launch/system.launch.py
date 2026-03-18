from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription(
        [
            Node(
                package="my_robot_system",
                executable="sensor_node",
                name="sensor_node",
                output="screen",
            ),
            Node(
                package="my_robot_system",
                executable="manager_node",
                name="manager_node",
                output="screen",
            ),
            Node(
                package="my_robot_system",
                executable="cooler_service",
                name="cooler_service",
                output="screen",
            ),
            Node(
                package="my_robot_system",
                executable="switch_action_server",
                name="switch_action_server",
                output="screen",
            ),
        ]
    )
