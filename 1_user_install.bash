#!/bin/bash
sudo apt install openssh-server
sudo systemctl enable ssh.service

sudo useradd -md rom
echo "User name : rom"
echo "Enter password : "
passwd rom

sudo userdel -rf ubuntu
reboot
