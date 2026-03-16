# 필요한 모듈 임포트
import rclpy
from rclpy.node import Node
from rclpy.action import ActionServer
import time  # 시간 지연을 위해 사용

# Fibonacci 액션 메시지 임포트 (action_tutorials_interfaces 패키지에서 생성된 메시지)
from action_tutorials_interfaces.action import Fibonacci


# 액션 서버 노드 클래스 정의
class FibonacciActionServer(Node):
    
    def __init__(self):
        super().__init__("fibonacci_action_server")  # 노드 이름 설정
        # 액션 서버 생성: Fibonacci 타입, 이름은 "fibonacci", 콜백 함수는 execute_callback
        self._action_server = ActionServer(
            self, Fibonacci, "fibonacci", self.execute_callback
        )

    # 목표(goal)를 실행할 때 호출되는 콜백 함수
    # 비동기로도 가능하지만 여기선 동기 방식 사용
    def execute_callback(self, goal_handle):
        self.get_logger().info("Executing goal...")  # 실행 시작 로그 출력

        # 피드백 메시지 초기화: 처음 두 수는 0과 1
        feedback_msg = Fibonacci.Feedback()
        feedback_msg.partial_sequence = [0, 1]

        # 피보나치 수열 계산 루프
        for i in range(2, goal_handle.request.order):
            # 다음 수 계산 후 시퀀스에 추가
            feedback_msg.partial_sequence.append(
                feedback_msg.partial_sequence[i - 1]
                + feedback_msg.partial_sequence[i - 2]
            )
            # 클라이언트에 피드백 전송
            goal_handle.publish_feedback(feedback_msg)
            self.get_logger().info(f"Feedback: {feedback_msg.partial_sequence}")
            time.sleep(1)  # 1초 대기 (지연을 통해 실행 상황을 보여줌)

        # 목표 성공 처리
        goal_handle.succeed()

        # 결과 메시지 작성
        result = Fibonacci.Result()
        result.sequence = feedback_msg.partial_sequence  # 최종 수열 설정

        return result  # 클라이언트에 결과 반환

# 메인 함수: ROS 2 노드 실행
def main(args=None):
    rclpy.init(args=args)  # ROS 2 초기화
    node = FibonacciActionServer()  # 액션 서버 노드 생성
    rclpy.spin(node)  # 콜백 처리 루프 (서버 유지)
    rclpy.shutdown()
