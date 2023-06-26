## differential drive controller
velocity topic ကို အနည်းဆုံး 20Hz နဲ့ publish လုပ်ပေးပါ။ 0.5s ကျော်ရင် x=0, z=0 ဖြစ်ပါတယ်။ controller ကို စမ်းရန် အောက်က command ကို run ပါ။ 
```
ros2 launch rom2109_controller rom2109.launch.py
```
velocity စမ်းသပ်ဖို့အတွက် turtle_teleop_key node ဖြင့် မောင်းပေးပါ။
```
ros2 run turtlesim turtle_teleop_key --ros-args --remap /turtle1/cmd_vel:=/diffbot_base_controller/cmd_vel_unstamped
```
ဒါမှမဟုတ် topic publish လုပ်ပြီး မောင်းပါ။
```
ros2 topic pub -r 20 /diffbot_base_controller/cmd_vel_unstamped geometry_msgs/msg/Twist "linear:
  x: 0.1
  y: 0.0
  z: 0.0
angular:
  x: 0.0
  y: 0.0
  z: 0.0
"
```
ရပ်ဖို့အတွက်ဆိုရင် velocity ကို zero ပေးပါ။
```
ros2 topic pub -r 10 /diffbot_base_controller/cmd_vel_unstamped geometry_msgs/msg/Twist "linear:
  x: 0.0
  y: 0.0
  z: 0.0
angular:
  x: 0.0
  y: 0.0
  z: 0.0
"
```
အထက်ပါ command များဖြင့် robot ရွေ့လျားပါက အောက်ပါအတိုင်း rviz ဖွင့်ရ စစ်ဆေးပါ။

### to do
FIRMWARE ပြင်ရေးရန်<br>
<br>CONNECTION မရှိက DESIGN RPM ကို ZERO ထားရန်              (fixed)
<br>တနည်း USART RECEIVE မရတာနဲ့ DESIRE RPM ကို ZERO ထားပါ။    (fixed)