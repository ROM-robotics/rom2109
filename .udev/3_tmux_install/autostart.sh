#!/bin/bash

# for graphical user interface
#gnome-terminal --full-screen -- bash -c "tmuxinator ; exec bash -i"


# for multi user target
tmuxinator start -p /home/rom/.tmuxinator.yml
exec bash -i
