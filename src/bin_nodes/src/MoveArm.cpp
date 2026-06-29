  #include <memory>
  #include <thread>
  #include <vector>
  #include <string>

  #include <rclcpp/rclcpp.hpp>
  #include <moveit/move_group_interface/move_group_interface.h>
  #include <geometry_msgs/msg/pose.hpp>

  using moveit::planning_interface::MoveGroupInterface;

  int main(int argc, char ** argv)
  {
    rclcpp::init(argc, argv);

    // automatically_declare_parameters_from_overrides(true) lets MoveGroupInterface
    // pick up robot_description / kinematics parameters that get passed in.
    auto node = std::make_shared<rclcpp::Node>(
      "move_arm",
      rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true));

    auto logger = node->get_logger();

    // MoveGroupInterface needs the node to be spinning in the background so it can
    // read the current robot state, TF, etc. Spin on a separate thread.
    rclcpp::executors::SingleThreadedExecutor executor;
    executor.add_node(node);
    std::thread spin_thread([&executor]() { executor.spin(); });

    // "arm" is the planning group name from your SRDF.
    MoveGroupInterface arm(node, "arm");
    arm.setMaxVelocityScalingFactor(0.3);      // 30% of joint speed limits
    arm.setMaxAccelerationScalingFactor(0.3);
    arm.setPlanningTime(5.0);

    RCLCPP_INFO(logger, "Planning frame:    %s", arm.getPlanningFrame().c_str());
    RCLCPP_INFO(logger, "End effector link: %s", arm.getEndEffectorLink().c_str());

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

    auto goToPose= [&](){
      // ---- 1) Go to a named pose defined in the SRDF (pose1..pose4) ----
      arm.setNamedTarget("pose1");
      plan_and_execute("pose1");
    };


    auto goToJointAngles= [&](){
      // ---- 2) Go to explicit joint angles, in radians, ordered j1..j6 ----
      std::vector<double> joints = {0.0, 0.5, -1.0, 0.0, 1.0, 0.0};
      arm.setJointValueTarget(joints);
      plan_and_execute("joint target");
    };

    auto goToPosition= [&](){
      // ---- 3) Go to a Cartesian pose for the tool (MoveIt solves the IK) ----
      geometry_msgs::msg::Pose target;
      target.position.x = 0.20;
      target.position.y = 0.00;
      target.position.z = 0.40;
      target.orientation.w = 0.707;   // identity orientation (x=y=z=0)
      arm.setPoseTarget(target);    // targets the end-effector link (tool_link)
      plan_and_execute("cartesian pose");
    };

    auto goToPositionMoreControl = [&](double x, double y, double z, double roll, double pitch, double yaw) {
      tf2::Quaternion q;
      q.setRPY(roll, pitch, yaw);

      geometry_msgs::msg::Pose target;
      target.position.x = x;
      target.position.y = y;
      target.position.z = z;
      target.orientation.x = q.x();
      target.orientation.y = q.y();
      target.orientation.z = q.z();
      target.orientation.w = q.w();

      arm.setPoseTarget(target);
      plan_and_execute("cartesian pose");
  };

  auto performanceTest = [&](){
    goToPositionMoreControl(0.20, 0.00, 0.40,  0, M_PI, 0);      // from above
    goToPositionMoreControl(0.20, 0.00, 0.40,  0, M_PI/2, 0);    // from front
    goToPositionMoreControl(0.20, 0.00, 0.40,  0, 0, 0);          // from below
    goToPositionMoreControl(0.20, 0.00, 0.40, 0, M_PI, M_PI/4);          // from below
  };

    // Usage:
    (void)goToPose();
    (void)goToJointAngles();
    (void)goToPosition();
    performanceTest();

    rclcpp::shutdown();
    spin_thread.join();
    return 0;
  }
