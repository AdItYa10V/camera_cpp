#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>

class ImageSubscriber : public rclcpp::Node {
public:
    ImageSubscriber() : Node("imgSub") {
        subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
            "img_feed", 10, std::bind(&ImageSubscriber::listener_callback, this, std::placeholders::_1));
        
        // Load the cascade once at startup
        std::string xml_path = "/usr/share/opencv4/haarcascades/haarcascade_frontalface_default.xml";
        if (!face_cascade_.load(xml_path)) {
            RCLCPP_ERROR(this->get_logger(), "Could not load classifier!");
        }
    }

private:
    void listener_callback(const sensor_msgs::msg::Image::SharedPtr msg) {
        cv::Mat frame = cv_bridge::toCvShare(msg, "bgr8")->image;
        cv::Mat gray, small_frame;

        // SPEED TRICK 1: Downscale
        cv::resize(frame, small_frame, cv::Size(), 0.5, 0.5);
        cv::cvtColor(small_frame, gray, cv::COLOR_BGR2GRAY);

        std::vector<cv::Rect> faces;
        face_cascade_.detectMultiScale(gray, faces, 1.3, 5);

        for (const auto& face : faces) {
            // Re-scale coordinates back to original size
            cv::rectangle(frame, cv::Point(face.x*2, face.y*2), 
                          cv::Point((face.x + face.width)*2, (face.y + face.height)*2), 
                          cv::Scalar(0, 255, 0), 2);
        }

        cv::imshow("C++ Webcam Feed", frame);
        cv::waitKey(1);
    }
    cv::CascadeClassifier face_cascade_;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ImageSubscriber>());
    rclcpp::shutdown();
    return 0;
}
