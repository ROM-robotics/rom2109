## differential drive controller
velocity topic ကို အနည်းဆုံး 20Hz နဲ့ publish လုပ်ပေးပါ။ 0.5s ကျော်ရင် x=0, z=0 ဖြစ်ပါတယ်။ controller ကို စမ်းရန် အောက်က command ကို run ပါ။ 
```
ros2 launch rom2109_controller rom2109.launch.py
```
wheel encoder 1 revolution ကို  စမ်းသပ်ဖို့အတွက် turtle_teleop_key node ဖြင့် မောင်းပေးပါ။
```
ros2 launch rom2109_controller test_wheel.launch.py
```


### to do
FIRMWARE ပြင်ရေးရန်<br>
<br>CONNECTION မရှိက DESIGN RPM ကို ZERO ထားရန်              ( not fixed)
<br>တနည်း USART RECEIVE မရတာနဲ့ DESIRE RPM ကို ZERO ထားပါ။    ( not fixed)