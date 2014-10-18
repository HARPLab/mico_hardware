#include <MicoRobot.h>
#include <iostream>
#include "std_msgs/String.h"
#include <sstream>

int main(int argc, char* argv[])
{
    ROS_INFO_STREAM("MICO HARDWARE starting");
  ros::init(argc, argv, "mico_hardware");
  ros::NodeHandle nh;

  MicoRobot robot(nh);
  controller_manager::ControllerManager cm(&robot);

  ros::AsyncSpinner spinner(1);
  spinner.start();

     ros::Publisher chatter_pub = nh.advertise<std_msgs::String>("chatter", 1000);

  double delta = 0;
  while (ros::ok())
  {
     robot.read();
   //  robot.pos[1];
   //     ROS_INFO_STREAM();
   //  ROS_INFO_STREAM("robot position is:");
     jaco_position_t pos = robot.returnPos();
   //  ROS_INFO_STREAM(pos.joints[2]);
   //  ROS_INFO_STREAM(pos.joints[3]);
   //  ROS_INFO_STREAM(pos.joints[4]);
   //  ROS_INFO_STREAM(pos.joints[6]);
   //  ROS_INFO_STREAM(pos.joints[7]);
     std_msgs::String msg;
     std::stringstream ss;
     ss << pos.joints[2];
     msg.data = ss.str();
    // ROS_INFO("%s", msg.data.c_str());
     chatter_pub.publish(msg);
     cm.update(robot.get_time(), robot.get_period());
     robot.write();
     sleep(0.01);
  }

  return 0;
}