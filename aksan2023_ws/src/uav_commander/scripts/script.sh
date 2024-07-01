#!/bin/bash
tmux new-session -d -s 'vtol21' -n 'roscore'
tmux new-window -n 'mavros' -t 'vtol21'
tmux new-window -d -n 'lidar' -t 'vtol21'
tmux new-window -d -n 'localpose' -t 'vtol21'
tmux send-keys -t 'vtol21:roscore' 'roscore' ENTER
tmux send-keys -t 'vtol21:mavros' 'sleep 8; roslaunch uav_commander vtol-1.launch gcs_url:=udp://@192.168.0.101:14550' ENTER
tmux send-keys -t 'vtol21:lidar' 'sleep 16; roslaunch tfmini_ros tfmini.launch' ENTER
tmux send-keys -t 'vtol21:localpose' 'sleep 12; rostopic echo -c /mavros/local_position/pose' ENTER
tmux attach -t 'vtol21'
exit 0
