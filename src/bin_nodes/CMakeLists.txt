cmake_minimum_required(VERSION 3.8)
project(bin_nodes)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(moveit_ros_planning_interface REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(linkattacher_msgs REQUIRED)
find_package(moveit_msgs REQUIRED)
find_package(shape_msgs REQUIRED)
find_package(image_geometry REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)
find_package(sensor_msgs REQUIRED)


add_executable(MoveArm src/MoveArm.cpp)
target_include_directories(MoveArm PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(MoveArm PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(MoveArm
  rclcpp
  moveit_ros_planning_interface
  geometry_msgs)

add_executable(pick_and_place_fixed src/pick_and_place_fixed.cpp)
target_include_directories(pick_and_place_fixed PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(pick_and_place_fixed PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(pick_and_place_fixed
  rclcpp
  moveit_ros_planning_interface
  geometry_msgs
  tf2
  linkattacher_msgs)

add_executable(VisionNode src/VisionNode.cpp)
target_compile_features(VisionNode PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(VisionNode
  rclcpp
  cv_bridge
  sensor_msgs
  OpenCV
  image_geometry
  geometry_msgs)

install(TARGETS MoveArm pick_and_place_fixed VisionNode
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

install(DIRECTORY launch urdf rviz worlds
  DESTINATION share/${PROJECT_NAME})

ament_package()
