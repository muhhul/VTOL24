# gnome-terminal --tab -e "sim_vehicle.py -v ArduCopter -f gazebo-iris -m --mav10 -I0"
gnome-terminal --tab -e "roslaunch uav_commander sitlgazebo-1.launch" read
gnome-terminal --tab -e "roslaunch uav_commander pid.launch"
gnome-terminal --tab -e "roslaunch env_percept vtol-cv.launch"
gnome-terminal --tab -e "roslaunch uav_commander sitlgazebo-2.launch _pilot_filename:="testPrecLand.txt" "
gnome-terminal --tab -e "rosrun uav_commander safety_node"