#include <chrono>
#include <custom_msg_srv_pkg/msg/detail/my_sphere_msg__struct.hpp>
#include <functional>
#include <memory>
#include <rclcpp/logger.hpp>
#include <rclcpp/logging.hpp>
#include <string>

#include "custom_msg_srv_pkg/msg/my_num_msg.hpp"
#include "custom_msg_srv_pkg/msg/my_sphere_msg.hpp"
#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

class MyMsgPublisherNode : public rclcpp::Node {
public:
  MyMsgPublisherNode() : Node("my_msg_publisher_node") {
    publisher_1_ = this->create_publisher<custom_msg_srv_pkg::msg::MyNumMsg>(
        "my_num_msg_topic", 10);
    publisher_2_ = this->create_publisher<custom_msg_srv_pkg::msg::MySphereMsg>(
        "my_sphere_msg_topic", 10);
    timer_ = this->create_wall_timer(
        1000ms, std::bind(&MyMsgPublisherNode::timer_callback, this));
  }

private:
  void timer_callback() {
    auto message_1 = custom_msg_srv_pkg::msg::MyNumMsg();
    auto message_2 = custom_msg_srv_pkg::msg::MySphereMsg();
    message_1.num = 100;
    message_2.center.x = 1;
    message_2.center.y = 2;
    message_2.center.z = 3;
    message_2.radius = 20;
    publisher_1_->publish(message_1);
    publisher_2_->publish(message_2);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<custom_msg_srv_pkg::msg::MyNumMsg>::SharedPtr publisher_1_;
  rclcpp::Publisher<custom_msg_srv_pkg::msg::MySphereMsg>::SharedPtr
      publisher_2_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"),
              "Publishing MyNumMsg and MySphereMsg, check "
              "the ros2 topics...\n");
  rclcpp::spin(std::make_shared<MyMsgPublisherNode>());

  rclcpp::shutdown();
  return 0;
}
