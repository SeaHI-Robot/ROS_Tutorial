cmake_minimum_required(VERSION 3.8)
project(rosbag2_pkg_cpp)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
find_package(rclcpp REQUIRED)
find_package(rosbag2_cpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(example_interfaces REQUIRED)

add_executable(bag_recorder src/bag_recorder.cpp)
add_executable(data_generator src/data_generator.cpp)
add_executable(data_generator_and_rate_control src/data_generator_and_rate_control.cpp)
ament_target_dependencies(bag_recorder
  rclcpp
  rosbag2_cpp
  std_msgs
)
ament_target_dependencies(data_generator    
  rclcpp
  rosbag2_cpp
  example_interfaces
)
ament_target_dependencies(data_generator_and_rate_control
  rclcpp
  rosbag2_cpp
  example_interfaces
)
install(TARGETS
  bag_recorder
  data_generator
  data_generator_and_rate_control
  DESTINATION lib/${PROJECT_NAME})



if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
