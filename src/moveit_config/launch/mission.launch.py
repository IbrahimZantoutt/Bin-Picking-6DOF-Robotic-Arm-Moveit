from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, TimerAction
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from moveit_configs_utils import MoveItConfigsBuilder


def generate_launch_description():
    # How long to wait after starting VisionNode before launching the
    # pick-and-place loop. This gives VisionNode time to receive its first
    # camera frames and produce a detection -- pick_and_place_smart stops as
    # soon as get_targets reports "no target", so it must not run first.
    mission_delay = DeclareLaunchArgument(
        "mission_delay",
        default_value="3.0",
        description="Seconds to wait before starting the pick-and-place loop.",
    )

    # Same robot model move_group uses in gazebo.launch.py (root = world).
    # Needed so the MoveGroupInterface node has the URDF/SRDF/kinematics on its
    # own parameter server, plus sim time so it agrees with Gazebo's clock.
    moveit_config = (
        MoveItConfigsBuilder("robot_arm", package_name="moveit_config")
        .robot_description(mappings={"use_gazebo": "true"})
        .to_moveit_configs()
    )

    # Perception: green-cube detection + get_targets service. Runs immediately.
    vision_node = Node(
        package="bin_nodes",
        executable="VisionNode",
        output="screen",
    )

    # Planning + pick/place loop. Started after a short delay so the vision
    # service is up and already has a detection to hand out.
    pick_and_place = Node(
        package="bin_nodes",
        executable="pick_and_place_smart",
        output="screen",
        parameters=[
            moveit_config.robot_description,
            moveit_config.robot_description_semantic,
            moveit_config.robot_description_kinematics,
            {"use_sim_time": True},
        ],
    )

    delayed_pick_and_place = TimerAction(
        period=LaunchConfiguration("mission_delay"),
        actions=[pick_and_place],
    )

    return LaunchDescription([mission_delay, vision_node, delayed_pick_and_place])
