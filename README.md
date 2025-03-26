# The Chico Mendes Robot ambient Gazebo repository

This repository provides the ROS2 package to simulate the Chico Mendes robot ambient on Gazebo.

## Getting started

* On your workspace, clone this repository.
  ```bash
  cd ~/<your_workspace>/src
  git clone https://github.com/gaabsjrer/chico_gazebo.git
  ```
* Install dependencies.
  ```bash
  cd ~/<your_workspace>
  rosdep install --from-paths src --ignore-src -r -y
  ```
* Build it!
  ```bash
  colcon build
  ```
* Source the `setup.bash` from the `install` folder and spawn the robot.
  ```bash
  source install/setup.bash
  ros2 launch chico_gz chico_gazebo.launch.py
  ```
