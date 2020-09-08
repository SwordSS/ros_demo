#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <sensor_msgs/Image.h>
#include <string>
#include <vector>

void ImageCallback(const sensor_msgs::ImageConstPtr& Image_)
{
    cv_bridge::CvImageConstPtr cv_ptrImage;
    try
    {
        cv_ptrImage = cv_bridge::toCvShare(Image_);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }

    cv::Mat img;
    img = cv_ptrImage->image.clone();

    cv::imshow("img",img);
    cv::waitKey(1);
}

int main(int argc,char** argv)
{
    ros::init(argc, argv, "demo_cv_bridge");
    ros::NodeHandle n;
    ros::NodeHandle pn("~");

    std::string image_topic;
    pn.param<std::string>("image_topic",image_topic,"");

    if(image_topic=="")
    {
        ROS_ERROR_STREAM("image_topic is empty!");
        return 0;
    }

    ros::Subscriber sub = n.subscribe(image_topic.c_str(),5,ImageCallback);
    
    ros::spin();

    return 0;
}