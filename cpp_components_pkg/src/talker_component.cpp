#include <chrono>
#include <functional>
#include <memory>
#include <rclcpp/node_options.hpp>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

namespace ros2_components_learn {
class Talker : public rclcpp::Node {
public:
  Talker(const rclcpp::NodeOptions & options) : Node("talker", options), count_(0) {
    publisher_ =
        this->create_publisher<std_msgs::msg::String>("talker_topic", 10);
    timer_ = this->create_wall_timer(1000ms,
                                     std::bind(&Talker::timer_callback, this));
  }

private:
  void timer_callback() {
    auto message = std_msgs::msg::String();
    message.data = "Hello, world! " + std::to_string(count_++);
    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    publisher_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  size_t count_;
};
} // namespace ros2_components_learn

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(ros2_components_learn::Talker)
