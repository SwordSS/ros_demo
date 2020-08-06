#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

std::string turtle_name;

int main(int argc, char** argv){
    ros::init(argc, argv, "demo_tf_broadcaster");
    static tf::TransformBroadcaster br;

    while(ros::ok())
    {
        tf::Transform transform;
        transform.setOrigin( tf::Vector3(1.0, 1.0, 0.0) );
        tf::Quaternion q;
        q.setRPY(0, 0, 1.57);
        transform.setRotation(q);
        br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", "robot"));
        ROS_INFO("The transform has broadcasted!");
        ros::Duration(0.05).sleep();
    }
    return 0;
};