#include "add_collision_object/PubMeshes.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "building_workspace");
    ros::NodeHandle node_handle;
    ros::AsyncSpinner spinner(1);
    spinner.start();

    ros::Publisher scene_pub = node_handle.advertise<moveit_msgs::PlanningScene>("planning_scene", 1);
    
    sleep(2.0);
    try
    {
        geometry_msgs::Pose p;
        p.position.x = atof(argv[8]);
        p.position.y = atof(argv[9]);
        p.position.z = atof(argv[10]);
        if(argc == 14)
        {
            tf2::Quaternion orientation;
            orientation.setRPY(atof(argv[11]), atof(argv[12]), atof(argv[13]));
            p.orientation = tf2::toMsg(orientation);

        }
        else
        {
            p.orientation.x = atof(argv[11]);
            p.orientation.y = atof(argv[12]);
            p.orientation.z = atof(argv[13]);
            p.orientation.w = atof(argv[14]);
        }
        PubMeshes pub(scene_pub);
        pub.getMeshes(argv[1], argv[2], argv[3], p);
        pub.setColor(atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]));
        pub.Pub();
        ROS_INFO("object created"); 
    }
    catch(...)
    {
        ROS_INFO("object create faild");
    }
    return 0;
}