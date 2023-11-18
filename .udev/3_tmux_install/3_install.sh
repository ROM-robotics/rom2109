#!/bin/bash

###     tmux CONFIGURATION
sudo apt install -y tmux tmuxinator neofetch cowsay btop ranger
if [[ -e ~/.tmux.conf ]]
then
    rm ~/.tmux.conf
fi

cp ./.tmux.conf ~/.tmux.conf

if [[ -e ~/.tmuxinator.yml ]]
then
    rm ~/.tmuxinator.yml
fi

cp ./.tmuxinator.yml ~/
echo "Now, you can run tmuxinator from $HOME/ directory."

cp ./autostart.sh ~/
chmod +x ~/autostart.sh
echo "Copying autostart.sh to $HOME/"

echo "Copying enable_gui, disable_gui scrpts to $HOME/"
cp ./enable_gui ./disable_gui ~/


echo "Please add startup script"
echo "Example"
echo "$ crontab -e"
echo "@reboot /home/username/autostart.sh"
