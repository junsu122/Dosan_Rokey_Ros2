# 필요한 모듈 임포트
import rclpy
from rclpy.node import Node
from rclpy.action import ActionServer
import time  # 시간 지연을 위해 사용

# Fibonacci 액션 메시지 임포트 (action_tutorials_interfaces 패키지에서 생성된 메시지)
from action_tutorials_interfaces.action import Fibonacci


# 액션 서버 노드 클래스 정의
# ... (임포트 부분 동일)

class FibonacciActionServer(Node):
    def __init__(self):
        super().__init__("fibonacci_action_server")
        self._action_server = ActionServer(
            self, Fibonacci, "fibonacci", self.execute_callback
        )
        self.get_logger().info("--- Fibonacci 액션 서버 대기 중... ---")

    def execute_callback(self, goal_handle):
        # [Goal Request 수신]
        order = goal_handle.request.order
        self.get_logger().info(f"--- [STEP 1] Goal 수신 (주문량: {order}) ---")
        self.get_logger().info("--- [STEP 2] 작업 실행 및 피드백 시작 ---")

        feedback_msg = Fibonacci.Feedback()
        feedback_msg.partial_sequence = [0, 1]

        for i in range(2, order):
            feedback_msg.partial_sequence.append(
                feedback_msg.partial_sequence[i - 1] + feedback_msg.partial_sequence[i - 2]
            )
            # [Publish Feedback] 중간 데이터 전송
            goal_handle.publish_feedback(feedback_msg)
            self.get_logger().info(f"피드백 전송 중... (길이: {len(feedback_msg.partial_sequence)})")
            time.sleep(1)

        # [Result 전송 준비]
        goal_handle.succeed()
        result = Fibonacci.Result()
        result.sequence = feedback_msg.partial_sequence
        
        self.get_logger().info("--- [STEP 3] 작업 완료 및 Result 반환 ---")
        return result    


# 메인 함수: ROS 2 노드 실행
def main(args=None):
    rclpy.init(args=args)  # ROS 2 초기화
    node = FibonacciActionServer()  # 액션 서버 노드 생성
    rclpy.spin(node)  # 콜백 처리 루프 (서버 유지)
    rclpy.shutdown()
