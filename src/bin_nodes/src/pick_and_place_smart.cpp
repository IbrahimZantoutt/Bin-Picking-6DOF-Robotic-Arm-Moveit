#include "rclcpp/rclcpp.hpp"
#include <moveit/move_group_interface/move_group_interface.h>
#include <geometry_msgs/msg/pose.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <linkattacher_msgs/srv/attach_link.hpp>
#include <linkattacher_msgs/srv/detach_link.hpp>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit_msgs/msg/collision_object.hpp>

#include <bin_interfaces/srv/get_targets.hpp>

#include <chrono>
#include <thread>

using namespace std::chrono_literals;

using moveit::planning_interface::MoveGroupInterface;
int main(int argc, char **argv){
    rclcpp::init(argc, argv);

    auto node = std::make_shared<rclcpp::Node>("pick_and_place_smart", rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true));
    auto logger = node->get_logger();

    auto client = node->create_client<bin_interfaces::srv::GetTargets>("get_targets");

    auto request  = std::make_shared<bin_interfaces::srv::GetTargets::Request>();

    // The world spawns exactly these cubes at these positions. The camera only
    // reports *where* a cube is, never *which* one, so we attach the model whose
    // known position is closest to the detection -- never a blind counter (which
    // would grab the wrong cube and run off the end of the real models).
    struct Cube { std::string name; double x, y; };
    const std::vector<Cube> kCubes = {
        {"green_cube_1", 0.3, 0.55},
        {"green_cube_2", 0.5, 0.15},
        {"green_cube_3", 0.4, 0.35},
    };
    std::string current_cube_;   // model attached this cycle ("" = nothing held)

    // Return the known cube nearest (x,y), or "" if none is within the gate.
    auto nearestCube = [&](double x, double y) -> std::string {
        std::string best;
        double best_d2 = 0.05 * 0.05;   // 5 cm gate; cubes are ~20 cm apart
        for (const auto & c : kCubes) {
            double d2 = (c.x - x) * (c.x - x) + (c.y - y) * (c.y - y);
            if (d2 < best_d2) { best_d2 = d2; best = c.name; }
        }
        return best;
    };

    auto search = [&](geometry_msgs::msg::Point & out) -> bool {
        if (!client->wait_for_service(5s)) {
            RCLCPP_ERROR(logger, "get_targets service not available (is VisionNode running?)");
            return false;
        }
        auto future = client->async_send_request(request);
        if (future.wait_for(5s) != std::future_status::ready) {
            RCLCPP_ERROR(logger, "get_targets call timed out");
            return false;
        }
        auto response = future.get();
        if (response->found) {
            out = response->target.point;                 // <-- fill the output
            RCLCPP_INFO(logger, "Target at: x=%f y=%f z=%f", out.x, out.y, out.z);
            return true;
        }
        RCLCPP_WARN(logger, "No target found.");
        return false;
    };


    rclcpp::executors::SingleThreadedExecutor executor;
    executor.add_node(node);
    std::thread spin_thread([&executor]() { executor.spin(); });

    MoveGroupInterface arm(node, "arm");
    arm.setMaxVelocityScalingFactor(0.3);
    arm.setMaxAccelerationScalingFactor(0.3);
    arm.setPlanningTime(5.0);


    MoveGroupInterface gripper(node, "gripper");
    gripper.setMaxVelocityScalingFactor(0.3);
    gripper.setMaxAccelerationScalingFactor(0.3);
    gripper.setPlanningTime(5.0);

    // Helper: plan, and if planning succeeds, execute. Returns true on success.
    auto plan_and_execute = [&](const std::string & what) {
      MoveGroupInterface::Plan plan;
      bool ok = (arm.plan(plan) == moveit::core::MoveItErrorCode::SUCCESS);
      RCLCPP_INFO(logger, "Plan to [%s]: %s", what.c_str(), ok ? "SUCCESS" : "FAILED");
      if (ok) {
        arm.execute(plan);
      }
      return ok;
    };

    // Service clients for the Gazebo LinkAttacher plugin.
    auto attach_client = node->create_client<linkattacher_msgs::srv::AttachLink>("/ATTACHLINK");
    auto detach_client = node->create_client<linkattacher_msgs::srv::DetachLink>("/DETACHLINK");

    auto attach = [&](const std::string & m1, const std::string & l1,
                      const std::string & m2, const std::string & l2){
        if (!attach_client->wait_for_service(5s)) {
            RCLCPP_ERROR(logger, "/ATTACHLINK service not available");
            return false;
        }
        auto req = std::make_shared<linkattacher_msgs::srv::AttachLink::Request>();
        req->model1_name = m1;
        req->link1_name  = l1;
        req->model2_name = m2;
        req->link2_name  = l2;
        auto future = attach_client->async_send_request(req);
        if (future.wait_for(5s) != std::future_status::ready) {
            RCLCPP_ERROR(logger, "/ATTACHLINK call timed out");
            return false;
        }
        auto res = future.get();
        RCLCPP_INFO(logger, "Attach: %s (%s)", res->success ? "OK" : "FAIL", res->message.c_str());
        return res->success;
    };

    auto detach = [&](const std::string & m1, const std::string & l1,
                      const std::string & m2, const std::string & l2){
        if (!detach_client->wait_for_service(5s)) {
            RCLCPP_ERROR(logger, "/DETACHLINK service not available");
            return false;
        }
        auto req = std::make_shared<linkattacher_msgs::srv::DetachLink::Request>();
        req->model1_name = m1;
        req->link1_name  = l1;
        req->model2_name = m2;
        req->link2_name  = l2;
        auto future = detach_client->async_send_request(req);
        if (future.wait_for(5s) != std::future_status::ready) {
            RCLCPP_ERROR(logger, "/DETACHLINK call timed out");
            return false;
        }
        auto res = future.get();
        RCLCPP_INFO(logger, "Detach: %s (%s)", res->success ? "OK" : "FAIL", res->message.c_str());
        return res->success;
    };

    auto setGripper = [&](double g1, double g2){
        gripper.setJointValueTarget({std::map<std::string, double>{{"gripperfinger_left_joint", g1}, {"gripperfinger_right_joint", g2}}});

        MoveGroupInterface::Plan plan;
        if(gripper.plan(plan)==moveit::core::MoveItErrorCode::SUCCESS){
            gripper.execute(plan);
        }
    };

    auto goToPos = [&](double x, double y, double z, double roll, double pitch, double yaw){
        geometry_msgs::msg::Pose target_pose;
        target_pose.position.x = x;
        target_pose.position.y = y;
        target_pose.position.z = z;
        tf2::Quaternion q;
        q.setRPY(roll, pitch, yaw);
        target_pose.orientation.x = q.x();
        target_pose.orientation.y = q.y();
        target_pose.orientation.z = q.z();
        target_pose.orientation.w = q.w();
        arm.setPoseTarget(target_pose);
        return plan_and_execute("pose target");
    };

    auto pick = [&](double x, double y, double z){
        //goToPos(0.304, 0.339, 0.247,2.863, 1.389, -3.141);  better to add when added collision aware movement
        current_cube_ = nearestCube(x, y);
        if (current_cube_.empty()) {
            RCLCPP_WARN(logger, "No known cube near (%.3f, %.3f); skipping pick.", x, y);
            return;
        }
        if(goToPos(x, y, z+0.06, 3.1416, 0, 0)){
            attach("robot_arm", "wrist_yaw_link", current_cube_, "link");
            setGripper(0.01, 0.01);
        } else {
            current_cube_.clear();   // never grabbed it -> nothing to detach later
        }
    };

    auto place = [&](){
        //goToPos(0.374, -0.215, 0.327,-0.898, -1.442, 2.633);
        if(goToPos(0.313, -0.309, 0.379,3.141, 1.390, 3.142)){
            RCLCPP_INFO(logger, "reached pos");
        } else RCLCPP_INFO(logger, "failed to reach pos");

        // Only detach the cube we actually attached this cycle -- avoids the
        // "Joint does not exist!" failures from detaching a phantom name.
        if (!current_cube_.empty()) {
            detach("robot_arm", "wrist_yaw_link", current_cube_, "link");
        }
        setGripper(0.0, 0.0);
        current_cube_.clear();
    };

    auto addCollisionObjects = [&](){
        moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
        std::vector<moveit_msgs::msg::CollisionObject> collision_objects;
        collision_objects.resize(4);

        collision_objects[0].id = "table1";
        collision_objects[0].header.frame_id = "world";
        collision_objects[0].primitives.resize(1);
        collision_objects[0].primitives[0].type = shape_msgs::msg::SolidPrimitive::BOX;
        collision_objects[0].primitives[0].dimensions = {0.4, 0.6, 0.2};
        collision_objects[0].primitive_poses.resize(1);
        collision_objects[0].primitive_poses[0].position.x = 0.4;
        collision_objects[0].primitive_poses[0].position.y = -0.35;
        collision_objects[0].primitive_poses[0].position.z = 0.1;
        collision_objects[0].operation = moveit_msgs::msg::CollisionObject::ADD;

        collision_objects[1].id = "table2";
        collision_objects[1].header.frame_id = "world";
        collision_objects[1].primitives.resize(1);
        collision_objects[1].primitives[0].type = shape_msgs::msg::SolidPrimitive::BOX;
        collision_objects[1].primitives[0].dimensions = {0.4, 0.6, 0.2};
        collision_objects[1].primitive_poses.resize(1);
        collision_objects[1].primitive_poses[0].position.x = 0.4;
        collision_objects[1].primitive_poses[0].position.y = 0.35;
        collision_objects[1].primitive_poses[0].position.z = 0.1;
        collision_objects[1].operation = moveit_msgs::msg::CollisionObject::ADD;

        collision_objects[2].id = "bin";
        collision_objects[2].header.frame_id = "world";
        collision_objects[2].primitives.resize(1);
        collision_objects[2].primitives[0].type = shape_msgs::msg::SolidPrimitive::BOX;
        collision_objects[2].primitives[0].dimensions = {0.24, 0.34, 0.1};
        collision_objects[2].primitive_poses.resize(1);
        collision_objects[2].primitive_poses[0].position.x = 0.4;
        collision_objects[2].primitive_poses[0].position.y = -0.35;
        collision_objects[2].primitive_poses[0].position.z = 0.2;
        collision_objects[2].operation = moveit_msgs::msg::CollisionObject::ADD;

         collision_objects[3].id = "tables_wall";
        collision_objects[3].header.frame_id = "world";
        collision_objects[3].primitives.resize(1);
        collision_objects[3].primitives[0].type = shape_msgs::msg::SolidPrimitive::BOX;
        collision_objects[3].primitives[0].dimensions = {0.4, 0.05, 1};
        collision_objects[3].primitive_poses.resize(1);
        collision_objects[3].primitive_poses[0].position.x = 0.4;
        collision_objects[3].primitive_poses[0].position.y = 0;
        collision_objects[3].primitive_poses[0].position.z = 0.1;
        collision_objects[3].operation = moveit_msgs::msg::CollisionObject::ADD;



        planning_scene_interface.applyCollisionObjects(collision_objects);
    };

    addCollisionObjects();

    // Gazebo + the camera + the controllers take several seconds to come up
    // after launch, so the first get_targets calls report "no target" simply
    // because VisionNode has no camera frame yet -- NOT because the table is
    // empty. Wait (with retries) for the first real detection before starting;
    // only *after* we've seen a cube does an empty result mean "table cleared".
    geometry_msgs::msg::Point target;
    bool have_target = false;
    for (int i = 0; i < 60 && rclcpp::ok(); ++i) {   // wait up to ~60 s
        if (search(target)) { have_target = true; break; }
        RCLCPP_INFO(logger, "Waiting for perception to produce a target... (%d)", i);
        std::this_thread::sleep_for(1s);
    }

    while (rclcpp::ok() && have_target) {
        pick(target.x, target.y, target.z);
        std::this_thread::sleep_for(2s);
        place();
        have_target = search(target);   // stop once the table has been cleared
    }


    rclcpp::shutdown();
    spin_thread.join();
    return 0;
}