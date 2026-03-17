import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from std_msgs.msg import String
from cv_bridge import CvBridge
import cv2
from ultralytics import YOLO


class YoloDetector(Node):

    def __init__(self):
        super().__init__('yolo_detector')

        # camera subscribe
        self.subscription = self.create_subscription(
            Image,
            'camera/image_raw',
            self.image_callback,
            10)

        # detection text publisher
        self.result_pub = self.create_publisher(
            String,
            'detection/result',
            10)

        # annotated image publisher
        self.image_pub = self.create_publisher(
            Image,
            'detection/image',
            10)

        self.bridge = CvBridge()

        # YOLO model
        self.model = YOLO("./src/yolo_pub/models/yolov8n.pt")


    def image_callback(self, msg):

        frame = self.bridge.imgmsg_to_cv2(msg, "bgr8")

        results = self.model(frame)

        for r in results:
            boxes = r.boxes

            for box in boxes:

                x1, y1, x2, y2 = box.xyxy[0].tolist()

                x1 = int(x1)
                y1 = int(y1)
                x2 = int(x2)
                y2 = int(y2)

                cls_id = int(box.cls[0])
                label = self.model.names[cls_id]

                width = x2 - x1
                height = y2 - y1

                cx = int(x1 + width / 2)
                cy = int(y1 + height / 2)

                # -------------------------
                # Bounding box
                # -------------------------
                cv2.rectangle(frame, (x1, y1), (x2, y2), (0,255,0), 2)

                # -------------------------
                # Center point
                # -------------------------
                cv2.circle(frame, (cx, cy), 5, (0,0,255), -1)

                # -------------------------
                # Label text
                # -------------------------
                text = f"{label}"
                cv2.putText(frame, text,
                            (x1, y1-10),
                            cv2.FONT_HERSHEY_SIMPLEX,
                            0.6,
                            (0,255,0),
                            2)

                # -------------------------
                # publish detection result
                # -------------------------
                result_text = f"{label}, center=({cx},{cy}), width={width}, height={height}"

                result_msg = String()
                result_msg.data = result_text
                self.result_pub.publish(result_msg)

        # -------------------------
        # publish annotated image
        # -------------------------
        img_msg = self.bridge.cv2_to_imgmsg(frame, "bgr8")
        self.image_pub.publish(img_msg)


def main(args=None):

    rclpy.init(args=args)

    node = YoloDetector()

    rclpy.spin(node)

    node.destroy_node()
    rclpy.shutdown()