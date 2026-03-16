#!/usr/bin/env python3
"""
Apple Spawner Node
==================
Manages apple (turtle) lifecycle using ROS2 Services.
- Spawns a new apple at a random position
- Kills it when the controller reports it as eaten
- Publishes the apple target position on /apple_position

Concepts demonstrated: Service Client (Spawn, Kill), Topic Publisher
"""

import rclpy
from rclpy.node import Node
from turtlesim.srv import Spawn, Kill
from geometry_msgs.msg import Point
from std_msgs.msg import Bool
import random


class AppleSpawner(Node):
    def __init__(self):
        super().__init__('apple_spawner')

        # --- Service Clients (Spawn / Kill) ---
        self.spawn_client = self.create_client(Spawn, '/spawn')
        self.kill_client = self.create_client(Kill, '/kill')

        # --- Topic Publisher: broadcast apple position ---
        self.apple_pos_pub = self.create_publisher(Point, '/apple_position', 10)

        # --- Topic Subscriber: listen for "apple eaten" signal ---
        self.eaten_sub = self.create_subscription(
            Bool, '/apple_eaten', self.on_apple_eaten, 10)

        self.apple_name = 'apple_turtle'
        self.apple_exists = False
        self.target = Point()

        # Periodic publish of current apple position (so late-joining nodes get it)
        self.timer = self.create_timer(0.5, self.publish_position)

        # Spawn the first apple after a short delay (one-shot timer)
        self._initial_timer = self.create_timer(1.0, self.initial_spawn)

        self.get_logger().info('[AppleSpawner] Ready. Waiting for turtlesim...')

    def initial_spawn(self):
        """One-shot: spawn the very first apple, then cancel the timer."""
        self._initial_timer.cancel()
        if not self.apple_exists:
            self.spawn_apple()

    def spawn_apple(self):
        """Call /spawn service to create a new apple at a random location."""
        if self.apple_exists:
            return  # guard against double-spawn
        if not self.spawn_client.wait_for_service(timeout_sec=2.0):
            self.get_logger().warn('Spawn service not available, retrying...')
            return

        self.target.x = random.uniform(1.0, 10.0)
        self.target.y = random.uniform(1.0, 10.0)
        self.target.z = 0.0

        req = Spawn.Request()
        req.x = self.target.x
        req.y = self.target.y
        req.theta = 0.0
        req.name = self.apple_name

        future = self.spawn_client.call_async(req)
        future.add_done_callback(self.on_spawn_done)

    def on_spawn_done(self, future):
        try:
            future.result()
            self.apple_exists = True
            self.get_logger().info(
                f'New apple spawned at ({self.target.x:.2f}, {self.target.y:.2f})')
        except Exception as e:
            self.get_logger().error(f'Spawn failed: {e}')

    def kill_apple(self):
        """Call /kill service to remove the eaten apple."""
        req = Kill.Request()
        req.name = self.apple_name
        future = self.kill_client.call_async(req)
        future.add_done_callback(self.on_kill_done)

    def on_kill_done(self, future):
        try:
            future.result()
        except Exception:
            pass  # apple may already be gone
        self.apple_exists = False
        # Spawn a new one after a brief pause (one-shot)
        self._respawn_timer = self.create_timer(0.5, self._respawn_once)

    def _respawn_once(self):
        """One-shot respawn — cancel the timer after firing."""
        self._respawn_timer.cancel()
        self.spawn_apple()

    def on_apple_eaten(self, msg):
        """Callback: controller says the apple was eaten."""
        if msg.data and self.apple_exists:
            self.get_logger().info('Apple eaten! Removing and spawning next...')
            self.kill_apple()

    def publish_position(self):
        """Continuously broadcast the current apple position."""
        if self.apple_exists:
            self.apple_pos_pub.publish(self.target)


def main(args=None):
    rclpy.init(args=args)
    node = AppleSpawner()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
