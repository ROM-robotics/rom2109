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

    bot = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(get_package_share_directory('rom2109_controller'), 'launch', 'rom2109.launch.py')])
    )

    twist_mux = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(get_package_share_directory('rom2109_controller'), 'launch', 'twist_mux.launch.py')])
    )

    rqt_publisher_node = Node(
        package="rqt_publisher",
        executable="rqt_publisher",
        condition=IfCondition(LaunchConfiguration('use_rqt_pub'))
    )

    rviz_config_file = PathJoinSubstitution(
        [FindPackageShare("rom2109_controller"), "rviz", "tunning.rviz"]
    )

    rviz_node = Node(
        package="rviz2",
        executable="rviz2",
        condition=IfCondition(LaunchConfiguration('use_rviz')),
        name="rviz2",
        output="log",
        arguments=["-d", rviz_config_file],
    )

    lidar = IncludeLaunchDescription(PythonLaunchDescriptionSource([os.path.join(get_package_share_directory('rom2109_controller'), 'launch', 'rplidar.launch.py')]))


    return LaunchDescription(
        [
            DeclareLaunchArgument('use_rqt_pub', default_value='false', description='Use rqt publisher for velocity test.'),
            DeclareLaunchArgument('use_rviz', default_value='true', description='Use rviz.'),
            DeclareLaunchArgument('use_lidar', default_value='false', description='Use rplidar.'),
            bot,
            twist_mux,
            rqt_publisher_node,
            rviz_node,
            lidar,
        ]
    )
