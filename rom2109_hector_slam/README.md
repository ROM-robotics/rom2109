hector slam စမ်းရန်

https://drive.google.com/file/d/1vPmjTjUVHk-XR1lHgXlAwnQWabMv5fdz/view?usp=sharing

ကို download လုပ်ပြီး bag ထဲသိုထည့်ပါ။ tutorial.launch ကို run ပါ။ simulation အတွက် sim_time ကို true ပေးရပြီး rosbag ဖွင့်ရင် $ rosbag play xxx.bag --clock ကိုသုံးပါ။

#### for robot
1 - set sim_time false
2 - after launching, start map saving process with 
$ rostopic pub syscommand std_msgs/String "savegeotiff"
3 - ပြီးရင် map_saver နဲ့ save ပါ။
$ rosrun map_server map_saver -f myMap