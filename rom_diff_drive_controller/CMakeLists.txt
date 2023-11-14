cmake_minimum_required(VERSION 3.16)
project(rom_diff_drive_controller LANGUAGES CXX)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
  add_compile_options(-Wall -Wextra)
endif()

set(THIS_PACKAGE_INCLUDE_DEPENDS
  controller_interface
  generate_parameter_library
  geometry_msgs
  hardware_interface
  nav_msgs
  pluginlib
  rclcpp
  rclcpp_lifecycle
  rcpputils
  realtime_tools
  tf2
  tf2_msgs
)

find_package(ament_cmake REQUIRED)
find_package(backward_ros REQUIRED)
foreach(Dependency IN ITEMS ${THIS_PACKAGE_INCLUDE_DEPENDS})
  find_package(${Dependency} REQUIRED)
endforeach()

generate_parameter_library(rom_diff_drive_controller_parameters
  src/rom_diff_drive_controller_parameter.yaml
)

add_library(rom_diff_drive_controller SHARED
  src/rom_diff_drive_controller.cpp
  src/odometry.cpp
  src/speed_limiter.cpp
)
target_compile_features(rom_diff_drive_controller PUBLIC cxx_std_17)
target_include_directories(rom_diff_drive_controller PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/rom_diff_drive_controller>
)
target_link_libraries(rom_diff_drive_controller PUBLIC rom_diff_drive_controller_parameters)
ament_target_dependencies(rom_diff_drive_controller PUBLIC ${THIS_PACKAGE_INCLUDE_DEPENDS})
# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_definitions(rom_diff_drive_controller PRIVATE "DIFF_DRIVE_CONTROLLER_BUILDING_DLL")
pluginlib_export_plugin_description_file(controller_interface diff_drive_plugin.xml)

if(BUILD_TESTING)
  find_package(ament_cmake_gmock REQUIRED)
  find_package(controller_manager REQUIRED)
  find_package(ros2_control_test_assets REQUIRED)

  ament_add_gmock(test_rom_diff_drive_controller
    test/test_rom_diff_drive_controller.cpp
    ENV config_file=${CMAKE_CURRENT_SOURCE_DIR}/test/config/test_rom_diff_drive_controller.yaml)
  target_link_libraries(test_rom_diff_drive_controller
    rom_diff_drive_controller
  )
  ament_target_dependencies(test_rom_diff_drive_controller
    geometry_msgs
    hardware_interface
    nav_msgs
    rclcpp
    rclcpp_lifecycle
    realtime_tools
    tf2
    tf2_msgs
  )

  ament_add_gmock(test_load_rom_diff_drive_controller
    test/test_load_rom_diff_drive_controller.cpp
  )
  ament_target_dependencies(test_load_rom_diff_drive_controller
    controller_manager
    ros2_control_test_assets
  )
endif()

install(
  DIRECTORY include/
  DESTINATION include/rom_diff_drive_controller
)
install(TARGETS rom_diff_drive_controller rom_diff_drive_controller_parameters
  EXPORT export_rom_diff_drive_controller
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
)

ament_export_targets(export_rom_diff_drive_controller HAS_LIBRARY_TARGET)
ament_export_dependencies(${THIS_PACKAGE_INCLUDE_DEPENDS})
ament_package()
