#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Spawn.h>

int main(int argc, char** argv){
    ros::init(argc, argv, "my_tf_listener");

    int scale_angular, scale_linear;    

    ros::NodeHandle nodehandle;

    nodehandle.getParam("/scale_linear", scale_linear);

    nodehandle.getParam("/scale_angular", scale_angular);
    
    ros::service::waitForService("spawn");

    ros::ServiceClient spawn_turtle = nodehandle.serviceClient<turtlesim::Spawn>("spawn");

    turtlesim::Spawn srv;

    srv.request.x = 2.0;
    srv.request.y = 2.0;


    spawn_turtle.call(srv);

    ros::Publisher turtle_vel = nodehandle.advertise<geometry_msgs::Twist>("turtle2/cmd_vel", 10);

    tf::TransformListener listener;

    ros::Rate rate(10.0);


    while(nodehandle.ok()){
        tf::StampedTransform transform;

        try{
            listener.waitForTransform("/turtle2","/carrot1",ros::Time(0),ros::Duration(3.0));
            listener.lookupTransform("/turtle2", "/carrot1", ros::Time(0), transform);

        }
        catch (tf::TransformException &ex){
            ROS_ERROR("%s", ex.what());

            ros::Duration(1.0).sleep();

            continue;

        }

        geometry_msgs::Twist vel_msg;

        vel_msg.angular.z = scale_linear * 4.0 * atan2(transform.getOrigin().y(), 
                                    transform.getOrigin().x());
        vel_msg.linear.x = scale_angular *  0.5 * sqrt(pow(transform.getOrigin().x(), 2) +
                                  pow(transform.getOrigin().y(), 2));

        turtle_vel.publish(vel_msg);

        rate.sleep();


    }

    return 0;


}