from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    sensor_node = Node(
        package="my_robot_system",
        executable="sensor_node",
        name="sensor_node",
        output="screen",
    )

    manager_node = Node(
        package="my_robot_system",
        executable="manager_node",
        name="manager_node",
        output="screen",
    )

    cooler_service = Node(
        package="my_robot_system",
        executable="cooler_service",
        name="cooler_service",
        output="screen",
    )

    switch_action_server = Node(
        package="my_robot_system",
        executable="switch_action_server",
        name="switch_action_server",
        output="screen",
    )

    return LaunchDescription(
        [
            sensor_node,
            manager_node,
            cooler_service,
            switch_action_server,
        ]
    )
