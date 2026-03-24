cmake_minimum_required(VERSION 3.8)
project(cam_cpp_components)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 1. Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)

# 2. Build the Components as a shared library
add_library(multi_stage_components SHARED
  src/producer.cpp
  src/display.cpp
)
target_include_directories(multi_stage_components PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
ament_target_dependencies(multi_stage_components
  rclcpp
  rclcpp_components
  std_msgs
  sensor_msgs
  cv_bridge
)

# 3. Register the components so they can be loaded by other containers
rclcpp_components_register_node(multi_stage_components
  PLUGIN "multi_stage::Producer"
  EXECUTABLE producer_node
)


rclcpp_components_register_node(multi_stage_components
  PLUGIN "multi_stage::Display"
  EXECUTABLE display_node
)

# 4. Build the manual Container (the "brain" process)
add_executable(cam_container src/cam_container.cpp)
target_link_libraries(cam_container multi_stage_components ${OpenCV_LIBS})
ament_target_dependencies(cam_container rclcpp rclcpp_components)

# 5. Install everything
install(TARGETS
  multi_stage_components
  cam_container
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include/ DESTINATION include)

ament_package()
