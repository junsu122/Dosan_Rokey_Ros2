import rclpy
from rclpy.node import Node
from std_srvs.srv import Trigger


class CoolerService(Node):
    def __init__(self):
        super().__init__("cooler_service")
        self.srv = self.create_service(Trigger, "cooler_motor", self.handle_request)

    def handle_request(self, request, response):
        self.get_logger().info("Cooler activated!")
        response.success = True
        response.message = "Cooler turned on"
        return response


def main():
    rclpy.init()
    cooler_service = CoolerService()
    rclpy.spin(cooler_service)
    cooler_service.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
