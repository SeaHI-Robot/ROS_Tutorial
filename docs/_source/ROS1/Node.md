# ROS Node

> 上一节我们介绍了`turtlesim`仿真器，进一步的，看看ROS最基本的component，“Node/节点”；



- 不同的节点运行不同的程序，同时节点间需要通讯，交流数据来让整个系统有机运行；

- ROS提供的 “Topic/话题” 的通讯机制，是最常用的节点间通讯方法；




## Topic / 话题
rosrun打开turtlesim_node，再打开turtle_teleop_key（上一节最后讲的操作）:


现在我们想知道，这两个节点之间怎么进行数据交流的。ROS中一个好用的可视化工具是rqt_graph！(没装rqt_graph的话要安装一下)

```
$ rqt_graph
```

![](https://gitee.com/SeaHIPage/My_Pics/raw/master/from_ubuntu/image.png)

圆圈画的为节点，你细品......



>  `/turtle1`是话题，`/cmd_vel`是运动信息，通过Topic发布的数据是在Topic下面挂着的；



你要问我为什么这么设计，我会说因为......优雅，好用；

<br>

细致讲讲Topic，Topic包含以下几个Component：

1. **发布者（Publisher）**：节点通过发布者将消息发送到特定的Topic上。一个节点可以有多个发布者，每个发布者都可以在不同时间发布不同类型的消息。*teleop_turtle* *就充当publisher角色*;
2. **订阅者（Subscriber）**：节点通过订阅者从Topic上接收消息。与发布者类似，一个节点可以有多个订阅者，每个订阅者可以接收不同类型的消息。*turtlesim就充当subscriber角色;*
3. **消息（Message）**：消息是特定类型的数据，由用户自定义。可以是常见的数据类型（如整数、浮点数等），也可以是复杂的数据结构（如数组、结构体等）。*Message的数据结构必须严格遵循ROS的规范，要么使用ROS规定的数据结构类型，如geometry_msgs, std_msgs等；同时也可以自定义数据结构，参见wiki或者自行查阅用法;*



### **Topic机制的workflow**

> 当一个节点发布消息时，它会将消息发送给`ROS Master`，并指定消息所属的`Topic`。同时，ROS Master会将这个消息的信息（包括消息类型）广播给所有的订阅者。订阅者收到广播后，可以根据消息类型进行处理。
>
> **简而言之：publisher就“嗯发”，subscriber想收哪个`Topic`的消息的话就嗯收；**
>
> 因此，常说Topic通讯机制是一种 **“一对多”** 的通讯机制；




<br>
<br>
<br>

<center>
未完待续......
</center>

<center>

Last edited on September 16, 2023.
</center>

<br>
<br>
<br>
