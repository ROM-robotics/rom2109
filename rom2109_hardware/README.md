###### ပြင်ရန်
hw_controllers.yaml ကို ပြင်ပါ။

360 degree မောင်းပြီး drift ကို စစ်ပါ။ drift ရှိနေရင် 
- အရင်ဆုံး rviz က ဘီးရဲ့ frame နဲ့ အပြင် robot က ဘီးရဲ့ marker တို့ ညီမညီစစ်ပါ။ ( fixed frame -> base_link ထားပြီးစစ်ပါ )
- မညီရင် urdf ထဲက encoder count ကို ပြင်ပါ။ wheel diameter ကိုလည်းစစ်ပါ။

- fixed frame -> odom ထားပြီး 360 လှည့်ပါ။ rviz နဲ့  hw robot မတူရင် hw_controllers.yaml ထဲက 
- wheel_seperation ကို တိုး/လျော့ လုပ်ပါ။



<a href="https://github.com/ROM-robotics/rom2109">မူလစာမျက်နှာ </a>