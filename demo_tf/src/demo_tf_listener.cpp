#include <ros/ros.h>
#include <tf/transform_listener.h>

int main(int argc, char** argv){
    ros::init(argc, argv, "demo_tf_listener");

    ros::NodeHandle n;

    tf::TransformListener listener;

    float saved_x = 0.0;
    float saved_y = 0.0;
    float saved_z = 0.0;

    float saved_rx = 0.0;
    float saved_ry = 0.0;
    float saved_rz = 0.0;
    float saved_rw = 1.0;

    ros::Rate rate(10.0);
    while (ros::ok()){
        tf::StampedTransform transform;
        try{
            ros::Time now=ros::Time::now();
            //下面两行的逻辑关系可以深究一下
            listener.waitForTransform("/world","/robot",now,ros::Duration(1.0));
            listener.lookupTransform("/world", "/robot",now, transform);
            //
            saved_x = transform.getOrigin().x();
            saved_y = transform.getOrigin().y();
            saved_z = transform.getOrigin().z();

            saved_rx = transform.getRotation().getAxis().x();
            saved_ry = transform.getRotation().getAxis().y();
            saved_rz = transform.getRotation().getAxis().z();
            saved_rw = transform.getRotation().getW();

            ROS_INFO("Transform position received is %f %f %f,rostaion received is %f,%f,%f,%f",saved_x,saved_y,saved_z,saved_rx,saved_ry,saved_rz,saved_rw);
        }
        catch (tf::TransformException ex){
            ROS_ERROR("%s",ex.what());
            ros::Duration(1.0).sleep();
        }
        rate.sleep();
    }
  return 0;
};