import rclpy
from rclpy.node import Node
from std_msgs.msg import String


class Listener(Node):
    def __init__(self):
        super().__init__("listener")
        self.subscription = self.create_subscription( String, "talker_topic", self.listener_callback, 10)
        self.subscription  # prevent unused variable warning

    def listener_callback(self, msg):
        self.get_logger().info('I heard: "%s"' % msg.data)


def main(args=None):
    rclpy.init(args=args)

    listener_node = Listener()

    rclpy.spin(listener_node)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    listener_node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
