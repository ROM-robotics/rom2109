#!/bin/bash

echo ""
echo "          ROM ROBOTICS LTD     "
echo ""


# DELETE user
sudo pkill -u ubuntu
sudo userdel -r ubuntu


# UPDATE, UPGRADE
echo ""
echo " ROM ROBOTICS LTD:: updating ......................................................."
echo ""
sudo apt update 


# INSTALL ROS NOETIC
echo ""
echo " ROM ROBOTICS LTD:: installing ros noetic ( base, robot, navigation) ..............."
echo ""
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
sudo apt update
sudo apt install -y ros-noetic-ros-base ros-noetic-robot ros-noetic-navigation
echo "source /opt/ros/noetic/setup.bash">> ~/.bashrc
source ~/.bashrc
sudo apt install -y python3-rosdep python3-rosinstall python3-rosinstall-generator python3-wstool build-essential
sudo rosdep init
rosdep update


# CREATE WORKSPACE
echo ""
echo " ROM ROBOTICS LTD:: Creating workspace /ROS/catkin_ws/src ........................."
echo ""
source ~/.bashrc
mkdir -p ~/ROS/catkin_ws/src
cd ~/ROS/catkin_ws/src
catkin_init_workspace
cd ~/ROS/catkin_ws
catkin_make
echo "source /home/ROS/catkin_ws/devel/setup.bash">> ~/.bashrc


# SET TIME ZONE AND REBOOT
echo ""
echo " ROM ROBOTICS LTD:: Time synchronize ........................."
echo ""
sudo timedatectl set-timezone Asia/Yangon
sudo timedatectl set-ntp true
date
# Nowaday, timedatectl is replaced with NPT, 