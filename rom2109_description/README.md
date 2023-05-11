#### description package

###### gazebo နဲ့ တွဲသုံးချင်ရင် gazebo simulation time ကို အသုံးပြုပါ။
ros2 launch rom2109_description description.xacro.launch.py use_sim_time:=true

###### gazebo 
ros2 launch gazebo_ros gazebo.launch.py

###### spawn သူက robot_state_publisher ရဲ့ topic ကိုယူပါမယ်။
ros2 run gazebo_ros spawn_entity.py -topic robot_description -entity rom2109

###### အဲ့လို ၃ခု မ run ချင်ရင် rom2109_gazebo ထဲက 
ros2 launch rom2109_gazebo rom2109_sim.launch.py