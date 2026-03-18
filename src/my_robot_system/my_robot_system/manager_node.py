import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32
from std_srvs.srv import Trigger
from rclpy.action import ActionClient
from my_robot_interfaces.action import SwitchControl


class ManagerNode(Node):
    def __init__(self):
        super().__init__("manager_node")

        # Subscriber
        self.subscriber = self.create_subscription(
            Float32, "temperature", self.temp_callback, 10
        )

        # Service Client
        self.cooler_client = self.create_client(Trigger, "cooler_motor")

        # Action Client
        self.switch_client = ActionClient(self, SwitchControl, "switch_control")

        # 상태 변수 (중복 호출 방지)
        self.cooling_active = False

    def temp_callback(self, msg):
        temp = msg.data
        self.get_logger().info(f"Received temperature: {temp:.2f}")

        # 상태 기반 제어
        if temp > 30.0 and not self.cooling_active:
            self.get_logger().info("Temperature high → Cooling ON")
            self.cooling_active = True
            self.call_cooler_service()
            self.send_switch_goal(True)

        elif temp <= 30.0 and self.cooling_active:
            self.get_logger().info("Temperature normal → Cooling OFF")
            self.cooling_active = False
            self.send_switch_goal(False)

    # blocking 제거
    def call_cooler_service(self):
        if not self.cooler_client.service_is_ready():
            self.get_logger().warn("Cooler service not ready")
            return

        req = Trigger.Request()
        future = self.cooler_client.call_async(req)
        future.add_done_callback(self.cooler_response_callback)

    # 서비스 결과 처리
    def cooler_response_callback(self, future):
        try:
            response = future.result()
            self.get_logger().info(f"Service result: {response.message}")
        except Exception as e:
            self.get_logger().error(f"Service call failed: {e}")

    # action 결과 처리 포함
    def send_switch_goal(self, turn_on):
        if not self.switch_client.wait_for_server(timeout_sec=2.0):
            self.get_logger().warn("Switch control action server not available!")
            return

        goal_msg = SwitchControl.Goal()
        goal_msg.turn_on = turn_on

        self.get_logger().info(f"Sending goal: {'ON' if turn_on else 'OFF'}")

        future = self.switch_client.send_goal_async(goal_msg)
        future.add_done_callback(self.goal_response_callback)

    def goal_response_callback(self, future):
        try:
            goal_handle = future.result()
        except Exception as e:
            self.get_logger().error(f"Goal send failed: {e}")
            return

        if not goal_handle.accepted:
            self.get_logger().warn("Goal rejected")
            return

        self.get_logger().info("Goal accepted")

        result_future = goal_handle.get_result_async()
        result_future.add_done_callback(self.result_callback)

    def result_callback(self, future):
        try:
            result = future.result().result
            self.get_logger().info(f"Action result: {result.success}")
        except Exception as e:
            self.get_logger().error(f"Failed to get result: {e}")


def main():
    rclpy.init()
    manager_node = ManagerNode()
    rclpy.spin(manager_node)
    manager_node.destroy_node()
    manager_node.switch_client.destroy()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
