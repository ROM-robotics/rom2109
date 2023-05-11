## description package

အခု robot model ကို solidwork ဖြင့် design ဆွဲပြီး ros2 humble version ဖြင့် အသုံးပြုနိုင်သည်။ urdf ကို xacro ပုံစံပြောင်းထားပြီး rom2109_core.xacro သည် အဓိက ဖိုင်ဖြစ်ပါသည်။ simulation အတွက် camera xacro ဖိုင်နှစ်ခုထဲက နှစ်သက်ရာ အသုံးပြုနိင်သလို robot simulation controller အဖြစ် gazebo_control နှင့် gazebo_ros2_control နှစ်မျိုးရှိပြီး နှစ်သက်ရာအသုံးပြုနိုင်သည်။
gazebo_ros2_control သည် latest technology ဖြစ်တာမို့ သူ့ကိုပဲဦစားပေးအသုံးပြုသင့်သည်။ Real robot အတွက် hw_ros2_control.xacro ကို အသုံးပြုရမှာဖြစ်ပြီး လက်ရှိ implement မလုပ်ရသေးပါ။

#### urdf သက်သက်အသုံးပြုခြင်း
သင်ကိုယ်တိုင် simulation, hardware စနစ်များတပ်ဆင်မယ်ဆိုရင်တော့ အောက်ပါ launch ဖိုင်ကို run ပါ။ ဒါဆိုရင်တော့ robot_state_publisher, rviz , urdf နဲ့ robot_state_publisher, joint_state_publisher တို့ကို run ပါလိမ့်မယ်။ joint_state_publisher  ကိုတော့ လိုမှ run ပါ။
```
ros2 launch rom2109_description example_description.launch.py
```

#### gazebo နဲ့ တွဲသုံးချင်ရင် gazebo simulation time ကို အသုံးပြုပါ။
gazebo simulator နဲ့ တွဲပြီးအသုံးပြုမယ်ဆိုရင်တော့ description_xacro_sim_ros2_control.launch သို့မဟုတ် description_xacro_sim_gz_control.launch ကို အသုံးပြုနိုင်ပါတယ်။ ros2_control ကို အသုံးပြုသင့်ပါတယ်။ simulation ပြုလုပ်မှာမို့ ros2 node များသည် system time ကို အသုံးမပြုပဲ Gazebo time ကို အသုံးပြုသင့်တာမို့ use_sim_time ကို true ပေးပြီး run ပါ။ ပြီးရင် gazebo simulator ကို ဖွင့်ပါ။ ပြီးရင် simulator ထဲ robot ကို spawn လုပ်ပြီးထည့်ပါ။
```
ros2 launch rom2109_description description_xacro_sim_ros2_control.launch use_sim_time:=true
ros2 launch gazebo_ros gazebo.launch.py
ros2 launch gazebo_ros spawn_entity.py -topic robot_description -entity rom2109
```

#### rom2109_gazebo 
အဲ့လို ၃ ခု run ရတာ အဆင်မပြေဘူးထင်ရင် rom2109_gazebo package ထဲက အောက်ပါ launch ဖိုင်ကို run ပါ။
```
ros2 launch rom2109_gazebo rom2109_sim_ros2_control.launch.py
```
ဒါမှမဟုတ် 
```
ros2 launch rom2109_gazebo rom2109_sim_gz_control.launch.py
```