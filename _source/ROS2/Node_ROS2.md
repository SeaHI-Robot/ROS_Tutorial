# ROS2 Node 


> ROS2 Node的api相比ROS1改动较大，提倡使用面向对象编程的思想提高代码可维护性。 
>
>
> **Package build type in ROS2:**
> - ament_cmake: 和ros1一样的package的结构
> - ament_python: ros2中针对纯python构建的package的结构




## Using rclcpp for CPP programming

创建一个简单的cpp的package：
```bash
ros2 pkg create --build-type ament_cmake cpp_pkg --dependencies rclcpp std_msgs
```


写一个简单的publisher：
```cpp
#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;


class Talker : public rclcpp::Node
{
  public:
    Talker(): Node("talker_cpp_node"), count_(0)
    {
      publisher_ = this->create_publisher<std_msgs::msg::String>("talker_topic", 10);
      timer_ = this->create_wall_timer( 500ms, std::bind(&Talker::timer_callback, this ));
    }

  private:
    void timer_callback()
    {
      auto message = std_msgs::msg::String();
      message.data = "Hello, world! " + std::to_string(count_++);
      RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
      publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Talker>());
  rclcpp::shutdown();
  return 0;
}
```

[《ROS 2机器人开发从入门到实践》2.5.2用得到的C++新特性](https://www.bilibili.com/video/BV1CRWWeoEso/?spm_id_from=333.1007.top_right_bar_window_history.content.click&vd_source=489a733550a7c846fcce2e3eb3a683cc)]



- ROS2中，node及是一个共享指针，通过std::make_shared<Type>()模板函数创建。同时，node继承rclcpp::Node这个类。

- `#include <functional>`: functional是函数包装器的头文件。常见的函数有三种，直接定义的普通函数，类里面的成员函数，和lamda函数。包装器可以对所有函数类型进行封装，不同于python的函数decorator，c++的包装器像是在给函数起“别名”。上面的程序中的`std::bind()`函数，是安全调用成员函数的方式。

ros2写一个简单的publisher时候，采用OOP继承一个类的方式比ros1采用nodehandle操作node的方式复杂得多。采用面向对象后，cpp的代码比python的也复杂的多，也许这就是cpp的魅力吧。

Let's say上面这个代码片段的名字是talker.cpp; 进一步的，我们需要对包的CMakeLists.txt进行操作:

修改后的CMakeLists：
```cmake
cmake_minimum_required(VERSION 3.8)
project(cpp_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)


##### Look Me ! #####
add_executable(talker src/talker.cpp)

ament_target_dependencies(talker rclcpp std_msgs)

install(TARGETS
  talker
  DESTINATION lib/${PROJECT_NAME}
)
##### Look Me ! #####


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
```

和ros1或者一般的cmake构建的cpp工程类似，需要先添加可执行文件；随后一般我们要target_link_libraries()，ros2采用了新的语法，ament_target_dependencies(<exec> dependencie1 dependencie2 ...)这样对单独的可执行文件声明依赖的操作，看起来更优雅。
最后，ros2采用了install机制来安装最后生成的可执行文件，这一点和ros1有区别。而install语法端只需要声明一次，把需要的可执行文件添加进去即可，如下：
```cmake
install(TARGETS
  exec1
  exec2
  DESTINATION lib/${PROJECT_NAME}
)
```



## Using rclpy for Python programming


创建一个简单的python的package：
```bash
ros2 pkg create --build-type ament_python py_pkg --dependencies rclpy std_msgs
```

ament_python看起来就是一个纯python包的结构，使用setuptools。一般情况下，只需要在和package的一级同名文件夹下写代码就可以了，cd进入这个文件夹，可以看到有一个__init__.py的空文件，这个文件是告诉python解释器这个文件夹是一个可以import的python的package。

在py_pkg/py_pkg中新建一个文件，let's call it talker.py, 写一个简单的publisher：
```python
import rclpy
from rclpy.node import Node
import sys
from std_msgs.msg import String

class Talker(Node):
    def __init__(self):
        super().__init__("Talker")
        self.publisher = self.create_publisher(String, "talker_topic", 10)
        self.count = 0
        self.timer_ = self.create_timer(0.5, self.timer_callback)
    def timer_callback(self):
        message = String()
        message.data = "Hello ROS2，" + str(self.count)
        self.get_logger().info("Publishing:" + message.data)
        self.publisher.publish(message)
        self.count += 1
        
def main():
    rclpy.init()
    node = Talker()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()
```
可以看到，同样的在python中创建ROS2的Node也采用继承的方式，这可能和rcl底层构建有关系，可能在写rcl的时候就这么规划了。

相比于CPP的代码，用python实现一个node明显代码简单了很多。但一样的是，都需要继承rclcpp/rclpy提供的Node类。


随后，不同于ros1，我们在ros2中有了独立的python构建类型，需要多一步设置: 
在setup函数中的entry_points变量中的'console_scripts'的list中添加我们需要的脚本对应的main函数，有点像CMakeLists中add_executable()
```python
setup(
    entry_points={
        'console_scripts': [
            "talker_py = py_pkg.talker:main"
        ],
    },
)
```
其中，talker_py作为这个脚本的"可执行文件名"。（为什么有双引号，因为python不需要编译啊~）


## Launch Files in ROS2 - For ROS1 User

笔者还是喜欢ros1中的xml格式，拓展性和可读性其实不错，且即改即用，很方便。
<br>

ROS2的launch文件确实抽象了点，ROS2的launch文件提倡用python写，launch文件的源代码也是python写的，因此拓展性也更好，支持了xml和yaml写launch文件。一个package中，需要编写launch文件的话且像ros1一样让package识别launch文件，还需要在 CMakeLists / setup.py 做launch文件的声明，挺麻烦。。。。。。
- 对于`ament_cmake`，加入:
```cmake
# Install launch files.
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)
```
- 对于`ament_python`，加入:
```python
import os
from glob import glob
# Other imports ...

package_name = 'py_launch_example'

setup(
    # Other parameters ...
    data_files=[
        # ... Other data files
        # Include all launch files.
        (os.path.join('share', package_name, 'launch'), glob(os.path.join('launch', '*launch.[py]or[yaml]or[xml]'))) # ADD THIS LINE ! 用python的launch就用.py的后缀，yaml和xml同理
    ]
)
```
详细的ros2中launch的使用请参考[链接](https://docs.ros.org/en/humble/Tutorials/Intermediate/Launch/Launch-system.html#integrating-launch-files-into-ros-2-packages)

<br>

按照官方文档，推荐在package.xml中声明依赖ros2launch，不加其实也没关系，加一下可以治强迫症。
```xml
<exec_depend>ros2launch</exec_depend>
```

笔者觉得在编写launch体验上ROS2比ROS1在效率和可读性上差的不止一点半点。即便如此，笔者更喜欢沿用xml的格式写ros2的launch文件。


<br>
<br>
<br>

<center>
Created on September 1, 2024.
</center>

<br>
<br>
<br>
