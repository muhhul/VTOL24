#!/bin/bash
tmux new-session -d -s 'vtol21' -n 'roscore'
tmux new-window -n 'mavros' -t 'vtol21'
tmux new-window -n 'env_percept' -t 'vtol21'
tmux new-window -d -n 'pid' -t 'vtol21'
tmux new-window -d -n 'board' -t 'vtol21'
tmux split-window -t 'vtol21:env_percept' -v
tmux send-keys -t 'vtol21:roscore' 'roscore' ENTER
tmux send-keys -t 'vtol21:mavros' 'sleep 8; roslaunch uav_commander vtol-1.launch gcs_url:=udp://@192.168.0.101:14550' ENTER
tmux send-keys -t 'vtol21:env_percept.0' 'sleep 8; roslaunch env_percept vtol-3.launch front_cam_enable:=true down_cam_enable:=false videodev_front:=0' ENTER
tmux send-keys -t 'vtol21:env_percept.1' 'sleep 12; roslaunch env_percept vtol-cv.launch namespace:=odroid' ENTER
tmux send-keys -t 'vtol21:pid' 'sleep 16; roslaunch uav_commander pid.launch' ENTER
tmux send-keys -t 'vtol21:board' 'sleep 16; roslaunch tfmini_ros tfmini.launch' ENTER
tmux split-window -t 'vtol21:board' -v
tmux split-window -t 'vtol21:board.1' -h
tmux resize-pane -t 'vtol21:board.1' -y 30
tmux resize-pane -t 'vtol21:board.2' -x 15
tmux split-window -t 'vtol21:board.2' -v
tmux resize-pane -t 'vtol21:board.3' -y 15
tmux send-keys -t 'vtol21:board.1' 'roslaunch uav_commander vtol-2.launch pilot_filename:='
tmux send-keys -t 'vtol21:board.2' 'sleep 16; rostopic hz /tfmini_node_asli/TFmini' ENTER
tmux send-keys -t 'vtol21:board.3' 'sleep 16; rostopic hz /tfmini_node_atas/TFmini' ENTER
tmux new-window -d -n 'lidars' -t 'vtol21'
tmux split-window -t 'vtol21:lidars' -v
tmux split-window -t 'vtol21:lidars.0' -h
tmux split-window -t 'vtol21:lidars.2' -h
tmux send-keys -t 'vtol21:lidars.0' 'rostopic echo -n1 /tfmini_node_atas/TFmini'
tmux send-keys -t 'vtol21:lidars.1' 'rostopic echo -n1 /tfmini_node_asli/TFmini'
tmux send-keys -t 'vtol21:lidars.2' 'rostopic echo -n1 /mavros/distance_sensor/rangefinder_sub'
tmux send-keys -t 'vtol21:lidars.3' 'sleep 16; rostopic hz /mavros/distance_sensor/rangefinder_sub' ENTER
tmux swap-window -s 'vtol21:lidars' -t 'vtol21:board'
tmux attach -t 'vtol21:board'
exit 0
