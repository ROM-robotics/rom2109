## ROM2109 Robot Controller
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

ros2 launch rom2109_controller all_strart.launch.py
ros2 launch rom2109_nav2 online_async_launch_mapping_launch.py
### to do
FIRMWARE ပြင်ရေးရန်<br>
<br>CONNECTION မရှိက DESIGN RPM ကို ZERO ထားရန်              ( not fixed)
<br>တနည်း USART RECEIVE မရတာနဲ့ DESIRE RPM ကို ZERO ထားပါ။    ( not fixed)