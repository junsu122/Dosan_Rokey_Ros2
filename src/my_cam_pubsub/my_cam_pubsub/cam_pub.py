import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2


class CameraPublisher(Node):

    def __init__(self):
        super().__init__("camera_publisher")
        self.publisher = self.create_publisher(Image, "camera/image_raw", 10)
        self.timer = self.create_timer(0.1, self.timer_callback)  # 10Hz
        self.cap = cv2.VideoCapture(0)
        self.bridge = CvBridge()

    def timer_callback(self):
        ret, frame = self.cap.read()
        if not ret:
            self.get_logger().error("Failed to read from camera")
            return

        msg = self.bridge.cv2_to_imgmsg(frame, encoding="bgr8")
        self.publisher.publish(msg)
        self.get_logger().info("Published image")


def main():
    rclpy.init()
    node = CameraPublisher()
    rclpy.spin(node)
    node.cap.release()
    node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
