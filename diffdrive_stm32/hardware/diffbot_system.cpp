#include "diffdrive_stm32/diffbot_system.hpp"

#include <chrono>
#include <cmath>
#include <limits>
#include <memory>
#include <vector>

#include "hardware_interface/types/hardware_interface_type_values.hpp"
#include "rclcpp/rclcpp.hpp"

namespace diffdrive_stm32
{
hardware_interface::CallbackReturn DiffDriveStm32Hardware::on_init(const hardware_interface::HardwareInfo & info)
{
  if (
    hardware_interface::SystemInterface::on_init(info) !=
    hardware_interface::CallbackReturn::SUCCESS)
  {
    return hardware_interface::CallbackReturn::ERROR;
  }
  cfg_.left_wheel_name = info_.hardware_parameters["left_wheel_name"];
  cfg_.right_wheel_name = info_.hardware_parameters["right_wheel_name"];
  cfg_.loop_rate = std::stof(info_.hardware_parameters["loop_rate"]);
  cfg_.device = info_.hardware_parameters["device"];
  cfg_.baud_rate = std::stoi(info_.hardware_parameters["baud_rate"]);
  cfg_.timeout_ms = std::stoi(info_.hardware_parameters["timeout_ms"]);
  cfg_.enc_counts_per_rev = std::stoi(info_.hardware_parameters["enc_counts_per_rev"]);
  RCLCPP_INFO(rclcpp::get_logger(" ================= "), "================================");
  RCLCPP_INFO(rclcpp::get_logger(" \033[1;36mDEEP BLUE AI LAB \033[1;0m "), " \033[1;36m& ROM Robotics is checking ... \033[1;0m");
  RCLCPP_INFO(rclcpp::get_logger(" ================= "), "================================");
  if (info_.hardware_parameters.count("pid_p") > 0)
  {
    cfg_.pid_p = std::stoi(info_.hardware_parameters["pid_p"]);
    cfg_.pid_d = std::stoi(info_.hardware_parameters["pid_d"]);
    cfg_.pid_i = std::stoi(info_.hardware_parameters["pid_i"]);
    cfg_.pid_o = std::stoi(info_.hardware_parameters["pid_o"]);
  }
  else
  {
    RCLCPP_INFO(rclcpp::get_logger("DiffDriveStm32Hardware"), "PID values not supplied, using defaults.");
  }
  

  wheel_l_.setup(cfg_.left_wheel_name, cfg_.enc_counts_per_rev);
  wheel_r_.setup(cfg_.right_wheel_name, cfg_.enc_counts_per_rev);


  for (const hardware_interface::ComponentInfo & joint : info_.joints)
  {
    // DiffBotSystem has exactly two states and one command interface on each joint
    if (joint.command_interfaces.size() != 1)
    {
      RCLCPP_FATAL(rclcpp::get_logger("DiffDriveStm32Hardware"),"Joint '%s' has %zu command interfaces found. 1 expected.", joint.name.c_str(),joint.command_interfaces.size());
      return hardware_interface::CallbackReturn::ERROR;
    }

    if (joint.command_interfaces[0].name != hardware_interface::HW_IF_VELOCITY)
    {
      RCLCPP_FATAL(rclcpp::get_logger("DiffDriveStm32Hardware"),"Joint '%s' have %s command interfaces found. '%s' expected.", joint.name.c_str(),joint.command_interfaces[0].name.c_str(), hardware_interface::HW_IF_VELOCITY);
      return hardware_interface::CallbackReturn::ERROR;
    }

    if (joint.state_interfaces.size() != 2)
    {
      RCLCPP_FATAL(rclcpp::get_logger("DiffDriveStm32Hardware"),"Joint '%s' has %zu state interface. 2 expected.", joint.name.c_str(),joint.state_interfaces.size());
      return hardware_interface::CallbackReturn::ERROR;
    }

    if (joint.state_interfaces[0].name != hardware_interface::HW_IF_POSITION)
    {
      RCLCPP_FATAL(rclcpp::get_logger("DiffDriveStm32Hardware"),"Joint '%s' have '%s' as first state interface. '%s' expected.", joint.name.c_str(),joint.state_interfaces[0].name.c_str(), hardware_interface::HW_IF_POSITION);
      return hardware_interface::CallbackReturn::ERROR;
    }

    if (joint.state_interfaces[1].name != hardware_interface::HW_IF_VELOCITY)
    {
      RCLCPP_FATAL(rclcpp::get_logger("DiffDriveStm32Hardware"),"Joint '%s' have '%s' as second state interface. '%s' expected.", joint.name.c_str(),joint.state_interfaces[1].name.c_str(), hardware_interface::HW_IF_VELOCITY);
      return hardware_interface::CallbackReturn::ERROR;
    }
  }

  return hardware_interface::CallbackReturn::SUCCESS;
}

std::vector<hardware_interface::StateInterface> DiffDriveStm32Hardware::export_state_interfaces()
{
  std::vector<hardware_interface::StateInterface> state_interfaces;

  state_interfaces.emplace_back(hardware_interface::StateInterface(wheel_l_.name, hardware_interface::HW_IF_POSITION, &wheel_l_.pos));
  state_interfaces.emplace_back(hardware_interface::StateInterface(wheel_l_.name, hardware_interface::HW_IF_VELOCITY, &wheel_l_.vel));

  state_interfaces.emplace_back(hardware_interface::StateInterface(wheel_r_.name, hardware_interface::HW_IF_POSITION, &wheel_r_.pos));
  state_interfaces.emplace_back(hardware_interface::StateInterface(wheel_r_.name, hardware_interface::HW_IF_VELOCITY, &wheel_r_.vel));

  return state_interfaces;
}

std::vector<hardware_interface::CommandInterface> DiffDriveStm32Hardware::export_command_interfaces()
{
  std::vector<hardware_interface::CommandInterface> command_interfaces;

  command_interfaces.emplace_back(hardware_interface::CommandInterface(
    wheel_l_.name, hardware_interface::HW_IF_VELOCITY, &wheel_l_.cmd));

  command_interfaces.emplace_back(hardware_interface::CommandInterface(
    wheel_r_.name, hardware_interface::HW_IF_VELOCITY, &wheel_r_.cmd));

  return command_interfaces;
}

hardware_interface::CallbackReturn DiffDriveStm32Hardware::on_configure(const rclcpp_lifecycle::State & /*previous_state*/)
{
  RCLCPP_INFO(rclcpp::get_logger("DiffDriveStm32Hardware"), "Configuring ...please wait...");
  if (comms_.connected())
  {
    comms_.disconnect();
  }
  comms_.connect(cfg_.device, cfg_.baud_rate, cfg_.timeout_ms);
  RCLCPP_INFO(rclcpp::get_logger("DiffDriveStm32Hardware"), "Successfully configured!");

  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn DiffDriveStm32Hardware::on_cleanup(const rclcpp_lifecycle::State & /*previous_state*/)
{
  RCLCPP_INFO(rclcpp::get_logger("DiffDriveStm32Hardware"), "Cleaning up ...please wait...");
  if (comms_.connected())
  {
    comms_.disconnect();
  }
  RCLCPP_INFO(rclcpp::get_logger("DiffDriveStm32Hardware"), "Successfully cleaned up!");

  return hardware_interface::CallbackReturn::SUCCESS;
}


hardware_interface::CallbackReturn DiffDriveStm32Hardware::on_activate(const rclcpp_lifecycle::State & /*previous_state*/)
{
  RCLCPP_INFO(rclcpp::get_logger("DiffDriveStm32Hardware"), "Activating ...please wait...");
  if (!comms_.connected())
  {
    return hardware_interface::CallbackReturn::ERROR;
  }
  if (cfg_.pid_p > 0)
  {
    comms_.set_pid_values(cfg_.pid_p,cfg_.pid_d,cfg_.pid_i,cfg_.pid_o);
  }
  RCLCPP_INFO(rclcpp::get_logger("DiffDriveStm32Hardware"), "Successfully activated!");

  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn DiffDriveStm32Hardware::on_deactivate(const rclcpp_lifecycle::State & /*previous_state*/)
{
  RCLCPP_INFO(rclcpp::get_logger("DiffDriveStm32Hardware"), "Deactivating ...please wait...");
  RCLCPP_INFO(rclcpp::get_logger("DiffDriveStm32Hardware"), "Successfully deactivated!");

  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::return_type DiffDriveStm32Hardware::read(const rclcpp::Time & /*time*/, const rclcpp::Duration & period)
{
  
  if (!comms_.connected())
  {
    RCLCPP_INFO(rclcpp::get_logger("DiffBotSystemHardware"), "comms_.connected() is false.");
    return hardware_interface::return_type::ERROR;
  }
  
  comms_.read_encoder_values(wheel_r_.enc, wheel_l_.enc);

  double delta_seconds = period.seconds();
  // Encoder values to wheel positions ( Author say check encoder overflows )
  float prev_l_pos = wheel_l_.pos;
  wheel_l_.pos = wheel_l_.calc_enc_angle();                     // radian calculation Ok, but check encoder overflow
  wheel_l_.vel = (wheel_l_.pos - prev_l_pos) / delta_seconds;   // radians per delta seconds calculation OK

  float prev_r_pos = wheel_r_.pos;
  wheel_r_.pos = wheel_r_.calc_enc_angle();
  wheel_r_.vel = (wheel_r_.pos - prev_r_pos) / delta_seconds;   // radians per delta seconds calculation OK
  /*
  RCLCPP_INFO(rclcpp::get_logger("\033[1;36mZeroing Test"), "right wheel encoder : %d", wheel_r_.enc);
  RCLCPP_INFO(rclcpp::get_logger("Zeroing Test"), "right wheel pos : %.15f", wheel_r_.pos);
  RCLCPP_INFO(rclcpp::get_logger("Zeroing Test"), "rad_per_count : %.15f \033[1;0m", wheel_r_.rads_per_count);
  
  RCLCPP_INFO(rclcpp::get_logger("\033[1;35mZeroing Test"), "left wheel encoder : %d", wheel_l_.enc);
  RCLCPP_INFO(rclcpp::get_logger("Zeroing Test"), "left wheel pos : %.15f", wheel_l_.pos);
  RCLCPP_INFO(rclcpp::get_logger("Zeroing Test"), "rad_per_count : %.15f \033[1;0m", wheel_l_.rads_per_count);
  */
  return hardware_interface::return_type::OK;
}

hardware_interface::return_type diffdrive_stm32 ::DiffDriveStm32Hardware::write(const rclcpp::Time & /*time*/, const rclcpp::Duration & /*period*/)
{
  if (!comms_.connected())
  {
    RCLCPP_INFO(rclcpp::get_logger("[ Deeb Blue AI Lab ]"), "comms_.connected() is false.");
    return hardware_interface::return_type::ERROR;
  }
  
  //int left_rpm = int(wheel_l_.cmd*10); int right_rpm = int(wheel_r_.cmd*10);
  comms_.set_motor_values(wheel_r_.cmd, wheel_l_.cmd);
  return hardware_interface::return_type::OK;
}

}  // namespace diffdrive_stm32

#include "pluginlib/class_list_macros.hpp"
PLUGINLIB_EXPORT_CLASS(
  diffdrive_stm32::DiffDriveStm32Hardware, hardware_interface::SystemInterface)
