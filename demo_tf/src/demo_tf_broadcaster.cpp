#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

int main(int argc, char** argv){
    ros::init(argc, argv, "demo_tf_broadcaster");
    static tf::TransformBroadcaster br;

    while(ros::ok())
    {
        tf::Transform transform;
        //方法1
        // transform.setOrigin( tf::Vector3(1.0, 1.0, 0.0) );
        // tf::Quaternion q;
        // q.setRPY(0, 0, 1.57);
        // transform.setRotation(q);

        //方法2
        //tf::Vector3 oriign(1,1,1);
        //tf::Matrix3x3 rotation;
        //rotation.setEulerYPR(1.57,0,0);
        //transform = tf::Transform(rotation,oriign);

        //方法3
        tf::Vector3 oriign(1,1,1);
        tf::Matrix3x3 rotation( 0,1,0,
                               -1,0,0,
                                0,0,1);
        transform = tf::Transform(rotation,oriign);

        br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "odom", "base_footprint"));
        ROS_INFO("The transform has broadcasted!");
        ros::Duration(0.05).sleep();
    }
    return 0;
};
