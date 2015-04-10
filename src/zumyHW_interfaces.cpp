#include "zumy_hardware_interfaces.h"
#include "controller_manager/controller_manager.h"
#include "ros/ros.h" 

int main(int argc, char **argv)
{
  ros::init(argc, argv, "zumy_harward_interface");

  ros::NodeHandle n;

  Zumy zumy;	
  controller_manager::ControllerManager cm(&zumy);

  while(ros::ok())
  {
    zumy.read();
    cm.update(zumy.get_time(), zumy.get_period());
    zumy.write();
    sleep(20);
  }
}
