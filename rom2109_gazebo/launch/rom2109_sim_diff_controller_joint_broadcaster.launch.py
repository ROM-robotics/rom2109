#!/usr/bin/env python3
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    

    diff_drive_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["diff_cont"],
    )

    joint_broad_spawner = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["joint_broad"],
    )

    # twist_mux_params = os.path.join(gazebo_pkg, 'config', 'twist_mux.yaml')
    # twist_mux_node = Node(
    #     package="twist_mux",
    #     executable="twist_mux",
    #     parameters=[twist_mux_params, {'use_sim_time': True}],
    #     remappings=[('/cmd_vel_out', '/diff_cont/cmd_vel_unstamped')]
    # )

    return LaunchDescription(
        [
            diff_drive_spawner,
            joint_broad_spawner,
        ]
    )
