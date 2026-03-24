#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include <opencv2/opencv.hpp>

namespace multi_stage {

class Producer : public rclcpp::Node {
public:
    Producer(const rclcpp::NodeOptions & options);
private:
    void timer_callback();
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    cv::VideoCapture cap_; 
};

class Processor : public rclcpp::Node {
public:
    Processor(const rclcpp::NodeOptions & options);
private:
    void callback(const sensor_msgs::msg::Image::SharedPtr msg); 
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr sub_; 
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr pub_;    
    cv::CascadeClassifier face_cascade_;  
};

class Display : public rclcpp::Node {
public:
    Display(const rclcpp::NodeOptions & options);
private:
    void callback(const sensor_msgs::msg::Image::SharedPtr msg);
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr sub_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr pub_;
    cv::CascadeClassifier face_cascade_;
};

} // namespace multi_stage
#endif
