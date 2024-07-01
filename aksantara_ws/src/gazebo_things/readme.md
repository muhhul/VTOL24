### Implementasi Realsense Tracking Camera - Gazebo

**To do**:
- Kamera realsense harusnya greyscale, belum diubah di modelnya
- (OOT) Model (sdf) kamera webcam (gimbal-small-2d) belum dicrosscheck dengan spesifikasi logitech C310

**Dependencies**:
- Gazebo, ROS, SITL Ardupilot
- Plugin `SwiftGust`, see [here](https://github.com/SwiftGust/ardupilot_gazebo)
- `gazebo_ros_pkgs`
- File `sitl_tf_to_mavros.launch` in pkg `vision_to_mavros`

**Setup**:
- Copy `vtol2021.launch` to `/opt/ros/noetic/share/gazebo_ros/launch`
- (kalau belum) `echo "source /usr/share/gazebo-11/setup.sh" >> ~/.bashrc`
- `echo "export GAZEBO_MODEL_PATH=$GAZEBO_MODEL_PATH:PATH_TO_HERE/models" >> ~/.bashrc`
- `echo "export GAZEBO_PLUGIN_PATH=$GAZEBO_PLUGIN_PATH:/opt/ros/noetic/lib" >> ~/.bashrc`
- `echo "export GAZEBO_RESOURCE_PATH=$GAZEBO_RESOURCE_PATH:PATH_TO_HERE/" >> ~/.bashrc`
- Buka SITL, `param load PATH_TO_HERE/vtol21.parm`
- Kedepannya buka SITL di folder yang sama dengan folder poin sebelumnya supaya param nya tidak reset.

**Usage**:
- `roslaunch gazebo_ros vtol2021.launch`
- `sim_vehicle.py -v ArduCopter -f gazebo-iris --console`
- `roslaunch uav_commander sitlgazebo-1.launch`
- `roslaunch uav_commander sitlgazebo-2.launch`
a
