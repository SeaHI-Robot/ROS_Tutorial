#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>  // 这是一个library里面一个做好的包（simple_action_server）里面的头文件
#include "actionlib_tutorials/DoDishesAction.h"  // 这个头文件是重点，在上一部分生成的action消息的头文件
 
// 为客户端数据类型定义一个别名
typedef actionlib::SimpleActionClient<actionlib_tutorials::DoDishesAction> Client;
 
// 当服务器完成后会调用该回调函数一次
void doneCb(const actionlib::SimpleClientGoalState & state,
            const actionlib_tutorials::DoDishesResultConstPtr & result)
{
    ROS_INFO("Yay! The dishes are now clean");
    ros::shutdown();
}
 
// 当服务器激活后会调用该回调函数一次
void activeCb()
{
    ROS_INFO("Goal just went active");
}
 
// 收到feedback后调用该回调函数
void feedbackCb(const actionlib_tutorials::DoDishesFeedbackConstPtr & feedback)
{
    ROS_INFO(" percent_complete : %f ", feedback->percent_complete);
}
 
int main(int argc, char **argv)
{
    ros::init(argc, argv, "do_dishes_client");
 
    // 定义一个客户端，连接名为do_dishes的服务器，开启自循环线程
    Client client("do_dishes", true);
 
    ROS_INFO("Waiting for action server to start.");
 
    client.waitForServer();  // 客户端等待服务器函数
    // 可以传递一个ros::Duration作为最大等待值，程序进入到这个函数开始挂起等待
    // 服务器就位或者达到等待最大时间退出，前者返回true,后者返回false
 
    ROS_INFO("Action server started, sending goal.");
 
    actionlib_tutorials::DoDishesGoal goal;  // 创建一个action的goal
 
    goal.dishwasher_id = 1;  // 定义盘子的目标，也就是洗一个盘子
 
    // 发送action的goal给服务器端，并且设置回调函数
    client.sendGoal(goal, &doneCb, &activeCb, &feedbackCb);
 
    ros::spin();
 
    return 0;
}