## rom2109 Autonomous Mobile Robot ( Start Project - Sepetmber 2021)

#### Contributors List
Min Kaung Min Lwin
Ei Kyi Phyu Khin

<a href="https://rom-robotics.gitbook.io/rom2109-amr-athonpyunilan/">Documentation </a> ကြည့်၍ လိုအပ်သော packages များ install လုပ်ပါ။

###### development မြန်ဆန်အောင် alias များအသုံးပြုပါ။
```
alias bb='colcon build --symlink-install && clear && source install/setup.bash'
alias delete_workspace='rm -rf build install log; echo "Done"'
```
<a href="https://docs.ros.org/en/galactic/Concepts/About-Domain-ID.html"> ROS_DOMAIN_ID </a>
###### To Do ( July 8 2023 )
controller pkg ထဲက z_test_2_move.launch.py နဲ့ ရှေ့နောက် ဘယ်ညာ တပါတ်စီ ပြည့်မှီအောင် စစ်ဆေးရန် ( စစ်ဆေးပြီး OK )

###### To Do ( July 9 2023 )
simulation မှ rom2109_nav2 ကို လေ့လာပြီး Hardware robot အတွက် ပြင်ဆင်ခြင်း ( စမ်းသပ်ဆဲ )

###### To Do ( July 15 )
amcl run ရာမှာ map_server  run သော်လည်း map မထွက် ( စမ်းသပ်ဆဲ )
https://github.com/ros2/rmw_cyclonedds?fbclid=IwAR3El9X7-mHpWpalkILMNVcEggj1g0cggvVd_frAhYK-zibZkcoEF3rYq6o
rmw_cyclonedds ကြောင့်လို့ပြောတယ် မစမ်းရသေး။
apt install ros-eloquent-rmw-cyclonedds-cpp
export RMW_IMPLEMENTATION=rmw_cyclonedds_cpp
ros2 doctor --report

