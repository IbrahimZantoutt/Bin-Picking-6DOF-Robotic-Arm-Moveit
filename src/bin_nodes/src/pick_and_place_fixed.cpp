#include "rclcpp/rclcpp.hpp"
#include <moveit/move_group_interface/move_group_interface.h>
#include <geometry_msgs/msg/pose.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <linkattacher_msgs/srv/attach_link.hpp>
#include <linkattacher_msgs/srv/detach_link.hpp>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

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
        //goToPos(0.304, 0.339, 0.247,2.863, 1.389, -3.141);  better to add when added collision aware movement
        goToPos(0.34, 0.347, 0.241,3.091, -1.412, 0.373);
        attach("robot_arm", "wrist_yaw_link", "green_cube", "link");
    };

    auto place = [&](){
        //goToPos(0.374, -0.215, 0.327,-0.898, -1.442, 2.633);
        goToPos(0.313, -0.309, 0.379,3.141, 1.390, 3.142);
        detach("robot_arm", "wrist_yaw_link", "green_cube", "link");
    };

    pick();

    //sleep is needed for a little delay until the arm has setteled down
    std::this_thread::sleep_for(2s);

    place();


    rclcpp::shutdown();
    spin_thread.join();
    return 0;
}