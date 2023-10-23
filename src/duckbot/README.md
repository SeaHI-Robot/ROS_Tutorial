# Duckbot

> 鸭鸭机器人，2023Fall-ME332课程中用于在ROS中学习使用URDF



## 使用说明

- 将 `duckbot` 文件夹复制到自己的工作空间src目录
- 运行 `$ rosdep install duckbot` 安装依赖项



## 补充

- 打开 `launch` 文件夹，查看 `gazebo_teleop_keyboard.launch` 文件:

  ```xml
   <node name="teleop_keyboard" pkg="teleop_twist_keyboard" type="teleop_twist_keyboard.py"/>
  ```

  这个语句启动了 `teleop_twist_keyboard`  包中的 `teleop_twist_keyboard.py` 脚本，本质上就是一个通过获取键盘输入来给 `cmd_vel` 话题发送 `Twist` 运动消息的脚本，自己写一个这个脚本也是可以的；



- 关于 Gazebo 中使用urdf的配置，可以参考：

  [Gazebo Plugins in ROS](https://classic.gazebosim.org/tutorials?tut=ros_gzplugins#SkidSteeringDrive)