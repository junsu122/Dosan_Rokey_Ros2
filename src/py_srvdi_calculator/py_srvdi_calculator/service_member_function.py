import rclpy
from rclpy.node import Node
from my_robot_interfaces.srv import Calculator

class MinimalService(Node):

    def __init__(self):
        super().__init__("minimal_service")
        self.srv = self.create_service(
            Calculator, "add_two_ints", self.add_two_ints_callback
        )

    def add_two_ints_callback(self, request, response):
        response.sum = request.a + request.b
        response.minus = request.a - request.b
        response.multiply = request.a * request.b
        response.divide = request.a / request.b
        self.get_logger().info("Incoming request\na: %d b: %d" % (request.a, request.b))

        return response

def main():
    rclpy.init()
    minimal_service = MinimalService()
    rclpy.spin(minimal_service)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
