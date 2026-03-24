#include <memory>
#include "rclcpp/rclcpp.hpp"

#include "cam_cpp_components/cam.hpp" 
#include "rclcpp_components/component_manager.hpp"

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);

    auto exec = std::make_shared<rclcpp::executors::MultiThreadedExecutor>();
    auto options = rclcpp::NodeOptions();
    auto manager = std::make_shared<rclcpp_components::ComponentManager>(exec);

    auto producer = std::make_shared<multi_stage::Producer>(options);
    auto display = std::make_shared<multi_stage::Display>(options);
    exec->add_node(manager);
    exec->add_node(producer);
    exec->add_node(display);

    exec->spin();
    rclcpp::shutdown();
    return 0;
}
