import os
import re

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, RegisterEventHandler
from launch.event_handlers import OnProcessExit
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from moveit_configs_utils import MoveItConfigsBuilder


def generate_launch_description():
    # Build the MoveIt config, telling xacro to use the Gazebo hardware plugin
    # (use_gazebo:=true also adds the `world` link + gazebo_ros2_control plugin).
    moveit_config = (
        MoveItConfigsBuilder("robot_arm", package_name="moveit_config")
        .robot_description(mappings={"use_gazebo": "true"})
        .to_moveit_configs()
    )

    # --- Gazebo Classic, loading our world ----------------------------------
    world_file = os.path.join(
        get_package_share_directory("bin_nodes"), "worlds", "world.sdf"
    )
    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(
                get_package_share_directory("gazebo_ros"),
                "launch",
                "gazebo.launch.py",
            )
        ),
        launch_arguments={"world": world_file, "verbose": "true"}.items(),
    )

    # --- robot_state_publisher feeds /robot_description ----------------------
    # gazebo_ros2_control reads robot_description from robot_state_publisher and
    # forwards it to the controller_manager as a `--param robot_description:=<xml>`
    # override. On Humble, rcl cannot parse that value if it contains the xacro
    # `<?xml?>` declaration or `<!-- -->` comment banner, so the controller_manager
    # silently fails to start and the arm collapses. Strip both before publishing.
    robot_description_xml = moveit_config.robot_description["robot_description"]
    robot_description_xml = re.sub(r"<\?xml[^>]*\?>", "", robot_description_xml)
    robot_description_xml = re.sub(r"<!--.*?-->", "", robot_description_xml, flags=re.DOTALL)

    # Everything must share Gazebo's /clock, or MoveIt (wall clock) and the
    # controller_manager (sim clock) disagree on trajectory timestamps and
    # execution fails with "controller failed during execution".
    use_sim_time = {"use_sim_time": True}

    robot_state_publisher = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        output="screen",
        parameters=[{"robot_description": robot_description_xml}, use_sim_time],
    )

    # --- Spawn the robot into Gazebo from the /robot_description topic -------
    spawn_entity = Node(
        package="gazebo_ros",
        executable="spawn_entity.py",
        arguments=["-topic", "robot_description", "-entity", "robot_arm"],
        output="screen",
    )

    # --- Controllers (spawned in order, once the robot exists in Gazebo) -----
    joint_state_broadcaster = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["joint_state_broadcaster", "-c", "/controller_manager"],
    )
    arm_controller = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["arm_controller", "-c", "/controller_manager"],
    )
    gripper_controller = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["gripper_controller", "-c", "/controller_manager"],
    )

    # --- MoveIt move_group ---------------------------------------------------
    move_group = Node(
        package="moveit_ros_move_group",
        executable="move_group",
        output="screen",
        parameters=[moveit_config.to_dict(), use_sim_time],
    )

    # --- RViz with the MoveIt motion planning display -----------------------
    rviz_config = os.path.join(
        get_package_share_directory("moveit_config"), "config", "moveit.rviz"
    )
    rviz = Node(
        package="rviz2",
        executable="rviz2",
        output="screen",
        arguments=["-d", rviz_config],
        parameters=[
            moveit_config.robot_description,
            moveit_config.robot_description_semantic,
            moveit_config.robot_description_kinematics,
            moveit_config.planning_pipelines,
            moveit_config.joint_limits,
            use_sim_time,
        ],
    )

    return LaunchDescription(
        [
            gazebo,
            robot_state_publisher,
            spawn_entity,
            move_group,
            rviz,
            # Chain the spawners so they start only after the robot is spawned.
            RegisterEventHandler(
                OnProcessExit(
                    target_action=spawn_entity,
                    on_exit=[joint_state_broadcaster],
                )
            ),
            RegisterEventHandler(
                OnProcessExit(
                    target_action=joint_state_broadcaster,
                    on_exit=[arm_controller],
                )
            ),
            RegisterEventHandler(
                OnProcessExit(
                    target_action=arm_controller,
                    on_exit=[gripper_controller],
                )
            ),
        ]
    )
