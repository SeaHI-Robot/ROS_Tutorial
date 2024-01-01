#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include "actionlib_tutorials/DoDishesAction.h"

// 为服务器数据类型定义别名
typedef actionlib::SimpleActionServer<actionlib_tutorials::DoDishesAction> Server;

// 收到action的goal后调用该回调函数
void execute_job(const actionlib_tutorials::DoDishesGoalConstPtr & goal, Server * as){

    ros::Rate r(1);
    actionlib_tutorials::DoDishesFeedback feedback;
 
    ROS_INFO("Dishwasher %d is working.", goal->dishwasher_id);
 
    // 假设洗盘子的进度，并且按照1hz的频率发布进度feedback
    for (int i = 1; i <= 10; i++)
    {
        feedback.percent_complete = i * 10;
 
	// 发布feedback
        as->publishFeedback(feedback);
 
        r.sleep();
    }
 
    // 当action完成后，向客户端返回结果
    ROS_INFO("Dishwasher %d finish working.", goal->dishwasher_id);
    as->setSucceeded();
    
}

int main(int argc, char ** argv){

    ros::init(argc, argv, "do_dishes_server");

    ROS_INFO("!!! do_dishes_server started !!!"); 

    ros::NodeHandle nh;

    // 定义服务器
    Server server(nh, "do_dishes", boost::bind(&execute_job, _1, &server), false);
    // 其中的参数n，就是NodeHandle。而“do_dishes”，是你给server起的名字
    // boost::bind(&execute, _1, &server)是当收到新的goal时候需要的返回函数
    // false的意思是暂时不启动这个server

    server.start();

    ros::spin();

    return 0;

}


