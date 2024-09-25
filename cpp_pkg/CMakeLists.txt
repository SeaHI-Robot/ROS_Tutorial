cmake_minimum_required(VERSION 3.8)
project(cpp_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(cpp_pkg REQUIRED)

add_executable(talker src/talker.cpp)
add_executable(listener src/listener.cpp)
add_executable(server src/service_server.cpp)
add_executable(client src/service_client.cpp)
add_executable(mymsg_publisher src/mymsg_publisher.cpp)
add_executable(mysrv_server src/mysrv_server.cpp)
add_executable(mysrv_client src/mysrv_client.cpp)

ament_target_dependencies(talker rclcpp std_msgs)
ament_target_dependencies(listener rclcpp std_msgs)
ament_target_dependencies(server rclcpp example_interfaces)
ament_target_dependencies(client rclcpp example_interfaces)
ament_target_dependencies(mymsg_publisher rclcpp cpp_pkg)
ament_target_dependencies(mysrv_server rclcpp cpp_pkg)
ament_target_dependencies(mysrv_client rclcpp cpp_pkg)

install(TARGETS
  talker
  listener
  server 
  client 
  mymsg_publisher
  mysrv_server
  mysrv_client
  DESTINATION lib/${PROJECT_NAME}
)

# Install launch files.
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

# Add custom msg and srv
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/MyNumMsg.msg"
  "msg/MySphereMsg.msg"
  "srv/AddThreeInts.srv"
  DEPENDENCIES geometry_msgs # Add packages that above messages depend on, in this case geometry_msgs for Sphere.msg
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
