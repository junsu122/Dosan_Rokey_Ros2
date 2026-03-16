#!/usr/bin/env python3
"""
P-Control Plotter Node
======================
Real-time graph comparing P-Control vs No-P-Control velocities.
- Subscribes to /turtle1/pose, /turtle1/cmd_vel, /apple_position
- Top row:    Actual P-Control output (linear / angular velocity)
- Bottom row: Simulated No-P-Control output (constant bang-bang)

Concepts demonstrated: Topic Subscriber, Data Visualization
"""

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist, Point
from turtlesim.msg import Pose
import math
import threading
import time

import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt
from collections import deque


class PControlPlotter(Node):
    def __init__(self):
        super().__init__('p_control_plotter')

        # --- Subscribers ---
        self.pose_sub = self.create_subscription(
            Pose, '/turtle1/pose', self.pose_callback, 10)
        self.cmd_vel_sub = self.create_subscription(
            Twist, '/turtle1/cmd_vel', self.cmd_vel_callback, 10)
        self.apple_sub = self.create_subscription(
            Point, '/apple_position', self.apple_callback, 10)

        # State
        self.current_pose = None
        self.target = None
        self.latest_cmd = Twist()

        # Graph data (max 300 points ~ 10 seconds at 30 Hz)
        self.max_pts = 300
        self.timestamps = deque(maxlen=self.max_pts)
        self.p_linear = deque(maxlen=self.max_pts)
        self.p_angular = deque(maxlen=self.max_pts)
        self.nop_linear = deque(maxlen=self.max_pts)
        self.nop_angular = deque(maxlen=self.max_pts)

        self.start_time = time.time()
        self.lock = threading.Lock()

        # Record data at 30 Hz
        self.timer = self.create_timer(1 / 30, self.record_data)

        self.get_logger().info('[Plotter] Ready. Graph window will open shortly...')

    # ---- ROS2 Callbacks ----
    def pose_callback(self, msg):
        self.current_pose = msg

    def cmd_vel_callback(self, msg):
        self.latest_cmd = msg

    def apple_callback(self, msg):
        self.target = msg

    # ---- Data Recording ----
    def record_data(self):
        if self.current_pose is None or self.target is None:
            return

        dx = self.target.x - self.current_pose.x
        dy = self.target.y - self.current_pose.y
        distance_error = math.sqrt(dx ** 2 + dy ** 2)
        angle_to_target = math.atan2(dy, dx)
        angle_error = angle_to_target - self.current_pose.theta
        while angle_error > math.pi:
            angle_error -= 2 * math.pi
        while angle_error < -math.pi:
            angle_error += 2 * math.pi

        # "Without P-control" simulation
        CONST_LINEAR = 2.0
        CONST_ANGULAR = 2.0
        no_p_lin = CONST_LINEAR if distance_error > 0.3 else 0.0
        no_p_ang = CONST_ANGULAR * (1.0 if angle_error > 0 else -1.0) if distance_error > 0.3 else 0.0

        with self.lock:
            self.timestamps.append(time.time() - self.start_time)
            self.p_linear.append(self.latest_cmd.linear.x)
            self.p_angular.append(self.latest_cmd.angular.z)
            self.nop_linear.append(no_p_lin)
            self.nop_angular.append(no_p_ang)

    # ---- Matplotlib Graph ----
    def run_plot(self):
        """Run the real-time graph (must be called from main thread)."""
        plt.ion()
        fig, axes = plt.subplots(2, 2, figsize=(13, 8))
        fig.suptitle('P-Control vs No-P-Control  |  Real-Time Comparison',
                     fontsize=14, fontweight='bold', color='white')
        fig.patch.set_facecolor('#1e1e2e')

        def style(ax, title, ylabel):
            ax.set_facecolor('#181825')
            ax.set_title(title, color='white', fontsize=10, fontweight='bold')
            ax.set_xlabel('Time (s)', color='#cdd6f4', fontsize=8)
            ax.set_ylabel(ylabel, color='#cdd6f4', fontsize=8)
            ax.tick_params(colors='#6c7086')
            ax.grid(True, alpha=0.2, color='#585b70')
            for s in ax.spines.values():
                s.set_color('#313244')

        # Top: With P-Control
        style(axes[0][0], '[With P-Control]  Linear Velocity  (v = Kp * dist_err)', 'm/s')
        ln_pl, = axes[0][0].plot([], [], color='#a6e3a1', lw=1.8, label='P-Control Linear')
        axes[0][0].legend(loc='upper right', fontsize=7,
                          facecolor='#313244', edgecolor='#585b70', labelcolor='white')

        style(axes[0][1], '[With P-Control]  Angular Velocity  (w = Kp * angle_err)', 'rad/s')
        ln_pa, = axes[0][1].plot([], [], color='#89b4fa', lw=1.8, label='P-Control Angular')
        axes[0][1].legend(loc='upper right', fontsize=7,
                          facecolor='#313244', edgecolor='#585b70', labelcolor='white')

        # Bottom: Without P-Control
        style(axes[1][0], '[Without P-Control]  Linear Velocity  (constant speed)', 'm/s')
        ln_nl, = axes[1][0].plot([], [], color='#f38ba8', lw=1.8, ls='--', label='No-P Linear')
        axes[1][0].legend(loc='upper right', fontsize=7,
                          facecolor='#313244', edgecolor='#585b70', labelcolor='white')

        style(axes[1][1], '[Without P-Control]  Angular Velocity  (bang-bang steering)', 'rad/s')
        ln_na, = axes[1][1].plot([], [], color='#fab387', lw=1.8, ls='--', label='No-P Angular')
        axes[1][1].legend(loc='upper right', fontsize=7,
                          facecolor='#313244', edgecolor='#585b70', labelcolor='white')

        all_lines = [ln_pl, ln_pa, ln_nl, ln_na]
        plt.tight_layout()

        while plt.fignum_exists(fig.number):
            with self.lock:
                if len(self.timestamps) > 1:
                    t = list(self.timestamps)
                    datasets = [
                        list(self.p_linear),
                        list(self.p_angular),
                        list(self.nop_linear),
                        list(self.nop_angular),
                    ]
                    for line, data, ax in zip(all_lines, datasets, axes.flatten()):
                        line.set_data(t, data)
                        ax.set_xlim(max(0, t[-1] - 15), t[-1] + 0.5)
                        if data:
                            ymin, ymax = min(data), max(data)
                            margin = max(0.5, (ymax - ymin) * 0.15)
                            ax.set_ylim(ymin - margin, ymax + margin)
            try:
                fig.canvas.draw_idle()
                fig.canvas.flush_events()
            except Exception:
                break
            plt.pause(0.05)


def main(args=None):
    rclpy.init(args=args)
    node = PControlPlotter()

    # ROS2 spin in a background thread
    ros_thread = threading.Thread(target=rclpy.spin, args=(node,), daemon=True)
    ros_thread.start()

    # Matplotlib on main thread
    try:
        node.run_plot()
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
