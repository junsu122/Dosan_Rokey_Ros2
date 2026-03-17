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
        self._client = ActionClient(self, Fibonacci, "fibonacci")

    def send_goal(self, order):
        self.get_logger().info('--- [STEP 1] 서버 연결 확인 중... ---')
        self._client.wait_for_server()

        goal_msg = Fibonacci.Goal()
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
    def __init__(self):
        super().__init__("fibonacci_action_client")  # 노드 이름 설정
        # Fibonacci 액션 타입의 액션 클라이언트 생성, 이름은 "fibonacci"
        self._client = ActionClient(self, Fibonacci, "fibonacci")

    def send_goal(self, order):
        # 액션 서버가 준비될 때까지 대기 (동기적 대기)
        self._client.wait_for_server()

        # 목표(goal) 메시지 생성 및 설정
        goal_msg = Fibonacci.Goal()
        goal_msg.order = order  # 몇 개의 피보나치 수를 요청할지 설정

        # 목표를 비동기로 전송하고, 피드백 및 응답 콜백 설정
        self._client.send_goal_async(
            goal_msg,
            feedback_callback=self.feedback_callback  # 피드백 콜백
        ).add_done_callback(self.goal_response_callback)  # 목표 수락 여부 콜백

    # 피드백을 수신했을 때 호출되는 콜백 함수
    def feedback_callback(self, feedback):
        self.get_logger().info(
            f"Received feedback: {feedback.feedback.partial_sequence}"
        )  # 현재까지 계산된 피보나치 수열을 출력

    # 목표 수락 여부를 처리하는 콜백 함수
    def goal_response_callback(self, future):
        goal_handle = future.result()  # 결과로부터 goal handle 획득

        if not goal_handle.accepted:
            self.get_logger().info("Goal rejected")  # 목표가 거절된 경우
            return

        self.get_logger().info("Goal accepted")  # 목표가 수락됨

        # 결과를 비동기로 요청하고, 완료되면 get_result_callback 호출
        goal_handle.get_result_async().add_done_callback(self.get_result_callback)

    # 목표 처리 결과를 받았을 때 호출되는 콜백 함수
    def get_result_callback(self, future):
        result = future.result().result  # 결과 객체에서 결과 데이터 추출
        self.get_logger().info(f"Result: {result.sequence}")  # 최종 피보나치 수열 출력

        # 노드 종료
        rclpy.shutdown()


# 메인 함수: ROS 2 초기화 및 노드 실행
def main(args=None):
    rclpy.init(args=args)  # ROS 2 초기화
    client = FibonacciActionClient()  # 액션 클라이언트 객체 생성
    client.send_goal(10)  # 피보나치 수열 10개 요청
    rclpy.spin(client)  # 콜백을 기다리며 노드를 계속 실행
