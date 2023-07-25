# ROM2109 Robot Controller
## 1) Tuning ပြုလုပ်ခြင်း
velocity topic ကို အနည်းဆုံး 20Hz နဲ့ publish လုပ်ပေးပါ။ 0.5s ကျော်ရင် x=0, z=0 ဖြစ်ပါတယ်။ controller ကို စမ်းရန် အောက်က command ကို run ပါ။ 
```
ros2 launch rom2109_controller rom2109.launch.py
```
wheel encoder 1 revolution ကို  စမ်းသပ်ဖို့အတွက် turtle_teleop_key node ဖြင့် မောင်းပေးပါ။
```
ros2 launch rom2109_controller z_1_wheel_test.launch.py
```
linear 1 meter နှင့် Angular 2 pi radian တို့ကို စစ်ဆေးရန်အတွက်  z_2_movement_test.launch.py တ္ငင် direction ပြင်ဆင်ပြီး အောက်ပါ တို့ကို launch  ပြုလုပ်ပါ။
```
ros2 launch rom2109_controller rom2109.launch.py
ros2 launch rom2109_controller z_1_wheel_test.launch.py
```

1 မီတာ စမ်းသပ်ခြင်းနှင့် 360 ဒီဂရီစမ်းသပ်ခြင်းပြီးပါက robot ကို စမ်းသပ် launch ပြုလုပ်နိုင်ပါသည်။ အသုံးပြုနိုင်မည့် arguments များမှာ
```
use_joystick:=true/false 
mapping:=true/false
amcl:=true/false
navigation:=true/false
use_rqt_pub:=true/false
use_rviz:=true/false
use_lidar:=true/false
```
## 2) စမ်းသပ်မောင်းနှင်ခြင်း
### အဆင့် ၁ Mapping ပြုလုပ်ခြင်း
```
ros2 launch rom2109_controller all_start.launch.py use_joystick:=true mapping:=true use_lidar:=true use_rviz:=true
```
### အဆင့် ၂ Localization ပြုလုပ်ခြင်း
```
ros2 launch rom2109_controller all_start.launch.py use_joystick:=true use_lidar:=true use_rviz:=true amcl:=true
```
### အဆင့် ၃ Navigation ပြုလုပ်ခြင်း
```
ros2 launch rom2109_controller all_start.launch.py use_joystick:=true use_lidar:=true use_rviz:=true amcl:=true navigation:=true
```
## 3) Server, Client တ္ငင်အသုံးပြုခြင်း
```
# Server ( robot computer )
ros2 launch rom2109_controller all_start.launch.py use_joystick:=true use_lidar:=true amcl:=true navigation:=true
# Client ( user computer )
ros2 launch rom2109_controller client.launch.py use_rviz:=true
```

### to do
FIRMWARE ပြင်ရေးရန်<br>
<br>CONNECTION မရှိက DESIGN RPM ကို ZERO ထားရန်              ( not fixed)
<br>တနည်း USART RECEIVE မရတာနဲ့ DESIRE RPM ကို ZERO ထားပါ။    ( not fixed)
