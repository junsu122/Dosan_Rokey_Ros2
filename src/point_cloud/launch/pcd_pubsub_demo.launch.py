import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():


    ply_path = os.path.join(get_package_share_directory(
        'point_cloud'), 'resource', 'fragment.ply')
    assert os.path.exists(ply_path)

    return LaunchDescription([
        Node(package='point_cloud',
            executable='pcd_publisher_node',
            name='pcd_publisher_node',
            output='screen',
            arguments=[ply_path],
        ),
        Node(package='point_cloud',
            executable='pcd_subscriber_node',
            name='pcd_subscriber_node',
            output='screen',
            arguments=[ply_path],
        ),
    ])