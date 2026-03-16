import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32
import random

class TemperaturePublisher(Node):
    
    def __init__(self):
        super().__init__('temperature_publisher')
        self.publisher_ = self.create_publisher(Float32, 'temperature', 10)
        self.timer = self.create_timer(1.0, self.publish_temperature)
        self.get_logger().info("Temperature Publisher started.")

    def publish_temperature(self):
        msg = Float32()
        msg.data = random.uniform(20.0, 40.0)  # 예: 20~40도
        self.publisher_.publish(msg)
        self.get_logger().info(f'Published temperature: {msg.data:.2f} °C')

def main(args=None):
    rclpy.init(args=args)
    node = TemperaturePublisher()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()
