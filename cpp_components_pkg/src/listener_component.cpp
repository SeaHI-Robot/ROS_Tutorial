#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
using std::placeholders::_1;

namespace ros2_components_learn {
class Listener : public rclcpp::Node {
public:
  Listener(const rclcpp::NodeOptions & options) : Node("listener", options) {
    subscription_ = this->create_subscription<std_msgs::msg::String>(
        "talker_topic", 10,
        std::bind(&Listener::topic_callback, this, _1));
  }

private:
  void topic_callback(const std_msgs::msg::String &msg) const {
    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
  }
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};
} // namespace ros2_components_learn

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(ros2_components_learn::Listener)
