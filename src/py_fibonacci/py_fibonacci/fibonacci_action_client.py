# 필요한 모듈 임포트
import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient

# Fibonacci 액션 메시지 임포트 (IDL로 생성된 모듈)
from action_tutorials_interfaces.action import Fibonacci

# 액션 클라이언트 노드 정의
# ... (임포트 부분 동일)

class FibonacciActionClient(Node):
    def __init__(self):
        super().__init__("fibonacci_action_client")
        self._client = ActionClient(self, Fibonacci, "fibonacci") ## action파일 Goal, Reuslt, Feedback의 메세지 형태를 가져와서 fibonacci라는 이름의 액션 클라이언트 생성

    def send_goal(self, order):
        self.get_logger().info('--- [STEP 1] 서버 연결 확인 중... ---')
        self._client.wait_for_server() ## get_logger().info()를 이용해 로그 생성, wait_for_server()로 액션 서버가 준비될 때까지 대기

        goal_msg = Fibonacci.Goal() ## Fibonacci 애서 Goal의 메세지 형식을 가져와서 goal_msg라는 객체 생성
        goal_msg.order = order
        self.get_logger().info(f'--- [STEP 2] Goal 전송 (order: {order}) ---')

        self._client.send_goal_async(
            goal_msg,
            feedback_callback=self.feedback_callback
        ).add_done_callback(self.goal_response_callback)

    def goal_response_callback(self, future):
        goal_handle = future.result()
        # [Goal Response] 서버가 이 요청을 수행할지 말지 결정한 결과
        if not goal_handle.accepted:
            self.get_logger().error("--- [STEP 3] Goal Response: 거절됨 (Rejected) ---")
            return

        self.get_logger().info("--- [STEP 3] Goal Response: 수락됨 (Accepted) ---")
        self.get_logger().info("--- [STEP 4] Result 요청 중... ---")
        goal_handle.get_result_async().add_done_callback(self.get_result_callback)

    def feedback_callback(self, feedback):
        # [Feedback] 작업 중간 보고
        self.get_logger().info(f"[Feedback 수신]: {feedback.feedback.partial_sequence}")

    def get_result_callback(self, future):
        # [Result Response] 최종 결과 수신
        result = future.result().result
        self.get_logger().info("====================================")
        self.get_logger().info(f"--- [STEP 5] 최종 Result 수신 완료! ---")
        self.get_logger().info(f"결과 시퀀스: {result.sequence}")
        self.get_logger().info("====================================")
        rclpy.shutdown()    


# 메인 함수: ROS 2 초기화 및 노드 실행
def main(args=None):
    rclpy.init(args=args)  # ROS 2 초기화
    client = FibonacciActionClient()  # 액션 클라이언트 객체 생성
    client.send_goal(10)  # 피보나치 수열 10개 요청
    rclpy.spin(client)  # 콜백을 기다리며 노드를 계속 실행
