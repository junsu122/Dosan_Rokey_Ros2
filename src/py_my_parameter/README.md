ros2 launch py_my_parameter parameter.launch.py
ros2 run py_my_parameter parameter_node
이 두가지를 실행시키면, 기존 my_param의 내용이 업데이트 된다.

ros2 param set /parameter_node my_param "내가-바꿀-내용"
을 입력하면, 기존에 동작하던 param의 내용이 업데이트 되어서 보여진다.