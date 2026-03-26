import rclpy
from rclpy.node import Node
from sensor_msgs.msg import JointState
import math

class MoveRobot(Node):
    def __init__(self):
        super().__init__('move_robot')

        self.publisher_ = self.create_publisher(JointState, 'joint_states', 10)

        timer_period = 0.05  # 20Hz로 부드럽게 퍼블리시
        self.timer = self.create_timer(timer_period, self.timer_callback)

        self.start_time = self.get_clock().now()

    def timer_callback(self):
        now = self.get_clock().now()
        t = (now - self.start_time).nanoseconds * 1e-9  # 초 단위 시간

        msg = JointState()
        msg.header.stamp = now.to_msg()
        # 로봇의 joint 이름
        msg.name = [
            'neck',
            'left_shoulder',
            'right_shoulder',
            'left_hip',
            'right_hip',
        ]

        # 시간에 따라 각 joint를 sinusoidal하게 움직이기
        msg.position = [
            0.3 * math.sin(t),        # neck: 좌우로 부드럽게 흔들기
            0.5 * math.sin(t * 0.5),  # left_shoulder: 천천히 팔 들기
            0.5 * math.sin(t * 0.5),  # right_shoulder: 천천히 팔 들기
            0.4 * math.sin(t * 0.7),  # left_hip: 다리 앞뒤로 움직이기
            0.4 * math.sin(t * 0.7),  # right_hip: 다리 앞뒤로 움직이기
        ]

        self.publisher_.publish(msg)

def main(args=None):
    rclpy.init(args=args)
    node = MoveRobot()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
    