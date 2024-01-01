#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <turtlesim/Pose.h>

std::string turtle_name;



void poseCallback(const turtlesim::PoseConstPtr& msg){
  static tf::TransformBroadcaster br;
  tf::Transform transform;
  transform.setOrigin( tf::Vector3(msg->x, msg->y, 0.0) );
  tf::Quaternion q;
  q.setRPY(0, 0, msg->theta);
  transform.setRotation(q);
  br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", turtle_name));

// This is where the real work is done. Sending a transform with a TransformBroadcaster requires four arguments.

// 1. First, we pass in the transform itself.

// 2. Now we need to give the transform being published a timestamp, we'll just stamp it with the current time, ros::Time::now().

// 3. Then, we need to pass the name of the parent frame of the link we're creating, in this case "world"

// 4. Finally, we need to pass the name of the child frame of the link we're creating, in this case this is the name of the turtle itself.

// Note: sendTransform and StampedTransform have opposite ordering of parent and child.
}


int main(int argc, char** argv){
  ros::init(argc, argv, "my_tf_broadcaster");
  if (argc != 2){ROS_ERROR("need turtle name as argument"); return -1;};
  turtle_name = argv[1];

  ros::NodeHandle node;
  ros::Subscriber sub = node.subscribe(turtle_name + "/pose", 10, &poseCallback);

  ros::spin();
  return 0;

};
