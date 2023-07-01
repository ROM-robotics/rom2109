#!/usr/bin/env python3
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument, ExecuteProcess, IncludeLaunchDescription
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch.launch_description_sources import PythonLaunchDescriptionSource

import xacro

def generate_launch_description():

    twist_mux_params = os.path.join(get_package_share_directory('rom2109_controller'), 'config', 'twist_mux.yaml')
    twist_mux_node = Node(
        package="twist_mux",
        executable="twist_mux",
        parameters=[twist_mux_params],
        remappings=[('/cmd_vel_out', '/diffbot_base_controller/cmd_vel_unstamped')]
        #remappings=[('/cmd_vel_out', '/cmd_vel')]
    )

    bot = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(
            get_package_share_directory('rom_robotics_joy'), 'launch', 'joystick.launch.py'
        )])
    )


    return LaunchDescription(
        [
            twist_mux_node,
            bot,
        ]
    )
