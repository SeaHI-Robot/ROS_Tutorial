# ROS2 CLI & Colcon Build System

## ROS2 CLI

> ROS2 的cli相比ros1多了些功能，逻辑也比较清楚


[ROS2 humble Doc: CLI Tools](https://docs.ros.org/en/humble/Tutorials/Beginner-CLI-Tools.html#)


## Colcon build System

> Colocn 是ROS2使用的更加完善的工作空间构建系统, 是用python写的, 其cli风格类似catkin build, 统一了python和cpp的构建规范（虽然python作为脚本语言不用编译, 这一点确实蛋疼）。同时colcon的拓展功能包也很多，可以通过`sudo apt install python3-colcon-<blabla>`安装。
>
> [ROS2 humble Doc: Colcon](https://docs.ros.org/en/humble/Tutorials/Beginner-Client-Libraries/Colcon-Tutorial.html#install-colcon)]

### Install Colcon
[click here](https://docs.ros.org/en/humble/Installation.html)

### Usage: 在这里讲解几个基本的且最常用的几个points
[click here](https://docs.ros.org/en/humble/Tutorials/Beginner-Client-Libraries/Colcon-Tutorial.html#create-a-workspace)

#### 1. 创建工作空间
```bash
mkdir -p ~/ros2_ws/src
cd ~/ros2_ws
```


#### 2. source 工作空间
需要source install下面的setup.<shell>文件, 若终端是bash则<shell>是bash, zsh同理；
```bash
# 当前目录位于ros2_ws
source ./install/setup.bah
```

#### 3. colcon cd: 类似ros1的roscd
[click here](https://docs.ros.org/en/humble/Tutorials/Beginner-Client-Libraries/Colcon-Tutorial.html#setup-colcon-cd)
```bash
sudo apt install python3-colcon-cd
# if you use zsh, replace bash with zsh
echo "source /usr/share/colcon_cd/function/colcon_cd.sh" >> ~/.bashrc
echo "export _colcon_cd_root=/opt/ros/humble/" >> ~/.bashrc
```

#### 4. colcon autocompletion
[click here](https://docs.ros.org/en/humble/Tutorials/Beginner-Client-Libraries/Colcon-Tutorial.html#setup-colcon-tab-completion)
```bash
sudo apt install python3-colcon-argcomplete 
# if you use zsh, replace .bash with .zsh
echo "source /usr/share/colcon_argcomplete/colcon-argcomplete.bash" >> ~/.bashrc
```

#### 5. colcon build

-  直接运行`colcon build`会编译当前工作空间下所有包，也可以单独编译某个包。

```bash
colcon build --packages-select <pkg>
```

- 若使用nvim做ros2 cpp开发，需要使用clangd，同时编译的时候要导出compile_commands.json帮助clangd具备lsp功能。

```bash
colcon build --cmake-arg -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
```

- 若开发ament_python的ros2包，由于python不用编译，install的时候可以将install的目录里的python脚本文件和src中包里的源码建立软连接，使得编译更快。
```bash
colcon build --symlink-install
```






<!-- 末尾 -->
<br>
<br>
<br>

<center>
Created on September 1, 2024.
</center>

<br>
<br>
