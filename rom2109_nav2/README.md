# rom2109_nav2 

##### ဒါတွေ install လုပ်ထားပါ။
```
sudo apt install ros-humble-navigation2
sudo apt install ros-humble-nav2-bringup
sudo apt install ros-humble-turtlebot3*
sudo apt install ros-humble-twist-mux ros-humble-nav2*     
sudo apt install ros-humble-robot-localization
sudo apt install -y ros-humble-slam-toolbox
```

### 1 Mapping
slamtoolbox အတွက် yaml ဖိုင်မှာ frame တွေစစ်ဆေးပြီး mapping mode မှာထားပါ။
အတုယူရေးသားဖို့ အောက်ပါတို့ကို လုပ်ပါ။ <br>
###### cp /opt/ros/humble/share/slam_toolbox/config/mapper_params_online_async.yaml your_path/ <br>
###### ros2 launch slam_toolbox online_async_launch.py params_file:=/pathto/yaml use_sim_time:=true
သို့မဟုတ် အောက်က ပြင်ဆင်ပြီးသား launch ဖိုင်ကို run ပါ။
```
ros2 launch rom2109_gazebo rom2109_sim_ros2_control.launch.py
ros2 launch rom2109_gazebo controller_spawner.launch.py
ros2 launch rom2109_nav2 online_async_launch_mapping_launch.py
```
##### rviz မှာ config ဖြစ်တဲ့ rom2109_gazebo/rviz2/slam.rviz ကို ဖွင့်ပါ။ ပြီးရင် အောက်ပါ node နဲ့ မောင်းပါ။
```
ros2 run teleop_twist_keyboard teleop_twist_keyboard /cmd_vel:=/diff_cont/cmd_vel_unstamped
```
 ပြီးရင် ပါတ်မောင်းပြီး မြေပုံကို save ပါ။
 မြေပုံ save ဖို့က 
RVIZ Panels -> add_new panel > slamtoolbox
map save ဖို့က format နှစ်မျိုးရှိတယ်။ တမျိုးက old style သူက ပြန်ဖွင့်ဖို့  map server လိုမယ်။ Serialize လုပ်ပြီးသိမ်းရင်တော့ slamtoolbox က ပြန်ဖွင့်ပေးနိုင်တယ်။

map ပြန်ထည့်ဖို့ yaml, map_server နည်း နှစ်ခုရှိပြီး yaml မှာဆိုရင် mapping ကို localization ပြောင်း , map path ထည့်ပေးပါ။ 


#### Using Map
တကယ်တော့ localization node ဆိုပေမဲ့ amcl မပါဝင်။ slamtoolbox က localization လုပ်ပေးတာဖြစ်တယ်။ တနည်းအားဖြင့် map->odom ထုတ်ပေးနေတာပေါ့။ yaml localization mode မှာထားပြီး config/mapper_params_online_async_localization.yaml ရဲ့ map_file_name မှာ serial map ကိုထည့်ပေးပါ။ ပြီးမှအောက်ပါ launch ကို run ပါ။
```
ros2 launch rom2109_nav2 online_async_launch_localization_launch.py
```
ဒါမှမဟုတ် မြေပုံသက်သက် load လုပ်ချင်ရင်
```
ros2 run nav2_util lifecycle_bringup map_server
ros2 run nav2_map_server map_server --ros-args -p yaml_filename:=my_map_old.yaml -p use_sim_time:true
```
map->odom ကို amcl ကလည်းထုတ်ပေးမှာမို့ jumping ဖြစ်နေနိုင်ပါတယ်။

### 2 Localization
sim_localization_launch.py ထဲမှာ declare_map_yaml_cmd မှာ save ထားတဲ့ map ထည့်ပြီးမှ localization node ကို run ပါ။
အခုဆိုရင် amcl localisation ကို သုံးလို့ရပါပြီ။ 
```
ros2 run nav2_util lifecycle_bringup amcl
ros2 run nav2_amcl amcl --ros-args -p use_sim_time:=true
```
ခုဆိုရင် initial pose တစ်ခုလိုတာမို့ warning ပြပါလိမ့်မယ်။ /initial_pose ကို topic နည်းလမ်းနဲ့ ပေးနိုင်သလို RVIZ ကနေ 2D Pose Estimate ကိုနှိပ်ပြီး ပေးနိုင်ပါတယ်။
RViz --> 2D Pose Estimate
amcl အဆင်ပြေပေမဲ့ robot သည် rviz တွင် jumping ဖြစ်နေတယ်။
TO FIX -> duplicate map->odom publisher

