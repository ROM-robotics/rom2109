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

    use_joystick = LaunchConfiguration('use_joystick')
    mapping = LaunchConfiguration('mapping')
    amcl = LaunchConfiguration('amcl')
    navigation = LaunchConfiguration('navigation')

    use_rqt_pub = LaunchConfiguration('use_rqt_pub')
    use_rviz = LaunchConfiguration('use_rviz')
    use_lidar = LaunchConfiguration('use_lidar')

    bot = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(get_package_share_directory('rom2109_controller'), 'launch', 'rom2109.launch.py')])
    )

    twist_mux = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(get_package_share_directory('rom2109_controller'), 'launch', 'twist_mux.launch.py')])
    )

    joystick_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(get_package_share_directory('rom_robotics_joy'), 'launch', 'joystick.launch.py')]),
        launch_arguments={'use_joystick': use_joystick}.items(),
        condition=IfCondition(use_joystick)
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

    lidar = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(get_package_share_directory('rom2109_controller'), 'launch', 'rplidar.launch.py')]),
        condition=IfCondition(use_lidar)
    )

    slamtoolbox_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(get_package_share_directory('rom2109_nav2'), 'launch', 'online_async_launch_mapping_launch.py')]),
        condition=IfCondition(mapping)
    )

    amcl_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(get_package_share_directory('rom2109_nav2'), 'launch', 'hw_localization_init_pose_launch.py')]),
        condition=IfCondition(amcl)
    )

    navigation_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(get_package_share_directory('rom2109_nav2'), 'launch', 'hw_navigation_launch.py')]),
        condition=IfCondition(navigation)
    )
    return LaunchDescription(
        [
            DeclareLaunchArgument('use_joystick', default_value='false', description='Use joystick or Not.'),
            DeclareLaunchArgument('mapping', default_value='false', description='Use mapping  or Not.'),
            DeclareLaunchArgument('amcl', default_value='false', description='Use Localization  or Not.'),
            DeclareLaunchArgument('navigation', default_value='false', description='Use navigation  or Not.'),
            DeclareLaunchArgument('use_rqt_pub', default_value='true', description='Use rqt publisher for velocity test.'),
            DeclareLaunchArgument('use_rviz', default_value='true', description='Use rviz.'),
            DeclareLaunchArgument('use_lidar', default_value='false', description='Use rplidar.'),
            bot,
            twist_mux,
            joystick_launch,
            rqt_publisher_node,
            rviz_node,
            lidar,
            slamtoolbox_launch,
            amcl_launch,
            navigation_launch,
        ]
    )
