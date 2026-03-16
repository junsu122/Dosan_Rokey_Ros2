import rclpy as rp
from rclpy.node import Node
from sensor_msgs.msg import Temperature # 추가됨
import math  # 추가됨
from datetime import datetime # 추가됨


class BoardTemp(Node):

    def __init__(self):
        super().__init__("board_temp_publisher")
        self.publisher = self.create_publisher(Temperature, "/temp", 10)

        timer_period = 0.5
        self.timer = self.create_timer(timer_period, self.timer_callback)

    def timer_callback(self):
        msg = Temperature()
        msg.header.stamp.sec = datetime.now().second
        msg.temperature = math.sin(msg.header.stamp.sec)
        self.publisher.publish(msg)

def main():
    rp.init(args=None)
    board_temp_publisher = BoardTemp()
    rp.spin(board_temp_publisher)
    board_temp_publisher.destroy_node()
    rp.shutdown()

if __name__ == "__main__":
    main()
