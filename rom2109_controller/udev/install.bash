#!/bin/bash

echo ""
echo "          ROM ROBOTICS LTD     "
echo "      This script copies a udev rule to /etc/udev/rules.d/ "
echo "      You Can Use /home/mr_robot/robotController instead of /dev/ttyUSB* and "
echo "      You Can Use /dev/rplidar instead of /dev/ttyUSB* and "
echo ""

#sudo cp 99-rom-robot-controller.rules /etc/udev/rules.d
sudo cp rplidar.rules  /etc/udev/rules.d
sudo ln -s /dev/serial/by-id/usb-1a86_USB_Serial-if00-port0 /home/mr_robot/robotController

echo ""
echo "Restarting udev"
echo ""
sudo service udev reload
sudo service udev restart
sudo udevadm control --reload
#sudo udevadm trigger --action=change
