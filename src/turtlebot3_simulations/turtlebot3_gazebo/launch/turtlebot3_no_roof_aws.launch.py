#!/usr/bin/env python3

import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    # 1. 경로 설정
    pkg_turtlebot3_gazebo = get_package_share_directory('turtlebot3_gazebo')
    pkg_gazebo_ros = get_package_share_directory('gazebo_ros')
    
    use_sim_time = LaunchConfiguration('use_sim_time', default='true')
    x_pose = LaunchConfiguration('x_pose', default='-2.0')
    y_pose = LaunchConfiguration('y_pose', default='-0.5')

    world = os.path.join(
        pkg_turtlebot3_gazebo,
        'worlds',
        'no_roof_small_warehouse.world'
    )

    # 2. [핵심 수정] Gazebo 모델 경로 강제 정화
    # 준수님이 알려주신 실제 모델 경로를 직접 변수에 담습니다.
    # 기존 환경변수를 뒤에 붙이지 않고 이 경로와 기본 시스템 경로만 딱 지정합니다.
    my_model_path = "/home/junsu/ros2_ws/src/turtlebot3_simulations/turtlebot3_gazebo/models"
    gazebo_system_path = "/usr/share/gazebo-11/models"
    
    # 꼬인 /opt/ros/humble/share 경로를 포함하지 않도록 새로 정의해버립니다.
    os.environ['GAZEBO_MODEL_PATH'] = f"{my_model_path}:{gazebo_system_path}"

    # 3. Gazebo 서버/클라이언트 설정
    verbose_args = LaunchConfiguration('extra_gazebo_args', default='--verbose')
    
    gzserver_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_gazebo_ros, 'launch', 'gzserver.launch.py')
        ),
        launch_arguments={'world': world, 'extra_gazebo_args': verbose_args}.items()
    )

    gzclient_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_gazebo_ros, 'launch', 'gzclient.launch.py')
        ),
        launch_arguments={'extra_gazebo_args': verbose_args}.items()
    )

    # 4. 로봇 스폰 설정
    launch_file_dir = os.path.join(pkg_turtlebot3_gazebo, 'launch')
    
    robot_state_publisher_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(launch_file_dir, 'robot_state_publisher.launch.py')
        ),
        launch_arguments={'use_sim_time': use_sim_time}.items()
    )

    spawn_turtlebot_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(launch_file_dir, 'spawn_turtlebot3.launch.py')
        ),
        launch_arguments={'x_pose': x_pose, 'y_pose': y_pose}.items()
    )

    ld = LaunchDescription()
    ld.add_action(gzserver_cmd)
    ld.add_action(gzclient_cmd)
    ld.add_action(robot_state_publisher_cmd)
    ld.add_action(spawn_turtlebot_cmd)

    return ld