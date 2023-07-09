from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

from launch_ros.actions import Node


def generate_launch_description():

    # 'forward', 'reverse' for straight_node
    straight_node = Node(
        package='rom2109_controller',
        executable='go_straight',
        name='rom_robotics_go_straight_node',
        parameters=[{'direction': 'reverse'}]
    )
    # 'right', 'left' for rotate_node
    rotate_node = Node(
        package='rom2109_controller',
        executable='go_rotate',
        name='rom_robotics_go_rotate_node',
        parameters=[
            {'direction': 'right'} 
        ])
    return LaunchDescription([
        #straight_node,
        rotate_node,
    ])