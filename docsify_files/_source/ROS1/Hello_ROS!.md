



# Hello ROS！



此tutorial 基于ubuntu 20.04 ros noetic。在 ros1 的众多版本中，推荐使用 noetic，因为 noetic 是 ros1 的最后一个版本，性能最稳定，可以认为noetic就是ros1的完全体。



[ROS 官网](https://ros.org/)

[ROS wiki](http://wiki.ros.org/)

[ROS packages 官方指南，在这里查找ROS提供的包的详细信息](https://index.ros.org/)

---



## ROS 安装

自行了解，互联网大把的资料

---





## Hello ROS！

> 小海龟可爱捏



### 创建你的catkin工作空间

工作空间/wrokspace是一个文件夹，在这个文件夹中，你可以进行你的ROS开发。

catkin是ros1中的最成熟也是最主流的开发编译系统，你的ros开发即将始于catkin。

```
// mkdir是linux中新建路径的指令，可以创建文件夹；
//这个指令在根目录下创建了一个名为catkin_ws的folder，并且在这个新建的folder中创建了src的folder
$ mkdir -p ~/catkin_ws/src

// cd是linux中切换路径的指令
$ cd ~/catkin_ws/

// catkin_make指令可以初始化一个catkin工作空间
$ catkin_make
```

以上我们初始化了一个采用catkin编译系统的ROS的workspace。



初次运行catkin_make会在src中创建CMakeLIST.txt文件。

![image-20230817183023138](https://gitee.com/SeaHIPage/My_Pics/raw/master/from_ubuntu/image-20230817183023138.png)

现在我们初始化了catkin_ws，但是现在ROS还没有识别到这个工作空间的路径，使用下面的指令查询ROS的路径：

```
$ echo $ROS_PACKAGE_PATH
```

![image-20230817182546186](https://gitee.com/SeaHIPage/My_Pics/raw/master/from_ubuntu/image-20230817182546186.png)

没有识别到catkin_ws， 为了添加catkin_ws到ROS的路径，我们需要在终端内执行：

```
$ source ~/catkin_ws/devel/setup.bash
```

再次`echo $ROS_PACKAGE_PATH`查询，catkin_ws已经被添加；

![image-20230817182809545](https://gitee.com/SeaHIPage/My_Pics/raw/master/from_ubuntu/image-20230817182809545.png)





**补充：**

上面在命令行中去`source` catkin_ws/devel/setup.bash的操作，是在当前的终端中把catkin_ws添加到ROS路径中，因此新开一个终端后还要使用ROS的话，就必须重新去`source`，非常麻烦。



为了不每次都在新终端里`source`，你需要打开根目录下的.bashrc文件

<img src="https://gitee.com/SeaHIPage/My_Pics/raw/master/from_ubuntu/image-20230817164032397.png" alt="image-20230817164032397" style="zoom:50%;" /> 

在里面添加`source ~/catkin_ws/devel/setup.bash`即可； 在新的终端被建立的时候都会去执行.bashrc中的内容，避免了手动输入。

![](https://gitee.com/SeaHIPage/My_Pics/raw/master/from_ubuntu/image-20230817183613767.png)





### 跑跑小海龟

为了避免枯燥，先跑一个ROS官方提供的一个有趣的样例：



确保安装了这个包：（将\<distro\>替换成你自己的ros版本）

```
$ sudo apt-get install ros-<distro>-ros-tutorials
```

1. 新建一个终端，输入`roscore`，回车运行。

> roscore是ROS1特有的，他连接所有的ROS节点，是ROS1中的“中央处理器”。ROS2采用了分布分布式架构，消灭了roscore的中心化，因此更稳定；试想你在使用ROS1，然后除了问题，roscore宕机了，那么整个系统也就G了。

2. 新建一个终端，输入`rosrun turtlesim turtlesim_node `，回车运行；这个操作打开了一个节点（node)，对应一个”TurtlSim海龟仿真器“ 。

> rosrun 指令用于启动一个ros节点；turtlesim表示这个节点所在的ROS Package，turtlesim_node则指向了你要启动的节点，节点的内容是由python写好的脚本或者编译好的C++执行文件。

3. 新建一个终端，输入`rosrun turtlesim turtle_teleop_key `，回车运行；然后你就可以通过方向建控制小海龟的移动了。

![image-20230817184831272](https://gitee.com/SeaHIPage/My_Pics/raw/master/from_ubuntu/image-20230817184831272.png)

![image-20230817190705075](https://gitee.com/SeaHIPage/My_Pics/raw/master/from_ubuntu/image-20230817190705075.png)



### 小结

