#include "hardware_interface/joint_command_interface.h"
#include "hardware_interface/joint_state_interface.h"
#include "hardware_interface/robot_hw.h"

#include "ros/time.h"
#include "ros/duration.h"

class Zumy : public hardware_interface::RobotHW {
public:
  Zumy(){
    //register joint state interface 
    hardware_interface::JointStateHandle state_handle_left_wheel("wheel_left_joint",&pos[0],&vel[0],&eff[0]);
    jnt_state_interface.registerHandle(state_handle_left_wheel);

    hardware_interface::JointStateHandle state_handle_right_wheel("wheel_right_joint",&pos[1],&vel[1],&eff[1]);
    jnt_state_interface.registerHandle(state_handle_right_wheel);

    registerInterface(&jnt_state_interface);

    //register joint velocity interface
    hardware_interface::JointHandle vel_handle_left_wheel(jnt_state_interface.getHandle("wheel_left_joint"), &cmd[0]);
    jnt_vel_interface.registerHandle(vel_handle_left_wheel);

    hardware_interface::JointHandle vel_handle_right_wheel(jnt_state_interface.getHandle("wheel_right_joint"), &cmd[1]);
    jnt_vel_interface.registerHandle(vel_handle_right_wheel);

    registerInterface(&jnt_vel_interface);

    //record current time
    last_time = ros::Time::now();
  }
  
  void read();
  void write();
  ros::Time get_time();
  ros::Duration get_period();

private:
  hardware_interface::JointStateInterface jnt_state_interface;
  hardware_interface::VelocityJointInterface jnt_vel_interface;
  //hardware_interface::PositionJointInterface jnt_pos_interface;
  ros::Time last_time;
  ros::Duration period;
  double cmd[2];
  double pos[2];
  double vel[2];
  double eff[2];
};

void Zumy::read () {
  pos[0]=1;
  pos[1]=1;
  vel[0]=0;
  vel[1]=0;
  eff[0]=0;
  eff[1]=0;
}

void Zumy::write(){
}

ros::Time Zumy::get_time(){
  return ros::Time::now();
}

ros::Duration Zumy::get_period(){
  ros::Time current_time = ros::Time::now();
  ros::Duration period = current_time - last_time;
  last_time = current_time;
  return period;
}


