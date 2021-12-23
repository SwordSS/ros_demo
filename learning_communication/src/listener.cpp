/**
 * 该例程将订阅chatter话题，消息类型String
 */
 
#include "ros/ros.h"
#include <std_msgs/String.h>

// 接收到订阅的消息后，会进入消息回调函数
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  // 将接收到的消息打印出来
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}

void boostCallback(const std_msgs::String::ConstPtr& msg,const int input_x,const int input_y)
{
  // 将接收到的消息打印出来
  ROS_INFO("I heard: [%s]&[%d]&[%d]", msg->data.c_str(),input_x,input_y);
}

int main(int argc, char **argv)
{
  // 初始化ROS节点
  ros::init(argc, argv, "listener");

  // 创建节点句柄
  ros::NodeHandle n;

  // 创建一个Subscriber，订阅名为chatter的topic，注册回调函数chatterCallback
  ros::Subscriber chatter_sub = n.subscribe<std_msgs::String>("chatter", 1000, &chatterCallback);

  int input_x = 1;
  int input_y = 2;
  // 回调函数中传递另外的参数
  ros::Subscriber boost_sub = n.subscribe<std_msgs::String>("boost", 1000, boost::bind(&boostCallback,_1,boost::ref(input_x),boost::ref(input_y)));

  // 循环等待回调函数
  ros::spin();

  return 0;
}