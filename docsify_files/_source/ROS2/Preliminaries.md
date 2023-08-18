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



hh



xsanxjaksbxahjbchdbkhcdnsjkcdnsjkncdsjkcndsjk

## 创建你的colcon工作空间

colcon是ros2的开发编译系统，功能更加庞大。

```
$ mkdir -p ~/colcon_ws/src       
$ cd ~/colcon_ws/
$ colcon build
```

以上我们初始化了一个采用colcon编译系统的ROS2的workspace。



接下来需要用到这个工作空间时，进行`$ source ~colcon_ws/devel/setup.bash`，便把该工作空间添加到了ROS包的路径中，可通过下面的指令检测时候添加成功:

```
$ echo $ROS_PACKAGE_PATH
```





