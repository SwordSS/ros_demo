//c++
#include <iostream>
#include <string>
#include <stdlib.h>

//ros
#include <ros/ros.h>
#include <rosbag/bag.h>
#include <std_msgs/Int32.h>
#include <std_msgs/String.h>

int main(int argc, char** argv){
    ros::init(argc, argv, "demo_bag_write");
    ros::NodeHandle nh;//调用ros::Time::now()必须要之前有句柄存在

    std::string home_path = getenv("HOME");
    
    rosbag::Bag bag;
    std::string bag_path = home_path+"/test_bag.bag";
    bag.open(bag_path, rosbag::bagmode::Write);

    std_msgs::String chatter;
    chatter.data = std::string("foo");

    std_msgs::Int32 numbers;
    numbers.data = 42;

    std_msgs::Int32 numbers_test;
    numbers_test.data = 43;

    ros::Duration duartion;
    duartion.fromSec(1.0);

    bag.write("chatter", ros::Time::now()+duartion, chatter);
    bag.write("numbers", ros::Time::now(),numbers);
    bag.write("numbers_test", ros::Time::now(), numbers_test);

    bag.close();

    std::cout << "bag is writed in "+bag_path<< std::endl;

    return 0;
}