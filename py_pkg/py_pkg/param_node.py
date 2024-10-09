import rclpy
import rclpy.node

class SimpleParamNode(rclpy.node.Node):
    def __init__(self):
        super().__init__('param_node')
        time_period = 1 
        self.timer_ = self.create_timer(time_period, self.timer_callback)
        self.declare_parameter('my_param', 'world')
    def timer_callback(self):
        my_param = self.get_parameter('my_param').get_parameter_value().string_value
        self.get_logger().info("Hello " + my_param)        

        #  my_new_param = rclpy.Parameter('my_param', rclpy.Parameter.Type.STRING, 'world')
        #  all_new_params = [my_new_param]
        #  self.set_parameters(all_new_params)

def main():
    rclpy.init()
    node = SimpleParamNode()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ ==  '__main__':
    main()

