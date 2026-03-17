# 1. turtlesim 실행
ros2 run turtlesim turtlesim_node

# 2. 액션 서버 실행
ros2 run py_turtle_moveto move_turtle_action_server

# 3. 액션 클라이언트 실행 (목표 전송)
ros2 run py_turtle_moveto move_turtle_action_client

# 4. ros2 action send_goal 명령으로도 직접 테스트
ros2 action send_goal /turtle1/move_turtle my_robot_interfaces/action/MoveTurtle "{x: 8.0, y: 2.0}"
