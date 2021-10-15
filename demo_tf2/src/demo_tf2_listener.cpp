#include <geometry_msgs/TransformStamped.h>
#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>

void transformPoint(const tf2_ros::Buffer &buffer)
{
  //坐标转换，显示转换后的坐标
  try
  {
    ros::Time past = ros::Time::now() - ros::Duration(1.0);
    ros::Time now = ros::Time::now();

    geometry_msgs::TransformStamped bf_past_T = 
    buffer.lookupTransform("odom", "base_footprint", past);

    geometry_msgs::TransformStamped bf_now_T = 
    buffer.lookupTransform("odom","base_footprint", now,ros::Duration(1.0));

    ROS_INFO("past:odom->base_footprint: x=%f,stamp=%f",
        bf_past_T.transform.translation.x,
        bf_past_T.header.stamp.toSec());

    ROS_INFO("now :odom->base_footprint: x=%f, stamp=%f",
        bf_now_T.transform.translation.x,
        bf_now_T.header.stamp.toSec());
  }
  catch (tf2::TransformException &ex)
  {
    ROS_ERROR("%s",
              ex.what());
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "tf_listener");
  ros::NodeHandle n;

  // 设置接收器
  tf2_ros::Buffer tfBuffer;
  tf2_ros::TransformListener tfListener(tfBuffer);

  // 定时获取坐标变换
  ros::Timer timer = n.createTimer(ros::Duration(0.05), boost::bind(&transformPoint, boost::ref(tfBuffer)));
  ros::spin();
}
