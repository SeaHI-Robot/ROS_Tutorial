#include <algorithm>
#include <memory>
#include <rclcpp/node.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/serialized_message.hpp>
#include <rclcpp/subscription.hpp>
#include <std_msgs/msg/string.hpp>

#include <rosbag2_cpp/writer.hpp>

using std::placeholders::_1;

class BagRecorder : public rclcpp::Node {
public:
  BagRecorder() : Node("bag_recorder") {
    writer_ = std::make_unique<rosbag2_cpp::Writer>();
    writer_->open("my_bag");

    subscription_ = create_subscription<std_msgs::msg::String>("chatter", 10, std::bind(&BagRecorder::topic_callback, this, _1));
  }

private:
    void topic_callback(std::shared_ptr<rclcpp::SerializedMessage> msg) const{
        rclcpp::Time time_stamp = this->now();
        writer_->write(msg, "chatter", "std_msgs/msg/String", time_stamp);
    }
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
    std::unique_ptr<rosbag2_cpp::Writer> writer_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<BagRecorder>());
    rclcpp::shutdown();
    return 0;
}
