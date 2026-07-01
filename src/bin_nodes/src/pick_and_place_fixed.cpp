#include "rclcpp/rclcpp.hpp"
#include <moveit/move_group_interface/move_group_interface.h>
#include <geometry_msgs/msg/pose.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <thread>

using moveit::planning_interface::MoveGroupInterface;
int main(int argc, char **argv){
    rclcpp::init(argc, argv);

    auto node = std::make_shared<rclcpp::Node>("pick_and_place_fixed", rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true));
    auto logger = node->get_logger();

    rclcpp::executors::SingleThreadedExecutor executor;
    executor.add_node(node);
    std::thread spin_thread([&executor]() { executor.spin(); });

    MoveGroupInterface arm(node, "arm");
    arm.setMaxVelocityScalingFactor(0.3);
    arm.setMaxAccelerationScalingFactor(0.3);
    arm.setPlanningTime(5.0);

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
        plan_and_execute("pose target");
    };

    auto pick = [&](){
        goToPos(0.34, 0.347, 0.241,3.091, -1.412, 0.373);
    };

    auto place = [&](){
        goToPos(0.374, -0.215, 0.327,-0.898, -1.442, 2.633);
    };

    pick();
    place();


    rclcpp::shutdown();
    spin_thread.join();
    return 0;
}