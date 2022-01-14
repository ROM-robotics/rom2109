#!/bin/bash

echo ""
echo "          ROM ROBOTICS LTD     "
echo ""

# UPDATE, UPGRADE
echo ""
echo " ROM ROBOTICS LTD:: updating ...................................."
echo ""
source ~/.bashrc
sudo apt update 

# INSTALL ROS PACKAGES
echo ""
echo " ROM ROBOTICS LTD:: installing required ros packages ............"
echo ""
sudo apt install -y ros-noetic-depthimage-to-laserscan ros-noetic-slam-toolbox*
sudo apt install -y ros-noetic-slam-gmapping ros-noetic-amcl ros-noetic-move-base*
sudo apt install -y ros-noetic-hector-slam*
# git clone 
source ~/.bashrc
cd ~/ROS/catkin_ws/src
git clone https://github.com/Slamtec/rplidar_ros.git
cd ~/ROS/catkin_ws/
catkin_make

# CONFIGURE NETWORK
echo ""
echo " ROM ROBOTICS LTD:: writing Network Setting to ~/.bashrc ........"
echo ""
echo "export ROS_IP=192.169.100.200" >> ~/.bashrc
echo "export ROS_HOSTNAME=192.168.100.200" >> ~/.bashrc
echo "export ROS_MASTER_URI=http://192.168.100.200:11311" >> ~/.bashrc

# SOURCE BASHRC
echo ""
echo " ROM ROBOTICS LTD:: sourcing .bashrc to ~/.profile .............."
echo ""
echo "if [ -f ~/.bashrc ]; then " >> ~/.profile
echo "  . ~/.bashrc " >> ~/.profile
echo "fi " >> ~/.profile



# COMPILE ROBOT DRIVER
echo ""
echo " ROM ROBOTICS LTD:: Trying to ROM2109 ROBOT DRIVER ..............."
echo ""
source ~/.bashrc
cp -r ~/rom2109 ~/ROS/catkin_ws/src
cd ~/ROS/catkin_ws/
rm -rf ~/ROS/catkin_ws/src/rom2109/rom2109_gazebo
catkin_make


# INSTALL UDEV RULES
echo ""
echo " ROM ROBOTICS LTD:: install udev rules .........................."
echo ""
source ~/.bashrc
sudo cp ~/rom2109/rom2109_controller/udev/rplidar.rules /etc/udev/rules.d
sudo ln -s /dev/serial/by-id/usb-1a86_USB_Serial-if00-port0 ~/robotController
rm -rf ~/rom2109

# i2c on ubuntu server 20.04
sudo apt install -y i2c-tools python3-pip
sudo pip3 install smbus2



sudo shutdown 0



