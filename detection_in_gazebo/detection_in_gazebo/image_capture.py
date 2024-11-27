import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2
import os


class CameraSubscriber(Node):
    def __init__(self):
        super().__init__('camera_subscriber_node')
        self.subscriber_ = self.create_subscription(Image, "/camera/image_raw", self.camera_sub_callback, 10)
        self.bridge = CvBridge()
        self.image_id = 0
        script_path = os.path.dirname(os.path.abspath(__file__))
        self.package_path = os.path.dirname(script_path)
    
    def camera_sub_callback(self, msg):
        current_frame = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        cv2.imshow("Topic: /camera/image_raw", current_frame)
        
        key = cv2.waitKey(1) & 0xFF
        if key == ord('q'):
            raise KeyboardInterrupt
        if key == ord('s'):
            self.image_id += 1
            saved_img_path = self.package_path + '/images/image_{}.jpg'.format(self.image_id)
            cv2.imwrite(saved_img_path, current_frame)
            print("Image {} captured!".format(self.image_id))
            print(saved_img_path, "\n")



def main():
    print("Press q ti quit \nPress s to save current image to <path_to_detection_in_gazebo>/images/\n")

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
