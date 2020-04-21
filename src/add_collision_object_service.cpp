#include <ros/ros.h>
#include <std_srvs/Trigger.h>
#include<stdlib.h>


bool handback(std_srvs::Trigger::Request &req, std_srvs::Trigger::Response & rep)
{
    try
    {
        system("roslaunch add_collision_object add_collision_object.launch");
        rep.success = true;
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        rep.success = false;
        return false;
    }
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "add_collision_service");
    ros::NodeHandle nh;
    ros::AsyncSpinner spinner(1);
    spinner.start();
    ros::ServiceServer add_server = nh.advertiseService("add_collision", handback);
    ROS_INFO("Please invoke the service");
    ros::waitForShutdown();
    return 0;
}
