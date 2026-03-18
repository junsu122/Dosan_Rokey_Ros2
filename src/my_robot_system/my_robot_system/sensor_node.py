import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32
import random


class SensorNode(Node):
    def __init__(self):
        super().__init__("sensor_node")
        self.publisher = self.create_publisher(Float32, "temperature", 10)
        self.timer = self.create_timer(1.0, self.publish_temperature)

    def publish_temperature(self):
        temp = random.uniform(25.0, 35.0)
        self.get_logger().info(f"Publishing Temperature: {temp:.2f}")
        msg = Float32()
        msg.data = temp
        self.publisher.publish(msg)


def main():
    rclpy.init()
    sensor_node = SensorNode()
    rclpy.spin(sensor_node)
    sensor_node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
