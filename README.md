### <img src="https://i.imgur.com/ct8e7T4.png" height="80" />

| ![](https://i.imgur.com/NkL8Haw.gif) | ![](https://i.imgur.com/RrEc2Cd.gif) 
|:-------------------------:|:-------------------------:|
|||

This code formulates the Trajectory Optimization Problem for floating base systems and solves it using IPOPT or SNOPT. The solutions are given as [xpp] bags and can be visualized using (http://wiki.ros.org/xpp).

**Author/Maintainer: [Alexander W. Winkler](https://awinkler.github.io/)** 

This code was developed at the [Agile and Dexterous Robotics Lab](http://www.adrl.ethz.ch/doku.php), ETH Zurich. It is currently improved at the [Robotics Systems Lab](http://www.rsl.ethz.ch/), ETH Zurich.

 [<img src="https://i.imgur.com/uCvLs2j.png" height="60" />](http://www.adrl.ethz.ch/doku.php)  &nbsp; &nbsp; &nbsp; &nbsp;    [<img src="https://i.imgur.com/aGOnNTZ.png" height="50" />](https://www.ethz.ch/en.html)



## Dependencies

[Ipopt]/[Snopt]
Install and set the path to the header and source files through global varialbes in your .bashrc through

    export IPOPT_DIR=/home/path/to/ipopt/Ipopt-3.12.4
    SNOPT_DIR=/home/path/to/snopt/snopt_lib

[ROS]  
Packages: [xpp], catkin, roscpp, tf, kdl_parser, robot_state_publisher, message_runtime, message_generation, std_msgs, geometry_msgs, sensor_msgs, rviz, rosbag, keyboard
      
    sudo apt-get install ros-[ros_distro_name]-[pkg_name]
 
[Eigen]

    sudo apt-get install libeigen3-dev


##  Bugs & Feature Requests

Please report bugs and request features using the [Issue Tracker](https://github.com/leggedrobotics/xpp/issues).

[HyQ]: https://www.iit.it/research/lines/dynamic-legged-systems
[ROS]: http://www.ros.org
[xpp]: http://wiki.ros.org/xpp
[Ipopt]: https://projects.coin-or.org/Ipopt
[Snopt]: http://www.sbsi-sol-optimize.com/asp/sol_product_snopt.htm
[rviz]: http://wiki.ros.org/rviz
[catkin tools]: http://catkin-tools.readthedocs.org/
[Eigen]: http://eigen.tuxfamily.org
[Fa2png]: http://fa2png.io/r/font-awesome/link/