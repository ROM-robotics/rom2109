#!/bin/bash

echo ""
echo "          ROM ROBOTICS LTD     "
echo ""

# UPDATE, UPGRADE
echo ""
echo " ROM ROBOTICS LTD:: updating ...................................."
echo ""
source ~/.bashrc
sudo apt update && sudo apt upgrade

# INSTALL ROS PACKAGES
echo ""
echo " ROM ROBOTICS LTD:: installing required ros packages ............"
echo ""
sudo apt install ros-noetic-depthimage-to-laserscan
# git clone 
cd ~/ROS/catkin_ws/ && catkin_make

# CONFIGURE NETWORK
echo ""
echo " ROM ROBOTICS LTD:: writing Network Setting to ~/.bashrc ........"
echo ""
echo "export ROS_IP=192.169.100.158" >> ~/.bashrc
echo "export ROS_HOSTNAME=192.168.100.158" >> ~/.bashrc
echo "export ROS_MASTER_URI=http://192.168.100.57:11311" >> ~/.bashrc

# SOURCE BASHRC
echo ""
echo " ROM ROBOTICS LTD:: sourcing .bashrc to ~/.profile .............."
echo ""
echo "if [ -f ~/.bashrc ]; then " >> ~/.profile
echo "  . ~/.bashrc " >> ~/.profile
echo "fi " >> ~/.profile

# INSTALL UDEV RULES
echo ""
echo " ROM ROBOTICS LTD:: install udev rules .........................."
echo ""
sudo cp `rospack find rom2109_controller`/udev/rplidar.rules /etc/udev/rules.d
sudo ln -s /dev/serial/by-id/usb-1a86_USB_Serial-if00-port0 ~/robotController

# COMPILE ROBOT DRIVER
echo ""
echo " ROM ROBOTICS LTD:: Trying to ROM2109 ROBOT DRIVER ..............."
echo ""
cp -r ~/rom2109 ~/ROS/catkin_ws/src
cd ~/ROS/catkin_ws/
catkin_make

