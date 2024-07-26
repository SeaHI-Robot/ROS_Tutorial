# Hello ROS2！

此tutorial基于 ubuntu20.04 ros2 foxy。





## ROS2对比ROS1的优势？

- 稳定

- 更好的实时性
- 更好的多平台兼容性
- 商业开发都在用



[ROS 官网](https://ros.org/)

[ROS wiki](http://wiki.ros.org/)

[ROS packages 官方指南，在这里查找ROS提供的包的详细信息](https://index.ros.org/)

---



## ROS2 安装

自行了解，互联网大把的资料

---



## 创建你的colcon工作空间

colcon是ros2的开发编译系统，功能更加庞大。

```
$ mkdir -p ~/colcon_ws/src       
$ cd ~/colcon_ws/
$ colcon build
```

以上我们初始化了一个采用colcon编译系统的ROS2的workspace

![Alt text](https://gitee.com/SeaHIPage/My_Pics/raw/master/from_ubuntu/colcon_ws.png)

可以看到，`colcon`的目录和`catkin`还是有区别的；`src`文件夹还是老样子,作为开发package时候用到的目录；`build`文件夹和ROS1基本一样构建ROS软件包的中间文件和构建脚本；`install`是ros1没有的，ros2目录的setup。bash存放在这里，而ros1的目录存放在`devel`目录里；


## Hello ROS2！

> 按照惯例，入门ROS必先跑小海龟


安装turtlesim包
```
$ sudo apt install ros-foxy-turtlesim
```

从ros1到ros2，基本的一些指令有变化，如：

`roscore`  --> `被砍掉了`

`rosrun` --> `ros2 run`

`roslaunch` --> `ros2 launch`    


`rostopic` --> `ros2 topic`

`rosservice` --> `ros2 service`

`rosparam` --> `ros2 param`


直接`ros2 run`启动turtlesim包中的节点就可以愉快玩耍了；


![](https://gitee.com/SeaHIPage/My_Pics/raw/master/from_ubuntu/ros2turtle.png)


<br>
<br>
<br>

<center>
Last edited on September 17, 2023.
</center>

<br>
<br>
<br>
