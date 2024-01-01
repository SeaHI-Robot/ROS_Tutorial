#include <ros/ros.h>
#include <geometry_msgs/Twist.h>


int main(int argc, char **argv){

    ros::init(argc, argv, "cmd_vel_pub");


    if (argc != 2){

        printf("You need to have a input to assigned a topic name! Like \"/turtle1/cmd_vel\" \n ");

        return -1;
    }



    ros::NodeHandle n;

    ros::Publisher pub = n.advertise<geometry_msgs::Twist>(argv[1], 1000);


    geometry_msgs::Twist msg;
    msg.linear.x = 0.5;
    msg.angular.z = 0.1;
    ros::Rate rate(30);
    ros::Rate r(10);

    while(ros::ok()){
        
        pub.publish(msg);
        
        rate.sleep();

    }

    return 0;

}