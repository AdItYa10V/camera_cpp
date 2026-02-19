cmake_minimum_required(VERSION 3.8)
project(cam_cpp)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)

# Executable 1: Publisher
add_executable(imgPub src/imgPub.cpp)
target_link_libraries(imgPub ${OpenCV_LIBRARIES})
ament_target_dependencies(imgPub rclcpp sensor_msgs cv_bridge)

# Executable 2: Subscriber
add_executable(imgSub src/imgSub.cpp)
target_link_libraries(imgSub ${OpenCV_LIBRARIES})
ament_target_dependencies(imgSub rclcpp sensor_msgs cv_bridge)

# Install logic
install(TARGETS imgPub imgSub
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME})

ament_package()
