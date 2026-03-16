import rclpy
from rclpy.node import Node
from rcl_interfaces.msg import ParameterType
from rcl_interfaces.msg import SetParametersResult


# 파라미터를 사용하는 ROS 2 노드 정의
class ParameterNode(Node):
    
    def __init__(self):
        # 노드 이름을 'parameter_node'로 초기화
        super().__init__("parameter_node")

        # 'my_param'이라는 이름의 파라미터를 선언하고 기본값은 'default_value'로 설정
        self.declare_parameter("my_param", "default_value")

        # 파라미터 값을 가져와서 로그로 출력
        param_value = self.get_parameter("my_param").get_parameter_value().string_value
        self.get_logger().info(f"Initial my_param: {param_value}")

        # 타이머를 설정하여 2초마다 콜백 실행
        self.timer = self.create_timer(2.0, self.timer_callback)

        # 파라미터 값이 변경될 때 호출될 콜백 등록
        self.add_on_set_parameters_callback(self.parameter_callback)

    # 주기적으로 현재 파라미터 값을 출력하는 콜백 함수
    def timer_callback(self):
        current_value = (
            self.get_parameter("my_param").get_parameter_value().string_value
        )
        self.get_logger().info(f"Current my_param: {current_value}")

    # 파라미터가 변경될 때 호출되는 콜백 함수
    def parameter_callback(self, params):
        for param in params:
            # 'my_param'이라는 이름의 파라미터가 변경되었을 경우 로그 출력
            if param.name == "my_param":
                self.get_logger().info(f"Parameter my_param updated to: {param.value}")
        # 파라미터 변경을 허용
        return SetParametersResult(successful=True)


# 노드를 실행하는 메인 함수
def main(args=None):
    rclpy.init(args=args)  # rclpy 초기화
    node = ParameterNode()  # 노드 생성
    rclpy.spin(node)  # 노드를 실행 (spin)
    node.destroy_node()  # 노드 종료 시 리소스 정리
    rclpy.shutdown()  # rclpy 종료


# 이 파일이 메인으로 실행될 경우 main() 실행
if __name__ == "__main__":
    main()
