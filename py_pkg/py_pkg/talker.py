import rclpy
from rclpy.node import Node
import sys
from std_msgs.msg import String

class Talker(Node):
    def __init__(self):
        super().__init__("Talker")
        self.publisher = self.create_publisher(String, "talker_topic", 10)
        self.count = 0
        self.timer_ = self.create_timer(0.5, self.timer_callback)
    def timer_callback(self):
        message = String()
        message.data = "Hello ROS2，" + str(self.count)
        self.get_logger().info("Publishing:" + message.data)
        self.publisher.publish(message)
        self.count += 1
        
def main():
    rclpy.init()
    node = Talker()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()

# def main():
#     rclpy.init() 
#     node = Node(node_name="talker_node")
#     node.get_logger().info("Talker python node is started")
#     rclpy.spin(node = node)
#     rclpy.shutdown()
