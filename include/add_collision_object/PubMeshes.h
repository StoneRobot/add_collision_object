#pragma once
#include "ros/ros.h"
#include "moveit/move_group_interface/move_group_interface.h"
#include "geometric_shapes/shapes.h"
#include "geometric_shapes/mesh_operations.h"
#include "geometric_shapes/shape_operations.h"
#include "moveit/planning_scene_interface/planning_scene_interface.h"
#include "moveit_msgs/PlanningScene.h"
#include "moveit_msgs/ObjectColor.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include <string.h>
#include <vector>
#include <map>
#include <stdlib.h>
#include <stdexcept>
using namespace std; 

class PubMeshes
{
public:
    PubMeshes(ros::Publisher diff_pub);
    void getMeshes(string sys, string name, string frame_id, geometry_msgs::Pose pose);
    void setColor(size_t r, size_t g, size_t b, size_t a);
    void Pub();
    bool checkPubStatus();
    virtual ~PubMeshes()
    {
    };

private:
    moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
    ros::Publisher pub_scene_diff;
    string path;
    moveit_msgs::CollisionObject object;
    moveit_msgs::ObjectColor color;
    shape_msgs::Mesh object_mesh;
};