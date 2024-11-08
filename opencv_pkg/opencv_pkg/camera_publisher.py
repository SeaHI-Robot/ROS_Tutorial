import rclpy
from rclpy.node import Node
from cv_bridge import CvBridge
from sensor_msgs.msg import CompressedImage
import cv2

class CameraPublisher(Node):
    def __init__(self):
        super().__init__('camera_publisher_node')
        self.publisher_ = self.create_publisher(CompressedImage, 'image/compressed', 10)
        self.timer = self.create_timer(0.1, self.publish_image)
        self.cap = cv2.VideoCapture(0) 
        self.bridge = CvBridge()

    def publish_image(self):
        ret, frame = self.cap.read()
        if ret:
            compressed_image = self.bridge.cv2_to_compressed_imgmsg(frame)
            self.publisher_.publish(compressed_image)

    def __del__(self):
        self.cap.release()

def main(args=None):
    rclpy.init(args=args)
    camera_node = CameraPublisher()
    rclpy.spin(camera_node)
    camera_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
