## rom2109_gazebo

#### rom2109_sim_gz_control.launch 
olhသူ့မှာ urdf, gazebo, spawn node , rviz တို့ပါဝင်ပြီးတော့ /cmd_vel နဲ့ robot ကို မောင်းလို့ရတယ်။
```
ros2 launch rom2109_gazebo rom2109_sim_gz_control.launch.py
```
gz control မသုံးချင်ရင် gz ros2 control သုံးဖို့ကတော့ အောက်ကကောင်ပေါ့။
```
ros2 launch rom2109_gazebo rom2109_sim_ros2_control.launch.py
```
သူ့မှာကတော့ urdf, gazebo, spawn, rviz တို့အပြင် gazebo  မှာ controller manager ပါလာတာမို့ သူ့အတွက် plugin တွေအဖြစ် differential driver controller နဲ့ joint state broadcaster တိုပါလာပါတယ်။ ros2 control ရဲ့ diff_drive_controller သည် velocity topic များကို ရယူပြီး wheel velocity များအဖြစ် convert လုပ်ပေးပါလိမ့်မယ်။ 
ros2_control.xacro ထဲမှာတော့ wheel diameter တို့ base width စတဲ့ကောင်တွေတော့ မှန်မှန်ကန်ကန်ထည့်ပေးထားဖို့လိုပါတယ်။ 
နောက်ပိုင်း အလုပ်ရှုပ်သက်သာအောင်လည်း twist_mux_node ကို ထည့်ပေးထားတယ်။ သူက twist_mux.yaml ထဲထည့်ထားတဲ့ command velocity topic တွေကို ပေါင်းစပ်ပြီး output topic ထုတ်ပေးတာမို့ auto သွားလို့ရသလို တပြိုင်တည်း joystick , keyboard တို့နဲ့လည်း မောင်းလို့ ရပါတယ်။ အောက်မှာ နမူနာ twist_mux.yaml ပုံစံပါ။
```
twist_mux:
  ros__parameters:
    topics:
      navigation:
        topic: cmd_vel
        timeout: 0.5
        priority: 10
      joystick:
        topic: cmd_vel_joy
        timeout: 0.5
        priority: 100
```
#### ROBOT, CONTROLLER များ SPAWN မဖြစ်ခြင်းပြသနာ
တခါတလေ Gazebo ပွင့်ဖို့ ကြာတဲအတွက် robot မရောက်လာသလို , controller manager ( ros or gazebo ) မရလာသေးတဲ့အချိန်မှာ controller spawner node များ halt ဖြစ်သွားတတ်ပါတယ်။ ဒါကြောင့် delay ခံပြီး run ချင်ရင်တော့ အောက်ကကောင်ကို စမ်းပါ။ (စမ်းသပ်ဆဲ)
```
ros2 launch rom2109_gazebo delayed_rom2109_sim_ros2_control.launch.py
```

unfinish_rom2023_sim_slam.launch.py ကတော့ စတိုင်တစ်မျိုးနဲ့ရေးထားတာ မစမ်းရေသးပါ။


##### rom2109_sim_ros2_control.launch.py မှာ
rom2109_sim.launch.py မှာ ပါတာအပြင် gazebo ros2 controller ပါဝင်ပါတယ်။ ဒါအပြင် gazebo ရဲ့ controller  manager အတွက် 
- diff_drive_controller
- joint broadcaster controller 
နှစ်ခုလဲပါဝင်ပါတယ်။ controller spawner က gazebo ထက်မြန်နေရင် spawn ဖြစ်စဥ် မအောင်မြင်နိုင်တာမို့ delay နဲနဲပါးပါးခံရေးပါ။
delay ရေးပြီးသား launch ကတော့ delay_rom2109_sim_ros2_control.launch.py ဖြစ်ပါတယ်။
delay မသုံးပဲ launch ဖိုင်ခွဲရေးထားပုံကတော့
```
ros2 launch rom2109_gazebo rom2109_sim_ros2_control.launch.py
# gazebo ပွင့်ပြီး robot spawn ဖြစ်မှာ အောက်ပါ controller ကို run ပါ။
ros2 launch rom2109_gazebo rom2109_sim_diff_controller_joint_broadcaster.launch.py
```

Controller များ load ဖြစ်မဖြစ် စစ်ချင်ရင် 
```
ros2 control list_hardware_interfaces
ros2 control list_controllers
```

controller spawner ကို cli မှစမ်းရန်
```
ros2 run controller_manager spawner diff_cont
ros2 run controller_manager spawner joint_broad
```

မောင်းနှင်ရန်
```
ros2 run teleop_twist_keyboard teleop_twist_keyboard –ros-args -r /cmd_vel:=/diff_cont/cmd_vel_unstamped 
```

<img src="maps/gz_ros2_control.png" width="613" height="299" />


<a href="https://github.com/ROM-robotics/rom2109">မူလစာမျက်နှာ </a>