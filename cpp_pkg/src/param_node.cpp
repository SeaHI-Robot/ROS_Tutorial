#include <chrono>
#include <functional>
#include <memory>
#include <rclcpp/executors.hpp>
#include <rclcpp/node.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/timer.hpp>
#include <rclcpp/utilities.hpp>
#include <string>

using namespace std::chrono_literals;

class SimpleParamClass : public rclcpp::Node {

public:
  SimpleParamClass() : Node("param_node") {
    this->declare_parameter<std::string>("my_param", "world");
    timer_ = this->create_wall_timer(
        1000ms, std::bind(&SimpleParamClass::respond, this));
  }
  void respond() {
    this->get_parameter("my_param", param_string_);
    RCLCPP_INFO(this->get_logger(), "Hello %s", param_string_.c_str());
  }

private:
  std::string param_string_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SimpleParamClass>());
  rclcpp::shutdown();
  return 0;
}
