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
echo "Run tmuxinator from home directory."
