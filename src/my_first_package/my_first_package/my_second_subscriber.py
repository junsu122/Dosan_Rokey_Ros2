import rclpy as rp
from rclpy.node import Node
from sensor_msgs.msg import Temperature


class BoardtempSubscriber(Node):

    def __init__(self):
        super().__init__('board_temp_subscriber')
        self.subscription = self.create_subscription(
            Temperature, '/temp', self.callback, 10
        )
        self.subscription

    def callback(self, msg):
        print("Second: ", msg.header.stamp.sec, ", Temperature: ", msg.temperature)


def main():
    rp.init(args=None)

    board_temp_subscriber = BoardtempSubscriber()
    rp.spin(board_temp_subscriber)

    board_temp_subscriber.destroy_node()
    rp.shutdown()

if __name__ == '__main__':
    main()
