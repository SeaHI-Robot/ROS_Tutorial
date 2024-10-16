import rclpy
from rclpy.action import ActionClient
from rclpy.node import Node
from rclpy.logging import get_logger

from action_tutorials_interfaces.action import Fibonacci


class FibonacciActionClient(Node):

    def __init__(self):
        super().__init__('fibonacci_action_client')
        self._action_client = ActionClient(self, Fibonacci, 'fibonacci')

    def send_goal(self, order):
        goal_msg = Fibonacci.Goal()
        goal_msg.order = order

        self._action_client.wait_for_server()

        return self._action_client.send_goal_async(goal_msg)


def main(args=None):
    rclpy.init(args=args)

    action_client = FibonacciActionClient()

    future = action_client.send_goal(order=10)

    get_logger('my_loggger').info('Goal Sended......\n')

    rclpy.spin_until_future_complete(action_client, future)


if __name__ == '__main__':
    main()
