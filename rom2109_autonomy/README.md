### rom2109_autonomy

clone to your ROS2 workspace
```
$ git clone git@github.com:BehaviorTree/BehaviorTree.CPP.git
$ colcon build 

$ros2 pkg create test --build--type ament_cmake --dependencies behaviortree_cpp rclcpp 
$ colcon build
```

### 4 Patrol System 
Partol လှည့်ရန်။
```
# Autonomy with Simulation Robot
ros2 launch rom2109_gazebo rom2109_sim_ros2_control.launch.py
ros2 launch rom2109_gazebo controller_spawner.launch.py
ros2 launch rom2109_nav2 sim_localization_init_pose_launch.py
ros2 launch rom2109_nav2 sim_navigation_launch.py map_subscribe_transient_local:=true
ros2 launch rom2109_autonomy autonomy.launch.py
```
```
# Autonomy with Real Robot
tmuxinator
ros2 launch rom2109_autonomy autonomy.launch.py
```

### Groot
<a href="https://zenn.dev/tasada038/articles/b7d193b567b94a">example</a>
- install groot
- edit code for zeromq publisher
- monitor with groot

###### ros2 နဲ့ groot ကို ချိတ်ဖို့ zeroMQ လိုပါတယ်။
```
sudo apt-get install libtool pkg-config build-essential autoconf automake
sudo apt-get install libzmq*
```
##### Install cmake3.2 and qt5
```
sudo apt install qtbase5-dev libqt5svg5-dev libzmq3-dev libdw-dev
```

##### Install groot
```
git clone https://github.com/BehaviorTree/Groot.git
cd Groot
git submodule update --init --recursive
mkdir build
cd build
cmake ..
make
```

<a href="https://github.com/ROM-robotics/rom2109">မူလစာမျက်နှာ </a>
