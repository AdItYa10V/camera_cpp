#In the "src" folder are 2 ROS 2 Humble packages that serve the exact same purpose:

##Taking video from the camera, sending it through a topic to another node(in cam_cpp)/plugin(cam_cpp_components) to process and display that shit.
In my examples, I've done face detection using a haarcascade file.

##For the cam_cpp package:
There is a Python launch file that takes care of the node running. You can also run them yourself, if you're doing it for the love of the game.

##For the cam_cpp_components package:
The cam_container file has 'auto' statements that load the plugins automatically. There's also a manager component (/ComponentManager) that allows you to manually load plugins, again, for the love of the game.

Here is the link for ROS 2 Documentation:
[https://docs.ros.org/en/humble/index.html](https://docs.ros.org/en/humble/Tutorials/Intermediate/Composition.html#composition-using-launch-actions)
