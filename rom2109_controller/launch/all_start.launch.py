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

    bot = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(
            get_package_share_directory('rom2109_controller'), 'launch', 'rom2109.launch.py'
        )])
    )

    twist_mux = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(
            get_package_share_directory('rom2109_controller'), 'launch', 'twist_mux.launch.py'
        )])
    )

    lidar = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(
            get_package_share_directory('rom2109_controller'), 'launch', 'rplidar.launch.py'
        )])
    )


    return LaunchDescription(
        [
            bot,
            twist_mux,
        ]
    )
