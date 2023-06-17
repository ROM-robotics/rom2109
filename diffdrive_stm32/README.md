# diffdrive_stm32

This node is designed to provide a ros2_control hardware interface for an Arduino running firmware from `ros_arduino_bridge`.
It is designed to be used with a `diff_drive_controller` from `ros2_control`.
It is expected to communicate via serial and to have two motors, each with velocity control and position/velocity feedback.




It is based on the diffbot example from [ros2_control demos](https://github.com/ros-controls/ros2_control_demos/tree/master/example_2).

For a tutorial on how to develop a hardware interface like this, check out the video below:

https://youtu.be/J02jEKawE5U



## To Do
add stm32_comms.hpp
##### ---------------- add this to diffbot_system.hpp ---------------------
```
#include "diffdrive_stm32/stm32_comms.hpp"
#include "diffdrive_stm32/wheel.hpp"
```
private: scope ထဲကအကုန်ဖျက် ဒါထည့်
```
ArduinoComms comms_;
Config cfg_;
Wheel wheel_l_;
Wheel wheel_r_;
```
struct Config ထဲက pid တန်ဖိုးတွေဖြုတ်။

##### ---------------- add this to diffbot_system.cpp ---------------------
on_activate မှာ log နှစ်ကြောင်းရယ် return ရယ်ပဲချန်အကုန်ဖျက်ပြီးဒါထည့်
```
//comms_.connect();
```
on_deactivate မှာ log နှစ်ကြောင်းရယ် returnရယ်ပဲချန်အကုန်ဖျက်ပြီးဒါထည့်
```
//comms_.disconnect();
```
read() မှာreturn ပဲချန်အကုန်ဖျက်ပြီးဒါထည့်
```
//comms_.read_encoder_values();
```
write() မှာreturn ပဲချန်အကုန်ဖျက်ပြီးဒါထည့်
```
//comms_.set_motor_values();
```
on_init() ထဲမှာ structure Config ထဲက var တွေကို assign ထပ်လုပ်ပေး။ သူက description ထဲက ros2_control.xacro ကို string to double , string to int ပြောင်းပြီး ဖတ်မှာ။ 
```
cfg_.left_wheel_name = info_.hardware_parameters["left_wheel_name"];
cfg_.right_wheel_name = info_.hardware_parameters["right_wheel_name"];
cfg_.loop_rate = std::stof(info_.hardware_parameters["loop_rate"]);
cfg_.device = info_.hardware_parameters["device"];
cfg_.baud_rate = std::stoi(info_.hardware_parameters["baud_rate"]);
cfg_.timeout_ms = std::stoi(info_.hardware_parameters["timeout_ms"]);
cfg_.enc_counts_per_rev = std::stoi(info_.hardware_parameters["enc_counts_per_rev"]);
```
and so on..

##### Renaming 1
visibility_control.h ကို သွားပြီး right pane မှာ 
ROS2_CONTROL_DEMO_EXAMPLE_2 ကို CONTROL+SHIFT+F နဲ့ရှာ CASE SENSTIVE ကိုနှိပ်
FILTER TO က workspace/src/
DIFFDRIVE_STM32 နဲ့ replace လုပ်ပါ။

##### Renaming 2
diffbot_system.hpp ကို သွားပြီး ros2_control_demo_example_2 နဲ့ 
diffdrive_stm32 နဲ့ အပေါ်ကအတိုင်း အစားထိုးပါ။

##### Renaming 3
ပြီးရင် diffbot_system.hpp ထဲက class name ဖြစ်တဲ့ 
DiffBotSystemHardware ကို DiffDriveStm32Hardware နဲ့အပေါ်ကအတိုင်း အစားထိုး

##### Renaming 4
ပြီးရင် hardware/include directory ထဲက ros2_control_demo_example_2 dir ကို diffdrive_stm32 နဲ့အစားထိုး

##### Renaming 5
workspace/src ထဲက pkg name example_2 ကိုလည်း diffdrive_stm32 လို့ rename 

##### Renaming 6
ros2_control_demo_example_2.xml ကိုလည်း အောက်ပါအတိုင်း rename လုပ်ပါ။
```
diffdrive_stm32.xml
```

ပြီးရင် run ကြည့်
```
ros2 launch diffdrive_stm32 diffbot.launch.py
```



# diffdrive_stm32
https://control.ros.org/master/doc/ros2_control_demos/example_2/doc/userdoc.html

