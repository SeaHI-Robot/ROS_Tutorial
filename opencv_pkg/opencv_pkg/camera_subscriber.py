from inspect import currentframe
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import CompressedImage
from cv_bridge import CvBridge
import cv2
import numpy as np

class CameraSubscriber(Node):
    def __init__(self):
        super().__init__('camera_subscriber_node')
        self.subscriber_ = self.create_subscription(CompressedImage, "image/compressed", self.camera_sub_callback, 10)
        self.bridge = CvBridge()
    
    def camera_sub_callback(self, msg):
        image_data = np.frombuffer(msg.data, dtype=np.uint8)
        current_frame = cv2.imdecode(image_data, cv2.IMREAD_COLOR)
        cv2.imshow("Topic: image/compressed", current_frame)
        
        key = cv2.waitKey(1) & 0xFF
        if key == ord('q'):
            raise KeyboardInterrupt

def main():
    rclpy.init()
    camera_subscriber = CameraSubscriber()
    try:
        rclpy.spin(camera_subscriber)
    except KeyboardInterrupt:
        pass
    
    camera_subscriber.destroy_node()
    rclpy.shutdown()
    cv2.destroyAllWindows()
    
if __name__ == '__main__':
    main()
