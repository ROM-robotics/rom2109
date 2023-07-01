#!/bin/bash
#sudo apt install openssh-server
#sudo systemctl enable ssh.service

sudo useradd -m rom
echo "User name : rom"
echo "Enter password : "
echo "Password: robotics"
sudo passwd rom
sudo usermod -aG sudo rom
sudo usermod -s /bin/bash rom
echo "Enter password"
su rom
sudo userdel -rf ubuntu
sudo reboot
