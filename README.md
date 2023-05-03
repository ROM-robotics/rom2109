#### rom2109 Autonomous Mobile Robot

###### ROS2 humble အတွက် simulation package

$ sudo apt install -y ros-humble-gazebo-ros* <br>
$ sudo apt install -y ros-humble-ros2-control* <br>
$ sudo apt install -y ros-humble-controller-* <br>

<img src="images/bot.png" width="613" height="299" />
- spawn ရရန် ~/.gazebo/models/ ထဲသို့ rom2109_tall , rom2109_bot နှင့် သက်ဆိုင်ရာ robot_description package ကိုထည့်ပါ။ <br>
(( rom2109_bot, rom2109_tall ကို gz sdf convert လုပ်ခြင်း သို့မဟုတ် ros1 gazebo ဖြင့် urdf ကို spawn လုပ်ပြီး save as world ဖြင့် သက်ဆိုင်ရာ sdf ကို ရရှိနိင်သည်။ အဲ့ဒီ world သို့မဟုတ် sdf ထဲက link, joint များပါသော \<model> ... \</model> ကို sdf  ထဲ save ပြီး ~/.gazebo/models/ ထဲထည့်သွင်းထားခြင်းဖြစ်သည်။ ကိုယ်တိုင် robot ကို design ဆွဲထားပါက sdf ထဲက <uri>model://your_package/meshes/.. များကို path မှန်/ မမှန် စစ်ဆေးပါ။ )) <br>

<img src="images/dog_and_tall.png" width="619" height="330" />
- မူလ urdf တွင် gazebo plugin ( laser, differential ) များပါဝင်ပြီး မစမ်းသပ်ရေသးသော်လည်း differential plugin များမှ leftJoint --> left_joint, rightJoint --> right_joint, wheelDiameter --> wheel_diameter , wheelSeparation --> wheel_separation စသည့် spawner error များကို ရှင်းပြီးဖြစ်သည်။ 

- spawner ကို launch ဖိုင်မှခေါ်ရာတွင် position argument စတိုင်မှာ "-x", "0.0" အား "-x", '0.0' စသဖြင့်အသုံးပြုပါ။

- sensor အားလုံးအဆင်ပြေ။ SLAM မစမ်းရေသး

<img src="images/orange_bot.png" width="619" height="330" />
- rom2109_tall ကို ကိုပြည့်စုံအောင် design ဆွဲပြီး rom2109_bot ကို ကိုစည်သူရဲထွန်း design ဆွဲပြီး မြန်မာပြည်တွင် တပ်ဆင်သည်။
