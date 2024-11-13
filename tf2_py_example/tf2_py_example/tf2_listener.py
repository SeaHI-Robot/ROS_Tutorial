import rclpy
from rclpy.node import Node

from tf2_ros import TransformException
from tf2_ros.buffer import Buffer
from tf2_ros.transform_listener import TransformListener



class FrameListener(Node):

    def __init__(self):
        super().__init__('tf2_frame_listener')

        # Declare and acquire `target_frame` and `source_frame` parameter
        self.base_frame = self.declare_parameter('arm_base_frame', 'px100/base_link').get_parameter_value().string_value
        self.ee_frame = self.declare_parameter('arm_ee_frame', 'px100/ee_gripper_link').get_parameter_value().string_value

        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)
        
        # Call on_timer function every second
        self.timer = self.create_timer(1.0, self.on_timer)

    def on_timer(self):
        t = self.tf_buffer.lookup_transform(
                self.base_frame,
                self.ee_frame,
                rclpy.time.Time())
        self.get_logger().info('translation: {} \nrotation: {}'.format(t.transform.translation, t.transform.rotation))

def main():
    rclpy.init()
    node = FrameListener()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass

    rclpy.shutdown()

if __name__ == "__main__":
    main()
