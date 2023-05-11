## rom2109 Autonomous Mobile Robot

#### ROS2 humble အတွက် packageများ
ros2 launch rom2109_description description.xacro.launch.py use_sim_time:=true

#### gazebo 
"""
sudo apt install -y ros-humble-gazebo-ros* 
sudo apt install -y ros-humble-ros2-control*
sudo apt install -y ros-humble-controller-*
"""
ပြီးရင်  git clone ပြီး build ပါ။
git clone git@github.com:ROM-robotics/rom2109.git
colcon build

<img src="images/orange_bot.png" width="619" height="330" />rom2109_tall ကို ကိုပြည့်စုံအောင် design ဆွဲပြီး rom2109_bot ကို ကိုစည်သူရဲထွန်း design ဆွဲပြီး မြန်မာပြည်တွင် တပ်ဆင်သည်။

#### အသုံးပြုနည်း
<a href="https://github.com/ROM-robotics/rom2109/blob/humble-devel/rom2109_description/README.md">rom2109_description အသုံးပြုနည်း </a> 

<a href="https://github.com/ROM-robotics/rom2109/blob/humble-devel/rom2109_description/README.md">rom2109_gazebo အသုံးပြုနည်း </a> 

<a href="www.google.com">rom2109_nav2 အသုံးပြုနည်း </a> 

<a href="www.google.com">rom2109_autonomy အသုံးပြုနည်း </a> 

<a href="www.google.com">Real Robot အသုံးပြုနည်း </a> 

#### အဲ့လို ၃ခု မ run ချင်ရင် rom2109_gazebo ထဲက 
ros2 launch rom2109_gazebo rom2109_sim.launch.py