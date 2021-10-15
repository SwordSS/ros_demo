/**
 * 该例程将订阅chatter话题，消息类型String
 */
 
#include "ros/ros.h"
#include <std_msgs/String.h>
#include <std_msgs/String.h>

class listener
{
public:
    listener();
    ~listener(){};
private:
    void chatterCallback(const std_msgs::String::ConstPtr& msg);
    void boostCallback(const std_msgs::String::ConstPtr& msg,const int input_x,const int input_y);
private:
    ros::Subscriber chatter_sub;
    ros::Subscriber boost_sub;
    ros::NodeHandle n;
    int input_x;
    int input_y;
};

listener::listener()
    :input_x(1),input_y(2)
{
    chatter_sub = n.subscribe<std_msgs::String>("chatter", 1000, &listener::chatterCallback,this);
    boost_sub   = n.subscribe<std_msgs::String>("boost", 1000, boost::bind(&listener::boostCallback,this,_1,boost::ref(input_x),boost::ref(input_y)));
}

// 接收到订阅的消息后，会进入消息回调函数
void listener::chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  // 将接收到的消息打印出来
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}

void listener::boostCallback(const std_msgs::String::ConstPtr& msg,const int input_x,const int input_y)
{
  // 将接收到的消息打印出来
  ROS_INFO("I heard: [%s]&[%d]&[%d]", msg->data.c_str(),input_x,input_y);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  listener ltr;
  ros::spin();
  return 0;
}