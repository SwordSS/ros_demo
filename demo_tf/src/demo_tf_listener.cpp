#include <ros/ros.h>
#include <tf/transform_listener.h>

int main(int argc, char** argv){
    ros::init(argc, argv, "demo_tf_listener");

    ros::NodeHandle n;

    tf::TransformListener listener;

    float saved_rx = 0.0;
    float saved_ry = 0.0;
    float saved_rz = 0.0;

    ros::Rate rate(10.0);
    while (ros::ok()){
        tf::StampedTransform transform;
        try{
            ros::Time now=ros::Time::now();
            //下面两行的逻辑关系可以深究一下
            listener.waitForTransform("world","robot",now,ros::Duration(1.0));
            listener.lookupTransform("/world", "/robot",now, transform);
            //
            saved_rx = transform.getOrigin().x();
            saved_ry = transform.getOrigin().y();
            saved_rz = transform.getOrigin().z();
            ROS_INFO("Transform rotation(RPY) received is %f %f %f",saved_rx,saved_ry,saved_rz);
        }
        catch (tf::TransformException ex){
            ROS_ERROR("%s",ex.what());
            ros::Duration(1.0).sleep();
        }

        ROS_INFO("Saved transform is %f %f %f",saved_rx,saved_ry,saved_rz);

        rate.sleep();
    }
  return 0;
};