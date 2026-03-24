#include "cam_cpp_components/cam.hpp"
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <std_msgs/msg/header.hpp>
 
namespace multi_stage {
 
Producer::Producer(const rclcpp::NodeOptions & options)
: Node("producer", options)
{
    publisher_ = create_publisher<sensor_msgs::msg::Image>("img_feed", 10);
 
    cap_.open(0);
    if (!cap_.isOpened()) {
        RCLCPP_ERROR(this->get_logger(), "Failed to open webcam!");
    }
 
    timer_ = create_wall_timer(
        std::chrono::milliseconds(33),
        std::bind(&Producer::timer_callback, this));
}
 
void Producer::timer_callback()
{
    cv::Mat frame;
    cap_ >> frame;
 
    if (!frame.empty()) {
        auto msg = cv_bridge::CvImage(
            std_msgs::msg::Header(), "bgr8", frame).toImageMsg();
        publisher_->publish(*msg);
    }
}
 
}  // namespace multi_stage
 
#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(multi_stage::Producer)
 
