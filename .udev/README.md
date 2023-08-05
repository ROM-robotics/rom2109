## Robot computer ပြုလုပ်ရန်
### udev rules
```
./1_install_rudev_rules
./2_network
./3_tmux_install/3_install.sh
```
### uninstall ပြုလုပ်ရန်
```
./uninstall
```
##### Ubuntu 22 ဆိုရင် 
```
sudo apt remove brltty   
```
### auto startup 

startup app မှာ /path_to/3_tmux_install/autostart.sh ထည့်ပါ

## control computer ပြုလုပ်ရန်
```
ssh <name>@ip
tmux a || tmux
```
