#include <ros/ros.h>
#include <tf2_ros/static_transform_broadcaster.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "demo_tf_broadcaster");
    //发布静态tf
    static tf2_ros::StaticTransformBroadcaster static_broadcaster;
    //发布动态tf
    static tf2_ros::TransformBroadcaster dynamic_broadcaster;

    float i = 0.0;

    ros::NodeHandle nh;

    while(ros::ok())
    {
        geometry_msgs::TransformStamped dynamic_transformStamped;
        dynamic_transformStamped.header.stamp = ros::Time::now();
        dynamic_transformStamped.header.frame_id = "odom";
        dynamic_transformStamped.child_frame_id = "base_footprint";
        dynamic_transformStamped.transform.translation.x = i;
        dynamic_transformStamped.transform.translation.y = 0;
        dynamic_transformStamped.transform.translation.z = 0;
        dynamic_transformStamped.transform.rotation.x = 0;
        dynamic_transformStamped.transform.rotation.y = 0;
        dynamic_transformStamped.transform.rotation.z = 0;
        dynamic_transformStamped.transform.rotation.w = 1;

        geometry_msgs::TransformStamped static_transformStamped;
        static_transformStamped.header.stamp = ros::Time::now();
        static_transformStamped.header.frame_id = "base_footprint";
        static_transformStamped.child_frame_id = "laser";
        static_transformStamped.transform.translation.x = 0;
        static_transformStamped.transform.translation.y = 0;
        static_transformStamped.transform.translation.z = 1;
        static_transformStamped.transform.rotation.x = 0;
        static_transformStamped.transform.rotation.z = 0;
        static_transformStamped.transform.rotation.w = 1;

        dynamic_broadcaster.sendTransform(dynamic_transformStamped);
        static_broadcaster.sendTransform(static_transformStamped);
        
        i = i + 1;
        ROS_INFO("now :odom->base_footprint: x=%f, stamp=%f",
            dynamic_transformStamped.transform.translation.x,
            dynamic_transformStamped.header.stamp.toSec());

        ROS_INFO("now :base_footprint->laser: x=%f, stamp=%f",
            static_transformStamped.transform.translation.x,
            static_transformStamped.header.stamp.toSec());
        ros::Duration(0.25).sleep();
    }
  return 0;
};