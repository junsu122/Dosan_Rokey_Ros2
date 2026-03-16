#!/usr/bin/env python3
"""
Turtle Controller Node
======================
Navigates the turtle toward the apple using P-Control.
- Subscribes to /turtle1/pose (current position) and /apple_position (target)
- Publishes /turtle1/cmd_vel (velocity command)
- Publishes /apple_eaten (Bool) when the turtle reaches the apple

Concepts demonstrated: Topic Subscriber/Publisher, P-Control (Proportional Control)
"""

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist, Point
from turtlesim.msg import Pose
from std_msgs.msg import Bool
import math


class TurtleController(Node):
    def __init__(self):
        super().__init__('turtle_controller')

        # --- Publishers ---
        self.cmd_vel_pub = self.create_publisher(Twist, '/turtle1/cmd_vel', 10)
        self.eaten_pub = self.create_publisher(Bool, '/apple_eaten', 10)

        # --- Subscribers ---
        self.pose_sub = self.create_subscription(
            Pose, '/turtle1/pose', self.pose_callback, 10)
        self.apple_sub = self.create_subscription(
            Point, '/apple_position', self.apple_callback, 10)

        # State
        self.current_pose = None
        self.target = None
        self.score = 0
        self.apple_reached = False

        # P-Control gains
        self.Kp_linear = 1.5
        self.Kp_angular = 4.0

        # Control loop at 30 Hz
        self.timer = self.create_timer(1 / 30, self.control_loop)

        self.get_logger().info('[TurtleController] Ready. Waiting for apple position...')

    def pose_callback(self, msg):
        self.current_pose = msg

    def apple_callback(self, msg):
        if self.apple_reached:
            # New apple arrived after we ate the previous one
            self.apple_reached = False
        self.target = msg

    def control_loop(self):
        if self.current_pose is None or self.target is None or self.apple_reached:
            return

        # --- Error calculation ---
        dx = self.target.x - self.current_pose.x
        dy = self.target.y - self.current_pose.y

        distance_error = math.sqrt(dx ** 2 + dy ** 2)
        angle_to_target = math.atan2(dy, dx)
        angle_error = angle_to_target - self.current_pose.theta

        # Normalize angle to [-pi, pi]
        while angle_error > math.pi:
            angle_error -= 2 * math.pi
        while angle_error < -math.pi:
            angle_error += 2 * math.pi

        # --- Apple reached? ---
        if distance_error < 0.3:
            self.score += 1
            self.get_logger().info(f'Apple collected!  Score: {self.score}')

            # Stop the turtle
            self.cmd_vel_pub.publish(Twist())

            # Notify the spawner
            eaten_msg = Bool()
            eaten_msg.data = True
            self.eaten_pub.publish(eaten_msg)
            self.apple_reached = True
            return

        # --- P-Control ---
        cmd = Twist()
        cmd.linear.x = self.Kp_linear * distance_error
        cmd.angular.z = self.Kp_angular * angle_error
        self.cmd_vel_pub.publish(cmd)


def main(args=None):
    rclpy.init(args=args)
    node = TurtleController()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
