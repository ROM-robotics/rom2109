# rom2109 Autonomous Mobile Robot

Rom robot controller နှင့် lidar port များကို robot computer တွင် /dev/robotController , /dev/rplidar အဖြစ် ရရှိစေရန်
rom2109_controller/udev/install.bash ကို run ပါ။ ပြန်ဖျက်လိုပါက ./uninstall.bash ကို run ပါ။

ssh မှ login ဝင်ရာတွင် ~/.bashrc ကို run မပေးပါ။ login ဝင်တိုင်း source ~/.bashrc လုပ်ရပါမယ်။မလုပ်ချင်ရင် .bash_profile သို့မဟုတ် .profile မှာ အောက်ပါအတိုင်းရေးပါ။

if [ -f ~/.bashrc ]; then
  . ~/.bashrc
fi


