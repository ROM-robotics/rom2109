#!/usr/bin/env python3
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    
    twist_mux_params = os.path.join(get_package_share_directory('rom2109_controller'), 'config', 'twist_mux.yaml')
    twist_mux_node = Node(
        package="twist_mux",
        executable="twist_mux",
        parameters=[twist_mux_params],
        remappings=[('/cmd_vel_out', '/base_controller/cmd_vel_unstamped')]
        #remappings=[('/cmd_vel_out', '/cmd_vel')]
    )

    

    return LaunchDescription(
        [
            twist_mux_node,
        ]
    )
