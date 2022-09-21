//c++
#include <iostream>
#include <string>
#include <stdlib.h>

//ros
#include <ros/ros.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <std_msgs/Int32.h>
#include <std_msgs/String.h>

int main(int argc, char** argv){
    ros::init(argc, argv, "demo_bag_read");
    ros::NodeHandle nh;

    std::string home_path = getenv("HOME");

    rosbag::Bag bag;
    std::string bag_path = home_path+"/test_bag.bag";
    bag.open(bag_path, rosbag::bagmode::Read);

    std::string chatter_topic = "chatter";
    std::string number_topic = "numbers";
    std::string test_topic = "numbers_test";

    std::vector<std::string> topics;
    topics.push_back(chatter_topic);
    topics.push_back(number_topic);
    topics.push_back(test_topic);

    rosbag::View view(bag, rosbag::TopicQuery(topics));

    std::cout << "bag is readed in "+bag_path<< std::endl;

    for(auto itr = view.begin();itr!=view.end();itr++)
    {
        if (itr->getTopic() == chatter_topic || ("/" + itr->getTopic() == chatter_topic))
        {
            std_msgs::String::ConstPtr s_ptr = itr->instantiate<std_msgs::String>();
            if (s_ptr != NULL)  
                std::cout << s_ptr->data << std::endl;
        }

        if (itr->getTopic() == number_topic || ("/" + itr->getTopic() == number_topic))
        {
            std_msgs::Int32::ConstPtr i_ptr = itr->instantiate<std_msgs::Int32>();
            if (i_ptr != NULL)
                std::cout << i_ptr->data << std::endl;
        }

        if (itr->getTopic() == test_topic || ("/" + itr->getTopic() == test_topic))
        {
            std_msgs::Int32::ConstPtr i_ptr = itr->instantiate<std_msgs::Int32>();
            if (i_ptr != NULL)
                std::cout << i_ptr->data << std::endl;
        }
    }

    bag.close();

    return 0;
}