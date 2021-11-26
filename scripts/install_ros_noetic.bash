#!/bin/bash

echo ""
echo "          ROM ROBOTICS LTD     "
echo ""

# CREATE USER
sudo useradd mr_robot
sudo passwd mr_robot
sudo usermod -aG sudo mr_robot
sudo usermode -aG dialout mr_robot
su mr_robot

# UPDATE, UPGRADE
echo " ROM ROBOTICS LTD:: updating ....."
sudo apt update && sudo apt upgrade

# INSTALL ROS NOETIC
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt install curl git vim
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
sudo apt update
sudo apt install ros-noetic-ros-base
echo "source /opt/ros/noetic/setup.bash">> ~/.bashrc
source ~/.bashrc
sudo apt install python3-rosdep python3-rosinstall python3-rosinstall-generator python3-wstool build-essential
sudo rosdep init
rosdep update

# INSTALL DRIVER PACKAGES
mkdir -p ROS/catkin_ws/src
cd ROS/catkin_ws/src
catkin_init_workspace
cd ..
catkin_make
cd src
git clone https://github.com/greenghostman/rom2109.git


# SET TIME ZONE AND REBOOT
sudo timedatectl set-timezone Asia/Yangon
sudo timedatectl set-ntp true

# Nowaday, timedatectl is replaced with NPT, 