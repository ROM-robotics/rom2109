## rom2109 Autonomous Mobile Robot ( Start Project - Sepetmber 2021)

#### Contributors List

```
Kaung Htet Htun
Leo
Than Zaw Toe
Min Kaung Min Lwin
pyae phyo thant
Ei Kyi Phyu Khin
Thu Ta Zaw
Zwel Myat
Htoo Tayza Aung
Min Khant Aung
Hlyan Htet Nyi Nyi
Sit Ko Naing
Phone Myint Aung
Htet Wai Yan
``````
<a href="https://rom-robotics.gitbook.io/rom2109-amr-athonpyunilan/">Documentation ကြည့်၍ လိုအပ်သော packages များ install လုပ်ပါ။ </a>  <br><br>
<a href="https://navigation.ros.org/"> Navigation 2 ကိုလေ့လာပါ။</a>  <br><br>
<a href="https://rom-robotics.gitbook.io/navigation-ii/"> Nav 2 for ROM2109 ကို ဖတ်ပါ။ </a><br><br>
<a href="https://docs.ros.org/en/galactic/Concepts/About-Domain-ID.html"> ROS_DOMAIN_ID ကို စစ်ဆေးပါ။ </a> <br>
#### pull request တင်၍ contribute လုပ်ပါ။

#### development မြန်ဆန်အောင် alias များအသုံးပြုပါ။
##### Robot computer 
```
sudo apt install -y chrony
# Edit the /etc/chrony/chrony.conf file on server, add subnet mask
sudo echo "allow 192.168.1.0/24" >> /etc/chrony/chrony.conf
systemctl restart chronyd
# ~/autostart.sh script ကို startup applications ထဲထည့်ခြင်းဖြင့် auto run မှာဖြစ်တယ်။
# Client computer မှ ssh ဝင်ရောက်ပြီး "tmux a" ဖြင့် sessions များကို ပြန်လည်ရယူနိုင်ပါသည်။
```
##### ~/.bashrc for Robot, Client computers
```
alias bb='colcon build --symlink-install && source install/setup.bash'
alias delete_workspace='rm -rf build install log; echo "Done"'
alias auto_launch="ros2 launch rom2109_controller all_start.launch.py use_joystick:=true use_lidar:=true amcl:=true navigation:=true"
alias client_launch="ros2 launch rom2109_controller client.launch.py use_rviz:=true"
export RMW_IMPLEMENTATION=rmw_cyclonedds_cpp
```
##### Client computer
```
ssh <name>@robot_ip
sudo apt install -y chrony
# add robot computer ip 
server 192.168.1.XX iburst
systemctl restart chronyd
# check source , you should see 192.168.1.xx as server
chronyc sources
```
##### attach Robot computer's tmux session 
```
ssh <name>@robot_ip
tmux a || tmux
```
#### GUI or CLI
```
# to disable GUI
sudo systemctl set-default multi-user && reboot
# to enable GUI
sudo systemctl set-default graphical
# to start GUI manually
sudo systemctl start gdm3
```
###### To Do ( July 8 2023 )
controller pkg ထဲက z_test_2_move.launch.py နဲ့ ရှေ့နောက် ဘယ်ညာ တပါတ်စီ ပြည့်မှီအောင် စစ်ဆေးရန် ( စစ်ဆေးပြီး OK )

###### To Do ( July 9 2023 )
simulation မှ rom2109_nav2 ကို လေ့လာပြီး Hardware robot အတွက် ပြင်ဆင်ခြင်း ( စစ်ဆေးပြီး OK )

###### To Do ( July 15 )
amcl run ရာမှာ map_server  run သော်လည်း map မထွက် ( စစ်ဆေးပြီး OK )
apt install ros-humble-rmw-cyclonedds-cpp </br>
map subscribe လုပ်ရာမှာ traiscient local သုံးပါ။ lifcycle map server ကို စစ်ဆေးပါ။

###### To Do ( July 22 )
NAV 2  စတင်အလုပ်လုပ်သော်လည်းတည်ငြိမ်မှုမရှိ ( စမ်းသပ်ဆဲ )


