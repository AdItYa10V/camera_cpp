#include "cam_cpp_components/cam.hpp"
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
 
namespace multi_stage {
 
Display::Display(const rclcpp::NodeOptions & options)
: Node("display", options)
{
    // Load face cascade classifier
    std::string xml_path =
        "/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml";
    if (!face_cascade_.load(xml_path)) {
        RCLCPP_ERROR(this->get_logger(), "Could not load classifier!");
    }
 
    // Subscribe to raw frames from the Producer
    sub_ = create_subscription<sensor_msgs::msg::Image>(
        "img_feed", 10,
        std::bind(&Display::callback, this, std::placeholders::_1));
 
    // Publish processed frames on a separate topic
    pub_ = create_publisher<sensor_msgs::msg::Image>("processed_feed", 10);
}
 
void Display::callback(const sensor_msgs::msg::Image::SharedPtr msg)
{
    // Convert ROS image to OpenCV Mat
    cv::Mat frame = cv_bridge::toCvShare(msg, "bgr8")->image;
 
    // Downscale for faster detection, convert to grayscale
    cv::Mat gray, small_frame;
    cv::resize(frame, small_frame, cv::Size(), 0.5, 0.5);
    cv::cvtColor(small_frame, gray, cv::COLOR_BGR2GRAY);
 
    // Detect faces on the downscaled image
    std::vector<cv::Rect> faces;
    face_cascade_.detectMultiScale(gray, faces, 1.3, 5);
 
    // Draw rectangles scaled back to original resolution
    for (const auto & face : faces) {
        cv::rectangle(
            frame,
            cv::Point(face.x * 2, face.y * 2),
            cv::Point((face.x + face.width) * 2, (face.y + face.height) * 2),
            cv::Scalar(0, 255, 0), 2);
    }
 
    // Display locally
    cv::imshow("C++ Webcam Feed", frame);
    cv::waitKey(1);
 
    // Publish the annotated frame
    auto out_msg = cv_bridge::CvImage(
        msg->header, "bgr8", frame).toImageMsg();
    pub_->publish(*out_msg);
}
 
}  // namespace multi_stage
 
#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(multi_stage::Display)
 
