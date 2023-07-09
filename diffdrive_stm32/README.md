# diffdrive_stm32

```
cd your_worspace/src
vcs import --input rom2109/diffdrive_stm32/ros2_control_demos.humble.repos
cd ..
rosdep install --from-paths src --ignore-src -r -y
colcon build --symlink-install
```
Build တာကြာမှာဖြစ်တဲ့အတွက် packages-select သို့မဟုတ် workspace ခွဲပြီးသုံးသင့်တယ်။ ဒါမှမဟုတ် အောက်ပါအတိုင်း install/reinstall လုပ်ပါ။
```
sudo apt install -y ros-humble-gazebo-ros2-control \
ros-humble-ros2controlcli \
ros-humble-ros2-control \
ros-humble-ros2-controllers \
ros-humble-effort-controllers \
ros-humble-velocity-controllers \
ros-humble-gripper-controllers \
ros-humble-position-controllers \
ros-humble-tricycle-controller \
ros-humble-admittance-controller \
ros-humble-forward-command-controller \
ros-humble-joint-trajectory-controller \
ros-humble-rqt-joint-trajectory-controller \
ros-humble-controller-manager \
ros-humble-rqt-controller-manager \
ros-humble-hardware-interface \
ros-humble-controller-interface \
ros-humble-transmission-interface \
ros-humble-control-msgs \
ros-humble-controller-manager-msgs \
ros-humble-realtime-tools \
ros-humble-ros2-control-test-assets \
ros-humble-joint-limits \
ros-humble-joint-state-broadcaster \
ros-humble-force-torque-sensor-broadcaster \
ros-humble-force-torque-sensor-broadcaster \
ros-humble-ackermann-* \
ros-humble-imu-sensor-broadcaster 
```
ပြီးရင် run ကြည့်

```
colcon build --symlink-install
ros2 launch rom2109_controller rom2109.launch.py
```


