## joy stick driver for ros2 humble
 အရင်ဆုံးလိုတာလေးတွေ install လုပ်ပါ။
```
sudo apt install ros-humble-joy*
sudo apt install joystick jstest-gtk evtest -y
```
joy stick တပ်ပြီးရင် evtest သို့မဟုတ်  jstest-gtk သို့မဟုတ် အောက်ပါ ros command များဖြင့်  joy stick  ရဲ့ button နဲ့ axis များကို စစ်ဆေးပါ။
```
evtest 
```
```
jstest-gtk
```
```
ros2 run joy joy_enumerate_devices
ros2 run joy joy_node
ros2 topic echo /joy
ros2 run joy_tester test_joy
```
နမူနာ launch ဖိုင်နှင့် joystick.yaml ကိုရေးထားတယ်။ axis များမတူရင်  yaml မှာပြင်လို့ရသလို reference လိုချင်ရင် teleop_joy pkg ထဲက config/yaml ဖိုင်များကိုယူပါ။
enable button သို့မဟုတ် turbl button ကိုနှိပ်ပြီးမှ မောင်းလို့ရပါမယ်။ Gazebo နှင့်စမ်းသပ်ရာ အဆင်ပြေသည်။ 
twist မသုံးရင် stamped velocity သုံးလိုံရတယ်။ သူ့ကျ sim time  မလိုတော့ဘူး။ အဲ့တော့ twist ကို stamped  time ပါအောင် twist_stamp node သုံးလို့ရသလို  twist unstamp လည်းသုံးလို့ရတယ်။ ခုတော့  unstamped velocity သုံးတာမို့ joystick launch မှာလည်း sim time true ပေးထားတယ်။ 

<a href="https://github.com/ROM-robotics/rom2109_simulation"> မူလစာမျက်နှာ </a>
