from launch import LaunchDescription
from launch_ros.actions import Node
from moveit_configs_utils import MoveItConfigsBuilder


def generate_launch_description():
    # Same robot model move_group uses in gazebo.launch.py (root = world).
    moveit_config = (
        MoveItConfigsBuilder("robot_arm", package_name="moveit_config")
        .robot_description(mappings={"use_gazebo": "true"})
        .to_moveit_configs()
    )

    # A MoveGroupInterface node needs the URDF, SRDF and kinematics on its own
    # parameter server, plus sim time so it agrees with Gazebo's clock.
    # This does NOT start move_group/Gazebo/RViz -- run gazebo.launch.py first,
    # then run this in a second terminal.
    pick_and_place = Node(
        package="bin_nodes",
        executable="pick_and_place_fixed",
        output="screen",
        parameters=[
            moveit_config.robot_description,
            moveit_config.robot_description_semantic,
            moveit_config.robot_description_kinematics,
            {"use_sim_time": True},
        ],
    )

    return LaunchDescription([pick_and_place])
