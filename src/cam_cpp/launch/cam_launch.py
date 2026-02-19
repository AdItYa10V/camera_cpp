from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        # Start the C++ Publisher
        Node(
            package='cam_cpp',
            executable='imgPub',
            name='cpp_publisher',
            output='screen'
        ),
        # Start the C++ Subscriber
        Node(
            package='cam_cpp',
            executable='imgSub',
            name='cpp_subscriber',
            output='screen'
        ),
    ])
