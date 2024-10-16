cmake_minimum_required(VERSION 3.8)
project(action_use)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(action_define REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(rclcpp_components REQUIRED)

add_library(my_action_server SHARED src/my_action_server.cpp)
target_include_directories(my_action_server PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_compile_definitions(my_action_server PRIVATE
  "ACTION_USE_BUILDING_DLL"
)
ament_target_dependencies(my_action_server
  action_define
  rclcpp
  rclcpp_action
  rclcpp_components
)
rclcpp_components_register_node(my_action_server PLUGIN "action_use::FinonacciActionServer" EXECUTABLE fibonacci_action_server)
install(TARGETS
  my_action_server
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

add_library(my_action_client SHARED src/my_action_client.cpp)
target_include_directories(my_action_client PRIVATE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_compile_definitions(my_action_server
  PRIVATE "ACTION_USE_BUILDING_DLL"
)
ament_target_dependencies(my_action_client
  action_define
  rclcpp
  rclcpp_action
  rclcpp_components
)
rclcpp_components_register_node(my_action_client PLUGIN "action_use::FibonacciActionClient" EXECUTABLE fibonacci_action_client)
install(TARGETS
  my_action_client
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
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
