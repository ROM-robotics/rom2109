### slam Problems နှင့် အဖြေများ

#### 1. collide ဖြစ်ရင် ရပ်တယ်။ <br>
???

#### 2. frequency 20 ထားေပမဲ့ မငြိမ် freq ~ <= 10 လောက်ပဲရှိ <br>
driver ထဲမှာ transmit ကိုဖျက်ပြီး 0.00 0.00 များမပို့ရန် ပြင်ဆင်သည်။


#### 3. local planner arc length ကြီးတယ်။  <br>
base_local_planner မှာ sim_time 4.0 မှ 1.8  ပြောင်းကြည့်ထားတယ်။ 

#### 4. Navfn vs global planner which one ?
##### ROS Global Planner
There are 3 global planners that adhere to nav_core::BaseGlobalPlanner interface: global_planner, navfn and carrot_planner. The nav_core::BaseGlobalPlanner provides an interface for global used in navigation.

###### carrot_plannerPermalink
The carrot_planner is the simplest global planner, which makes the robot to get as close to a user-specified goal point as possible. The planner checks whether. the user-specified goal is an obstacle. If it is, it moves back along the vector between the robot and the goal. Otherwise, it passes the goal point as a plan to the local planner or controller (internally).

###### navfn and global_plannerPermalink
navfn and global_planner are based on the work by Brock and Khatib, 1999[1]. The difference is that navfn uses Dijkstra’s algorithm, while global_planner is computed with more flexible options, including:

- support A* algorithm
- toggling quadratic approximation
- toggling grid path

Therefore, we generally use global_planner in our own project. Here, we will talk about some key parameters of it. The most frequently used parameters allow_unkown(true), use_djikstra(true), use_quadratic(true), use_grid_path(false), old_navfn_behavior(false) could be set to their default values shown in the brackets. If we want to visualize the potential map in RVIZ, it is helpful to change visualize_potential(false) to be true. Besides this, there are three parameters that highly impact the quality of the planned global path, since they have an effect on the heuristic of the algorithm. They are cost_factor, neutral_cost, and lethal_cost.

