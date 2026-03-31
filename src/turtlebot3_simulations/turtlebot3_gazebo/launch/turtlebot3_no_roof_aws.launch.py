#!/usr/bin/env python3

import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    # --- [강력 처방 1] NVIDIA 그래픽 가속 및 에러 방지 설정 ---
    # MX450 GPU를 강제로 사용하게 하여 'Assertion px != 0' 에러를 차단합니다.
    os.environ['__NV_PRIME_RENDER_OFFLOAD'] = '1'
    os.environ['__GLX_VENDOR_LIBRARY_NAME'] = 'nvidia'
    os.environ['OGRE_RTT_MODE'] = 'Copy'

    # --- [강력 처방 2] 경로 정화 (수백 줄의 에러 로그 해결) ---
    # 가제보가 엉뚱한 곳을 뒤지지 않도록 준수님의 실제 워크스페이스 경로만 딱 지정합니다.
    user_home = os.path.expanduser('~')
    pkg_share_path = "/opt/ros/humble/share/turtlebot3_gazebo/models"
    my_model_path = os.path.join(user_home, 'ros2_ws/src/turtlebot3_simulations/turtlebot3_gazebo/models')
    gazebo_system_models = "/usr/share/gazebo-11/models"
    
    # GAZEBO_MODEL_PATH를 새로 정의 (기존 꼬인 환경변수 $GAZEBO_MODEL_PATH는 완전히 무시함)
    os.environ['GAZEBO_MODEL_PATH'] = f"{my_model_path}:{pkg_share_path}:{gazebo_system_models}"

    # 1. 패키지 경로 설정
    pkg_turtlebot3_gazebo = get_package_share_directory('turtlebot3_gazebo')
    pkg_gazebo_ros = get_package_share_directory('gazebo_ros')
    
    use_sim_time = LaunchConfiguration('use_sim_time', default='true')
    x_pose = LaunchConfiguration('x_pose', default='-2.0')
    y_pose = LaunchConfiguration('y_pose', default='-0.5')

    # 월드 파일 설정
    world = os.path.join(
        pkg_turtlebot3_gazebo,
        'worlds',
        'no_roof_small_warehouse.world'
    )

    # 2. Gazebo 서버/클라이언트 설정 (상세 로그 확인을 위해 verbose 활성화)
    gzserver_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_gazebo_ros, 'launch', 'gzserver.launch.py')
        ),
        launch_arguments={'world': world, 'verbose': 'true'}.items()
    )

    gzclient_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_gazebo_ros, 'launch', 'gzclient.launch.py')
        ),
        launch_arguments={'verbose': 'true'}.items()
    )

    # 3. 로봇 상태 출판 및 스폰 설정
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

    # 4. 실행 액션 추가
    ld = LaunchDescription()
    ld.add_action(gzserver_cmd)
    ld.add_action(gzclient_cmd)
    ld.add_action(robot_state_publisher_cmd)
    ld.add_action(spawn_turtlebot_cmd)

    return ld