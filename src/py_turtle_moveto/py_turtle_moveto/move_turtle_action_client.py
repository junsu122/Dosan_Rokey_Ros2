#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient
from my_robot_interfaces.action import MoveTurtle

class MoveTurtleActionClient(Node):

    def __init__(self):
        super().__init__('move_turtle_action_client')
        self._action_client = ActionClient(self, MoveTurtle, '/turtle1/move_turtle')

    def send_goal(self, x, y):
        goal_msg = MoveTurtle.Goal()
        goal_msg.x = x
        goal_msg.y = y

        self._action_client.wait_for_server()
        self.get_logger().info(f'Sending goal: ({x}, {y})')
        return self._action_client.send_goal_async(goal_msg, feedback_callback=self.feedback_callback)

    def feedback_callback(self, feedback_msg):
        feedback = feedback_msg.feedback
        self.get_logger().info(f'Distance remaining: {feedback.distance_remaining:.2f}')


def main(args=None):
    rclpy.init(args=args)
    node = MoveTurtleActionClient()

    # 1단계: 서버에 목표를 보내고 '수락' 여부를 기다림
    send_goal_future = node.send_goal(8.0, 8.0)
    rclpy.spin_until_future_complete(node, send_goal_future)
    
    goal_handle = send_goal_future.result()

    if not goal_handle.accepted:
        node.get_logger().info('Goal rejected :(')
        return

    node.get_logger().info('Goal accepted :)')

    # 2단계: 거북이가 최종 '도착'해서 결과를 보낼 때까지 기다림 (핵심!)
    result_future = goal_handle.get_result_async()
    rclpy.spin_until_future_complete(node, result_future)

    # 3단계: 결과 확인
    result = result_future.result().result
    node.get_logger().info(f'Goal completed! Success: {result.success}')

    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
