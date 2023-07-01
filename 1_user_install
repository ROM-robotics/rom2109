#!/bin/bash
sudo apt install openssh-server
sudo systemctl enable ssh.service

sudo useradd -md rom
echo "Enter password for user rom"
passwd rom

sudo userdel -rf ubuntu
reboot
