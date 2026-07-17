<div align="center">

# Vision-Guided Bin Picking — 6-DOF Robotic Arm

**Autonomous pick-and-place in ROS 2 & Gazebo, driven by a depth camera and MoveIt motion planning.**

A 6-DOF arm finds green cubes it has never been told the location of, computes each cube's 3D position from an overhead RGB-D camera, and plans **collision-free** trajectories to pick every cube and drop it into a bin — repeating until the table is clear.

![ROS 2](https://img.shields.io/badge/ROS_2-Humble-22314E?logo=ros&logoColor=white)
![MoveIt 2](https://img.shields.io/badge/MoveIt_2-Motion_Planning-0A7BBB)
![Gazebo](https://img.shields.io/badge/Gazebo-Classic-FF6C2C?logo=gazebo&logoColor=white)
![OpenCV](https://img.shields.io/badge/OpenCV-Perception-5C3EE8?logo=opencv&logoColor=white)
![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=cplusplus&logoColor=white)

</div>

---

## Demo

<table>
<tr>
<td width="50%" align="center">

### Full pick-and-place cycle

<img width="100%" alt="Arm picking cubes and placing them in the bin" src="https://github.com/user-attachments/assets/bf3cef15-7345-4798-b5e9-ff506b7af56c" />

</td>
<td width="50%" align="center">

### Robot model in RViz

<!-- Paste your RViz screenshot's <img ... /> tag here (drag-drop the file into GitHub's editor to get one). -->
<img width="100%" alt="rviz model arm" src="https://github.com/user-attachments/assets/085c6869-8e3f-430a-a7f2-79bbb3b9642a" />


</td>
</tr>
<tr>
<td width="50%" align="center">

### Live OctoMap

<img width="100%" alt="OctoMap occupancy grid" src="https://github.com/user-attachments/assets/bad09ef0-84bf-4e76-a141-e80ae7e0f4b6" />

</td>
<td width="50%" align="center">

### Vision node — detected cube, HSV, and green mask

<img width="100%" alt="VisionNode output: raw camera image with detected cube, HSV view, and green mask" src="https://github.com/user-attachments/assets/0646de4d-7334-4260-9403-1f3ab69673f0" />

</td>
</tr>
</table>

---

## Highlights

- **No hard-coded target positions** — the arm discovers where the cubes are purely from camera data at runtime.
- **Closed perception → planning → action loop** — vision detects a cube, a ROS 2 service hands over its 3D pose, MoveIt plans around obstacles, the arm executes, repeat until none remain.
- **Real collision avoidance** — tables, the bin, and a separating wall are registered in the MoveIt planning scene, and a live OctoMap is built from the depth stream, so every trajectory is verified collision-free before it runs.
- **Simulated grasping** — cubes are rigidly attached/detached to the gripper on contact via the IFRA LinkAttacher Gazebo plugin.
- **Written in modern C++17** across two ROS 2 nodes plus a custom service interface and a MoveIt Setup Assistant configuration.

---

## How It Works

```
 Overhead RGB-D camera (Gazebo)
        │  /camera/image_raw · /camera/depth/image_raw · /camera/camera_info
        ▼
 ┌──────────────────────────────┐        get_targets          ┌───────────────────────────────┐
 │  VisionNode  (OpenCV)         │   (bin_interfaces/srv)      │  pick_and_place_smart          │
 │  • HSV threshold → green mask │◄───────── request ──────────│  • MoveGroupInterface (arm +   │
 │  • largest contour + centroid │                             │    gripper)                    │
 │  • deproject pixel → 3D ray   │──────── PointStamped ──────►│  • OMPL plans around collision │
 │  • × depth, TF → robot_base   │      (found + cube pose)    │    objects + OctoMap           │
 └──────────────────────────────┘                             │  • attach → place → detach     │
                                                               └───────────────────────────────┘
                                                                             │
                                                                             ▼
                                                                MoveIt move_group + Gazebo
                                                                (trajectory execution)
```

**1. Detection —** `VisionNode` converts each camera frame to HSV, thresholds for green, cleans the mask with morphological open/close, and takes the largest contour's centroid. That pixel is deprojected into a 3D ray with the pinhole camera model, scaled by the depth image, and transformed via **tf2** into the arm's `robot_base` frame.

**2. Service —** the latest cube pose is served on demand through a custom `GetTargets` service (empty request → `bool found` + `geometry_msgs/PointStamped`). This lets the planner request one cube at a time and keep going until `found` is `false`.

**3. MoveIt planning —** `pick_and_place_smart` drives two planning groups (`arm`, `gripper`) through `MoveGroupInterface`. For every cube it plans an approach from above, closes the gripper, plans to the bin, and releases — all with velocity/acceleration scaling and a planning-time budget.

**4. Collision objects + OctoMap —** the two tables, the bin, and the wall between them are pushed into the planning scene as primitives via `PlanningSceneInterface`, and a `DepthImageOctomapUpdater` maintains an occupancy map from the depth sensor. MoveIt refuses any trajectory that would collide, so the arm reaches over the wall instead of through it.

**5. Grasp simulation —** since Gazebo friction alone won't reliably hold a cube, the node calls the **IFRA LinkAttacher** `/ATTACHLINK` and `/DETACHLINK` services to weld the cube to the wrist on pick and release it on place.

---

## Tech Stack

| Layer | Tools / Libraries |
|---|---|
| **Middleware** | ROS 2 **Humble** (`rclcpp`, custom `.srv` interface) |
| **Motion planning** | **MoveIt 2** (`moveit_ros_planning_interface`, OMPL, planning-scene + OctoMap) |
| **Simulation** | **Gazebo Classic**, `gazebo_ros2_control`, `ros2_control` controllers |
| **Perception** | **OpenCV**, `cv_bridge`, `image_geometry` (pinhole model), `tf2` / `tf2_ros` |
| **Grasping** | [IFRA_LinkAttacher](https://github.com/IFRA-Cranfield/IFRA_LinkAttacher) Gazebo plugin |
| **Robot model** | URDF/Xacro (6-DOF arm + parallel gripper), SRDF from MoveIt Setup Assistant |
| **Language / build** | C++17, `colcon`, `ament_cmake` |

---

## Repository Layout

```
src/
├── bin_nodes/          # C++ nodes, robot & camera URDFs, Gazebo world, launch files
│   ├── src/VisionNode.cpp           # perception + get_targets service
│   ├── src/pick_and_place_smart.cpp # planning + collision objects + pick/place loop
│   ├── urdf/ · worlds/ · launch/
├── bin_interfaces/     # GetTargets.srv (the vision → planner contract)
├── moveit_config/      # MoveIt Setup Assistant config + launch (move_group, controllers, OctoMap)
└── IFRA_LinkAttacher/  # Gazebo link-attacher plugin (grasp simulation)
```

---

## Getting Started

### Prerequisites
- Ubuntu 22.04 + **ROS 2 Humble**
- **Gazebo Classic**, MoveIt 2, and `ros2_control` / `gazebo_ros2_control`

```bash
sudo apt install ros-humble-moveit ros-humble-gazebo-ros-pkgs \
  ros-humble-gazebo-ros2-control ros-humble-ros2-control \
  ros-humble-ros2-controllers ros-humble-cv-bridge ros-humble-image-geometry
```

### Clone & build

> **Note:** `IFRA_LinkAttacher` is referenced but not bundled, so clone it separately into `src/` before building.

```bash
# 1. Clone the workspace
git clone https://github.com/IbrahimZantoutt/Bin-Picking-6DOF-Robotic-Arm-Moveit.git BinPicking
cd BinPicking

# 2. Add the grasp plugin (humble branch)
git clone -b humble https://github.com/IFRA-Cranfield/IFRA_LinkAttacher.git src/IFRA_LinkAttacher

# 3. Build & source
colcon build --symlink-install
source install/setup.bash
```

### Run

```bash
# Terminal 1 — Gazebo world, robot, controllers, MoveIt move_group + RViz
ros2 launch moveit_config gazebo.launch.py

# Terminal 2 — the full mission: perception node + autonomous pick-and-place loop
ros2 launch moveit_config mission.launch.py
```

`mission.launch.py` starts `VisionNode` (green-cube detection + `get_targets` service),
then launches the pick-and-place loop a few seconds later so perception has a detection
ready. Tune the wait with `mission_delay` if needed:

```bash
ros2 launch moveit_config mission.launch.py mission_delay:=8.0
```

The arm will now clear every green cube from the table into the bin, planning around the tables and wall on each cycle.

---

<div align="center">

*Built by [Ibrahim Zantout](https://github.com/IbrahimZantoutt) — robotics, perception & motion planning in ROS 2.*

</div>
