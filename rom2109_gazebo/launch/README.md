### အသိပေးစရာများ

##### rom2109_sim.launch.py က 
- description pkg ထဲက description.xacro.launch.py
- rviz
- gazebo_ros ထဲက gazebo.launch.py
- spawn node 
တို့ပါဝင်ပါတယ်။


##### rom2109_sim_ros2_control.launch.py မှာ
rom2109_sim.launch.py မှာ ပါတာအပြင် gazebo ros2 controller ပါဝင်ပါတယ်။ ဒါအပြင် gazebo ရဲ့ controller  manager အတွက် 
- diff_drive_controller
- joint broadcaster controller နှစ်ခုလဲပါဝင်ပါတယ်။ controller spawner က gazebo ထက်မြန်နေရင် spawn ဖြစ်စဥ် မအောင်မြင်နိုင်တာမို့ delay နဲနဲပါးပါးခံရေးပါ။

စမ်းချင်ရင် 
$ ros2 control list_hardware_interfaces
$ ros2 control list_controllers

controller spawner ကို cli မှစမ်းရန်
$ ros2 run controller_manager spawner diff_cont
$ ros2 run controller_manager spawner joint_broad

မောင်းနှင်ရန်
$ ros2 run teleop_twist_keyboard teleop_twist_keyboard –ros-args -r /cmd_vel:=/diff_cont/cmd_vel_unstamped 

<img src="gz_ros2_control.png" width="613" height="299" />
