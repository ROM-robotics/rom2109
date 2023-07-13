#!/usr/bin/env python3
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument, ExecuteProcess, IncludeLaunchDescription
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.substitutions import FindPackageShare

import xacro

def generate_launch_description():
    
    rviz_config_file = PathJoinSubstitution(
        [FindPackageShare("rom2109_controller"), "rviz", "scan.rviz"]
    )

    rviz_node = Node(
        package="rviz2",
        executable="rviz2",
        condition=IfCondition(LaunchConfiguration('use_rviz')),
        name="rviz2",
        output="log",
        arguments=["-d", rviz_config_file],
    )
    return LaunchDescription(
        [
            DeclareLaunchArgument('use_rviz', default_value='true', description='Use rviz.'),
            rviz_node,
        ]
    )
