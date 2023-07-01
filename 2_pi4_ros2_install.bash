#!/bin/bash

locale  # check for UTF-8

sudo apt update && sudo apt install locales
sudo locale-gen en_US en_US.UTF-8
sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
export LANG=en_US.UTF-8

locale  # verify settings

sudo apt install software-properties-common
sudo add-apt-repository universe

sudo apt update && sudo apt install curl -y
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg

echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null

sudo apt update
sudo apt -y upgrade

sudo apt install -y ros-humble-ros-base
sudo apt install -y ros-dev-tools

echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc

echo "alias bb='colcon build --symlink-install && clear && source install/setup.bash'" >> ~/.bashrc
echo "alias delete_workspace='rm -rf build install log; echo \"Done\"'" >> ~/.bashrc

mkdir -p ~/ros2/workspace/src
echo "source ~/rom/ros2/workspace/install/setup.bash" >> ~/.bashrc
echo "Use ROS_DOMAIN_ID=100 on your host's .bashrc"
echo "ROS_DOMAIN_ID=100" >> ~/.bashrc
source ~/.bashrc

sudo apt install -y ros-humble-gazebo-ros* 
sudo apt install -y ros-humble-ros2-control*
sudo apt install -y ros-humble-controller-*
sudo apt install -y ros-humble-slam-toolbox ros-humble-robot-localization ros-humble-navigation2 ros-humble-nav2-bringup ros-humble-turtlebot3* ros-humble-twist-mux ros-humble-nav2*
sudo apt install -y ros-humble-gazebo-ros2-control \
ros-humble-ros2controlcli \
ros-humble-ros2-control \
ros-humble-ros2-controllers \
ros-humble-effort-controllers \
ros-humble-velocity-controllers \
ros-humble-gripper-controllers \
ros-humble-position-controllers \
ros-humble-tricycle-controller \
ros-humble-admittance-controller \
ros-humble-forward-command-controller \
ros-humble-joint-trajectory-controller \
ros-humble-rqt-joint-trajectory-controller \
ros-humble-controller-manager \
ros-humble-rqt-controller-manager \
ros-humble-hardware-interface \
ros-humble-controller-interface \
ros-humble-transmission-interface \
ros-humble-control-msgs \
ros-humble-controller-manager-msgs \
ros-humble-realtime-tools \
ros-humble-ros2-control-test-assets \
ros-humble-joint-limits \
ros-humble-joint-state-broadcaster \
ros-humble-force-torque-sensor-broadcaster \
ros-humble-force-torque-sensor-broadcaster \
ros-humble-ackermann-* \
ros-humble-imu-sensor-broadcaster 



