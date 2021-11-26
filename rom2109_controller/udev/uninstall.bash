#!/bin/bash

echo ""
echo "          ROM ROBOTICS LTD     "
echo "      Uninstall"
echo "      This will remove /etc/udev/rules.d/99-rom-robot-controller.rules"
echo ""

#sudo rm /etc/udev/rules.d/99-rom-robot-controller.rules
sudo rm /etc/udev/rules.d/rplidar.rules
sudo rm /home/mr_robot/robotController

echo ""
echo "Restarting udev"
echo ""
sudo service udev reload
sudo service udev restart
sudo udevadm control --reload
#sudo udevadm trigger --action=change
