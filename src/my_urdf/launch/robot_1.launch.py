import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.substitutions import LaunchConfiguration
from launch.actions import DeclareLaunchArgument
from launch_ros.actions import Node
import xacro

def generate_launch_description():
    use_sim_time = LaunchConfiguration("use_sim_time")

    pkg_path = os.path.join(get_package_share_directory("my_urdf"))
    xacro_file = os.path.join(pkg_path, "urdf", "robot_1.xacro")
    # xacro_file = os.path.join(pkg_path, "urdf", "robot_revolute.xacro")
    robot_description = xacro.process_file(xacro_file)
    params = {"robot_description": robot_description.toxml(), "use_sim_time": use_sim_time}

    return LaunchDescription(
        [
            DeclareLaunchArgument(
                "use_sim_time", default_value="false", description="use sim time"
            ),
            Node(
                package="robot_state_publisher",
                executable="robot_state_publisher",
                output="screen",
                parameters=[params],
            ),
            # move_robot.py에서 /joint_state를 publish하므로
            # 별도의 /joint_state_publisher 노드를 추가할 필요가 없습니다.
            # 아래의 joint_state_publisher_gui를 이용하여 move_robot.py를 실행하기 전에 간단하게 확인해볼 수 있습니다.
            # Node(package='joint_state_publisher_gui',
            #                     executable='joint_state_publisher_gui',
            #                     name='joint_state_publisher_gui'),
            Node(
                package="rviz2",
                executable="rviz2",
                output="screen",
                parameters=[params],
            ),
        ]
    )
