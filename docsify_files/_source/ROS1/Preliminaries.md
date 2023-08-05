# Hello ROS！



此tutorial 基于ubuntu 20.04 ros noetic。在 ros1 的众多版本中，推荐使用 noetic，因为 noetic 是 ros1 的最后一个版本，性能最稳定，可以认为noetic就是ros1的完全体。



[ROS 官网](https://ros.org/)

[ROS wiki](http://wiki.ros.org/)

[ROS packages 官方指南，在这里查找ROS提供的包的详细信息](https://index.ros.org/)

---



## ROS 安装

自行了解，互联网大把的资料

---





## 创建你的catkin工作空间

catkin是ros1中的最成熟也是最主流的开发编译系统，你的ros开发即将始于catkin。

```
$ mkdir -p ~/catkin_ws/src       
$ cd ~/catkin_ws/
$ catkin_make
```

以上我们初始化了一个采用catkin编译系统的ROS的workspace。

初次运行catkin_make会在src中创建CMakeLIST.txt文件。





接下来需要用到这个工作空间时，进行`$ source ~catkin_ws/devel/setup.bash`，便把该工作空间添加到了ROS包的路径中，可通过下面的指令检测时候添加成功:

```
$ echo $ROS_PACKAGE_PATH
```

![image-20220921105438149](https://gitee.com/SeaHIPage/My_Pics/raw/master/from_ubuntu/image-20220921105438149.png)



