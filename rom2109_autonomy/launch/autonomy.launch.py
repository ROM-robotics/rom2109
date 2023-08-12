import os 
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    pkg_autonomy = get_package_share_directory('rom2109_autonomy')

    auto_node_cmd = Node(
        package="rom2109_autonomy",
        executable="autonomy_node",
        name="autonomy_node",
        parameters=[{
            "location_file": os.path.join(pkg_autonomy, "config", "sim_loc.yaml")
        }],
         remappings=[('/cmd_vel', '/cmd_vel_bt')]
    )

    ld = LaunchDescription()

    ld.add_action(auto_node_cmd)

    return ld
