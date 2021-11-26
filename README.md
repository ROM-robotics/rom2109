# rom2109 Autonomous Mobile Robot

- လိုအပ်သော package များကို install လုပ်ရန် install_all.bash ကို run ပါ။

- robot controller နှင့် lidar port များကို robot computer တွင် /home/rom/robotController , /dev/rplidar အဖြစ် ရရှိစေရန်
  rom2109_controller/udev/install.bash ကို run ပါ။ ပြန်ဖျက်လိုပါက ./uninstall.bash ကို run ပါ။

- ssh မှ login ဝင်ရာတွင် ~/.bashrc ကို run မပေးပါ။ ဒါကြောင့် roscore, roslaunch, rosrun များ run နိုင်မည်မဟုတ်ပါ။  login   ဝင်တိုင်း source ~/.bashrc လုပ်ရပါမယ်။ မလုပ်ချင်ရင် .bash_profile သို့မဟုတ် .profile မှာ အောက်ပါအတိုင်းရေးထည့်ပါရန်။

if [ -f ~/.bashrc ]; then <br>
  . ~/.bashrc <br>
fi <br>

- gmapping မြေပုံမပေါ်ပါက map , odom နှစ်ခု relation frame မရှိလို့ ဖြစ်နိုင်ပါတယ်။ tf သည် time sensitive ဖြစ်တာမို့ computer နှစ်လုံးအချိန်ညှိပါ။ 


## အာ့တွေ တစ်ခုချင်း လုပ်ဖို့ ပျင်းတယ်ဆိုရင် 
### sudo ./install_ros_noetic.bash // ပြီးရင် auto reboot ကျပါမယ်။
### sudo ./install_dependencies.bash  // reboot နောက်တကြိမ်။
### ဒါဆို username mr_robot နဲ့ password ဖြင့် login ဝင်ရောက်ကာ robot ကို အသုံးပြုနိင်ပါပြီ။ 