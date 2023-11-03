#!/usr/bin/env python3
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument, ExecuteProcess, IncludeLaunchDescription
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration, Command, FindExecutable, PathJoinSubstitution
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.substitutions import FindPackageShare
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

    rqt_pub_node = Node(
        package='rqt_publisher',
        executable='rqt_publisher',
        name='rqt_pub'
    )

    rviz_config_file = PathJoinSubstitution(
        [FindPackageShare("stm32f1_system_interface"), "rviz", "diffbot.rviz"]
    )
    rviz_node = Node(
        package="rviz2",
        executable="rviz2",
        name="rviz2",
        output="log",
        arguments=["-d", rviz_config_file],
    )

    return LaunchDescription(
        [
            bot,
            rqt_pub_node,
            twist_mux,
            rviz_node
        ]
    )
