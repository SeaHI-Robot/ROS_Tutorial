cmake_minimum_required(VERSION 3.10)
project(xbox_joystick)

find_package(catkin REQUIRED COMPONENTS
  joy
  roscpp
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

catkin_package(
   CATKIN_DEPENDS joy roscpp
)

add_executable(xbox_teleop src/xbox_teleop.cpp)

target_link_libraries(xbox_teleop
  ${catkin_LIBRARIES}
)

