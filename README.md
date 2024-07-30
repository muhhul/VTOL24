# VTOL24
Notes :
* Ini untuk test gate doang belum keseluruhan
* Ini pakai code OpenCV yg awal banget

Setup Model dsb: 
1. Pindahin file /src/drone/models/orange_obs -> catkin_ws/src/iq_sim/models  
    ATAU 
1. Masukin /src/drone/models/ ke path untuk model gazebo
2. cd ke root folder (cam_drone)
3. catkin_make di root folder
4. source devel/setup.sh 

Cara Jalanin : 
- catkin_make ulang untuk Aksan23 & cam_drone
- Run SITL
- cd ke cam_drone & source devel/setup.sh (atau masukin ke path)
- `roslaunch drone first_sim.launch`
- cd ke folder aksan23 & source devel/setup.sh (atau masukin ke path)
- `roslaunch env_percept vtol-cv.launch`
- `roslaunch uav_commander sitlgazebo-1.launch`
- `roslaunch uav_commander sitlgazebo-2.launch pilot_filename:=testGate.txt`
- `roslaunch uav_commander pid.launch`
- `rosrun uav_commander safety_node`
