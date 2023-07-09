cmake_minimum_required(VERSION 3.8)
project(rom2109_controller)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(gazebo_ros REQUIRED)
find_package(robot_state_publisher REQUIRED)
find_package(ros2_control REQUIRED)
find_package(ros2_controllers REQUIRED)
find_package(rviz2 REQUIRED)
find_package(xacro REQUIRED)
find_package(rom2109_description REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

add_executable(go_straight src/go_straight.cpp)
ament_target_dependencies(go_straight geometry_msgs rclcpp tf2 tf2_ros )

add_executable(go_rotate src/go_rotate.cpp)
ament_target_dependencies(go_rotate geometry_msgs rclcpp tf2 tf2_ros )

install(TARGETS
   go_straight
   go_rotate
   DESTINATION lib/${PROJECT_NAME})

install(
  DIRECTORY
    config
    launch
    rviz
  DESTINATION
    share/${PROJECT_NAME}/
)

ament_package()