### 3 Navigation
simulation နဲ့ slam toolbox ကို run ပြီး twist_mux ကို စမ်းကြည့်ပါ။ stamped velocity ကို သုံးမယ်ဆိုရင်တော့ twist_mux သုံးစရာမလိုပါ။ run ချင်ရင်  
```
ros2 launch rom2109_gazebo rom2109_sim_ros2_control.launch.py
ros2 launch rom2109_gazebo controller_spawner.launch.py
ros2 launch rom2109_nav2 sim_localization_launch.py
ros2 launch rom2109_nav2 sim_navigation_launch.py map_subscribe_transient_local:=true
```
RViz မှာ rom2109_gazebo/rviz2/nav2_default_view.rviz ကို ဖွင့်ပါ။
အဲ့မှာ initial pose ကို rviz ကပေးမနေရအောင် code ထပ်ရေးပြီး run တယ်။ ဘာလိုဆို initial pose ကို publish လုပ်ပေးမှာ localization က map->odom ကို publish လုပ်ပေးမှာမို့လို့။ ဒါကြောင့် init_robot_pose publisher ကိုရေးပြီး sim_localization_init_pose_launch.py ထဲမှာထည့်ထားတယ်။ အဲ့တော့ init_robot_pose ပါ run ချင်ရင် 
```
ros2 launch rom2109_gazebo rom2109_sim_ros2_control.launch.py
ros2 launch rom2109_gazebo controller_spawner.launch.py
ros2 launch rom2109_nav2 sim_localization_init_pose_launch.py
# ဒါဆို ဒီအဆင့်မှာ map->odom ရပါပြီ။ 2D pose estimate နှိပ်စရာမလိုတော့။
ros2 launch rom2109_nav2 sim_navigation_launch.py map_subscribe_transient_local:=true
```

### 4 Patrol System 
နောက်တခါ Partol လှည့်ချင်တယ်ဗျာ။ ဒါကြောင့်မို့လို့
```
ros2 launch rom2109_gazebo rom2109_sim_ros2_control.launch.py
ros2 launch rom2109_gazebo controller_spawner.launch.py
ros2 launch rom2109_nav2 sim_localization_init_pose_launch.py
ros2 launch rom2109_nav2 sim_navigation_launch.py map_subscribe_transient_local:=true
ros2 launch rom2109_autonomy autonomy.launch.py
```
## Q & A
##### simulation distance 1 meter နဲ့ rviz 1m, sim rotate တပါတ်နဲ့ rviz rotate တပါတ်မတူရင် ဘယ်လိုလုပ်ရမလဲ။ ( fixed )
##### gazebo empty world တွင် 360 degree နဲ့ rviz 360 စစ်ပါ။ မတူရင် ros2_control ထဲမှာ ပြင်ဆင်ပါ။ rotate လဲစစ်ပါ။
fixed rom2109_description/config/mycontrollers.yaml , wheel_radius: 0.04355 instead of 0.035
wheel_separation: 0.21 instead of 0.1966, fixed OK
```
ros2 launch rom2109_gazebo rom2109_sim_ros2_control_empty_world.launch.py
ros2 run teleop_twist_keyboard teleop_twist_keyboard /cmd_vel:=/diff_cont/cmd_vel_unstamped
```
##### controller တခါတလေနောက်ကျ၊ တက်မလာရင် ဘယ်လိုလုပ်ရမလဲ? ( tempory fixed )
##### delay နဲ့ရေးပါ။ လတ်တလောတော့ gazebo, robot spawn သက်သက် controller သက်သက် ခွဲရေးတယ်။
```
ros2 launch rom2109_gazebo delayed_rom2109_sim_ros2_control.launch.py
```
အပေါ်က launch ဖိုင်မျာဆိုရင် controller manager နဲ့ သက်ဆိုင်ရာ controller spawner များကို launch ထားပေမဲ့ တခါတလေ spawner များ တက်မလာတာဖြစ်တတ်တယ်။ ဒါကြောင့်  controller spawner များကို launch ဖိုင်အသစ်ဖြင့် ခွဲထားပြီး အောက်ပါအတိုင်း launch ပါ။ launch ဖိုင် မခွဲချင်ရင်တော့  Delay ကို အသေးစိတ်ထပ်ရေးဖို့လိုပါတယ်။
```
ros2 launch rom2109_gazebo rom2109_sim_ros2_control.launch.py
# gazebo ပွင့်ပြီး robot spawn ဖြစ်မှာ အောက်ပါ controller ကို run ပါ။
ros2 launch rom2109_gazebo controller_spawner.launch.py
```
##### Q: Robot  ရဲ့ လက်ရှိ Pose ကို ဘယ်လိုသိနိုင်မလဲ?
##### A: ros2 topic echo /amcl_pose
##### Q: nav2_params.yaml ဖိုင် ဘယ်လိုပြောင်းရမလဲ?
```
sed -i 's/nav2_params.yaml/nav2_params_collision.yaml/g' /path/to/hw_localization_init_pose_launch.py
sed -i 's/nav2_params.yaml/nav2_params_collision.yaml/g' /path/to/hw_localization_launch.py
```
## -------------------------------------------------------------------------------------------
## ပြင်ရန်ကျန်
##### Groot နဲ့ချိတ်ရန်
##### nav2_params.yaml မှာ robot_radius, cost_scaling_factor, inflation_radius တို့ကိုပြင်ပါ။
##### rom2109_nav2 မှ init_robot_pose.cpp မှာ publisher ရဲ့ get subscription count ရယူပြီး code ပြင်ရေးရန်။





<a href="https://github.com/ROM-robotics/rom2109_simulation">မူလစာမျက်နှာ </a>