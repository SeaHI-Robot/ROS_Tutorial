#include <chrono>

#include <rclcpp/rclcpp.hpp>  // For rclcpp::Clock, rclcpp::Duration and rclcpp::Time
#include <example_interfaces/msg/int32.hpp>

#include <rosbag2_cpp/writer.hpp>
#include <rosbag2_cpp/writers/sequential_writer.hpp>
#include <rosbag2_storage/serialized_bag_message.hpp>

using namespace std::chrono_literals;

int main(int, char**)
{
  example_interfaces::msg::Int32 data;
  data.data = 0;
  std::unique_ptr<rosbag2_cpp::Writer> writer_ = std::make_unique<rosbag2_cpp::Writer>();

  writer_->open("big_synthetic_bag");

  writer_->create_topic(
    {"synthetic",
     "example_interfaces/msg/Int32",
     rmw_get_serialization_format(),
     ""});

  rclcpp::Clock clock;
  rclcpp::Time time_stamp = clock.now();
  for (int32_t ii = 0; ii < 100; ++ii) {
    writer_->write(data, "synthetic", time_stamp);
    ++data.data;
    time_stamp += rclcpp::Duration(1s);
  }

  return 0;
}
