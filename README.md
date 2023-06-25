## rom2109 Autonomous Mobile Robot ( Start Project - Sepetmber 2021)

#### ROS2 humble အတွက် packages များ Install ပြုလုပ်ခြင်း ( Hardware Robot  ) 
packages များရှိ သက်ဆိုင်ရာ README.md ကို ကြည့်ပါ။

###### အောက်ပါ packages များသွင်းပါ။ 
```
sudo apt install -y ros-humble-gazebo-ros* 
sudo apt install -y ros-humble-ros2-control*
sudo apt install -y ros-humble-controller-*
cd your/workspace/src
git clone git@github.com:ROM-robotics/rom2109.git
cd your/workspace && colcon build --symlink-install && source install/setup.bash
```
<img src="images/orange_bot.png" width="619" height="330" />
rom2109_tall ကို ကိုပြည့်စုံအောင် design ဆွဲပြီး rom2109_bot ကို ကိုစည်သူရဲထွန်း design ဆွဲပြီး assembly ပြုလုပ်သည်။
<br><br>
#### Menu
<a href="https://github.com/ROM-robotics/rom2109/blob/humble-devel/rom2109_description/README.md"> 1) Robot ရွေးချယ်ရန် </a> 

<a href="https://github.com/ROM-robotics/rom2109/tree/humble-devel/rom2109_hardware"> 2)  Real Robot အသုံးပြုနည်း </a> 

<a href="https://github.com/ROM-robotics/rom2109/tree/humble-devel/rom2109_nav2"> 3)  Navigation ပြုလုပ်နည်း </a> 

<a href="https://github.com/ROM-robotics/rom2109/tree/humble-devel/rom2109_autonomy"> 4)  Patrol လှည့်နည်း </a> 

###### use alias
```
alias bb='colcon build --symlink-install && clear && source install/setup.bash'
alias delete_workspace='rm -rf build install log; echo "Done"
```



