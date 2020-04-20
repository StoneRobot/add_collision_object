#include "add_collision_object/PubMeshes.h"

PubMeshes::PubMeshes(ros::Publisher diff_pub)
{
    pub_scene_diff = diff_pub;
    
};

void PubMeshes::setColor(size_t r, size_t g, size_t b, size_t a)
{
    color.id = object.id;
    color.color.r = r;
    color.color.g = g;
    color.color.b = b;
    color.color.a = a;
}

void PubMeshes::getMeshes(string sys, string name, string frame_id, geometry_msgs::Pose pose)
{
    path = "package://" + sys;
    shapes::Mesh* m = shapes::createMeshFromResource(path);

    shapes::ShapeMsg object_mesh_msg;
    shapes::constructMsgFromShape(m,object_mesh_msg);
    object_mesh = boost::get<shape_msgs::Mesh>(object_mesh_msg);
    object.header.frame_id = frame_id;
    object.id = name;
    object.meshes.resize(1);
    object.meshes[0] = object_mesh;
    object.mesh_poses.resize(1);
    object.mesh_poses[0] = pose;
}

void PubMeshes::Pub()
{
    object.meshes.push_back(object_mesh);
    object.mesh_poses.push_back(object.mesh_poses[0]);
    object.operation = object.ADD;

    std::vector<moveit_msgs::CollisionObject> collision_objects;  
    collision_objects.push_back(object); 
    planning_scene_interface.addCollisionObjects(collision_objects);
    
    moveit_msgs::PlanningScene p;
    p.is_diff = true;
    p.object_colors.push_back(color);
    pub_scene_diff.publish(p);
}
