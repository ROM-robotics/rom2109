#!/bin/bash

echo ""
echo "          ROM ROBOTICS LTD     "
echo ""

# CREATE USER
echo " ROM ROBOTICS LTD:: Create mr_robot user ....."
sudo useradd -md /home/mr_robot mr_robot
sudo passwd mr_robot
sudo usermod -aG sudo mr_robot
sudo usermod -aG dialout mr_robot
sudo usermod -s /bin/bash mr_robot


sudo apt update 
sudo apt install -y curl git vim
sudo apt -y upgrade

# INSTALL network-manager service
sudo apt install -y network-manager
sudo nmtui
sudo hostnamectl set-hostname robot

# banner
sudo cp banner /etc/
sudo cp motd /etc/
echo "Banner /etc/banner" | sudo tee -a /etc/ssh/sshd_config > /dev/null

sudo reboot
