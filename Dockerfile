FROM ros:humble
WORKDIR /BinPicking

# --- Large, stable deps: installed once in this cached layer (before COPY src)
# --- so editing source doesn't re-download them on every rebuild. rosdep (below)
# --- then only fetches the small, fast-changing long tail.
RUN apt-get update && \
    apt-get install -y \
      ros-humble-moveit \
      ros-humble-gazebo-ros-pkgs \
      ros-humble-gazebo-ros2-control \
      ros-humble-ros2-controllers \
      ros-humble-rviz2 \
      libopencv-dev \
      python3-rosdep && \
    rm -rf /var/lib/apt/lists/*

COPY src src

RUN apt-get update && \
    rosdep update && \
    rosdep install --from-paths src --ignore-src -r -y && \
    rm -rf /var/lib/apt/lists/*

RUN . /opt/ros/humble/setup.sh && colcon build