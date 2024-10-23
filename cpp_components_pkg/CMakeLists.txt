cmake_minimum_required(VERSION 3.8)
project(cpp_components_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rclcpp_components REQUIRED)

add_library(talker_component SHARED src/talker_component.cpp)
ament_target_dependencies(talker_component
  rclcpp
  rclcpp_components
  std_msgs
)
rclcpp_components_register_node(
    talker_component
    PLUGIN "ros2_components_learn::Talker"
    EXECUTABLE talker
)
ament_export_targets(export_talker_component)
install(TARGETS
  talker_component
  EXPORT export_talker_component
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

add_library(listener_component SHARED src/listener_component.cpp)
ament_target_dependencies(listener_component
  rclcpp
  rclcpp_components
  std_msgs
)
rclcpp_components_register_node(
    listener_component
    PLUGIN "ros2_components_learn::Listener"
    EXECUTABLE listener
)
ament_export_targets(export_listener_component)
install(TARGETS
  listener_component
  EXPORT export_listener_component
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
# Install launch files
install(DIRECTORY
  launch
  DESTINATION share/PROJECT_NAME/
)


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
