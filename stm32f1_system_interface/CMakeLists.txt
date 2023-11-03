cmake_minimum_required(VERSION 3.16)
project(stm32f1_system_interface LANGUAGES CXX)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
  add_compile_options(-Wall -Wextra)
endif()

# find dependencies
set(THIS_PACKAGE_INCLUDE_DEPENDS
  hardware_interface
  pluginlib
  rclcpp
  rclcpp_lifecycle
)

# find dependencies
find_package(ament_cmake REQUIRED)
foreach(Dependency IN ITEMS ${THIS_PACKAGE_INCLUDE_DEPENDS})
  find_package(${Dependency} REQUIRED)
endforeach()


## COMPILE
add_library(
  stm32f1_system_interface
  SHARED
  hardware/diffbot_system.cpp
)
target_compile_features(stm32f1_system_interface PUBLIC cxx_std_17)
target_include_directories(stm32f1_system_interface PUBLIC
$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/hardware/include>
$<INSTALL_INTERFACE:include/stm32f1_system_interface>
)
ament_target_dependencies(
  stm32f1_system_interface PUBLIC
  ${THIS_PACKAGE_INCLUDE_DEPENDS}
)

target_link_libraries(stm32f1_system_interface PUBLIC serial)

# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_definitions(${PROJECT_NAME} PRIVATE "STM32F1_SYSTEM_INTERFACE_BUILDING_DLL")

# Export hardware plugins
pluginlib_export_plugin_description_file(hardware_interface stm32f1_system_interface.xml)

# INSTALL
install(
  DIRECTORY hardware/include/
  DESTINATION include/stm32f1_system_interface
)
install(
  DIRECTORY description/launch description/ros2_control description/urdf description/rviz
  DESTINATION share/stm32f1_system_interface
)
install(
  DIRECTORY bringup/launch bringup/config
  DESTINATION share/stm32f1_system_interface
)
install(TARGETS stm32f1_system_interface
  EXPORT export_stm32f1_system_interface
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)
endif()

## EXPORTS
ament_export_targets(export_stm32f1_system_interface HAS_LIBRARY_TARGET)
ament_export_dependencies(${THIS_PACKAGE_INCLUDE_DEPENDS})
ament_package()
