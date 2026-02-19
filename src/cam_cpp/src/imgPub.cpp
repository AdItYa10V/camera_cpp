#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>

class ImagePublisher : public rclcpp::Node {
public:
    ImagePublisher() : Node("imgPub") {
        publisher_ = this->create_publisher<sensor_msgs::msg::Image>("img_feed", 10);
        cap_.open(0);
        timer_ = this->create_wall_timer(std::chrono::milliseconds(33), std::bind(&ImagePublisher::timer_callback, this));
    }

private:
    void timer_callback() {
        cv::Mat frame;
        cap_ >> frame;
        if (!frame.empty()) {
            auto msg = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", frame).toImageMsg();
            publisher_->publish(*msg);
        }
    }
    cv::VideoCapture cap_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ImagePublisher>());
    rclcpp::shutdown();
    return 0;
}
