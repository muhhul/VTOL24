#!/bin/bash

tmux new-session -s 'vtol21' -d -n 'usb-cam'
tmux new-window -t 'vtol21' -d -n 'vtol-cv'
tmux send-keys -t 'vtol21:usb-cam' 'roslaunch env_percept vtol-3.launch front_cam_enable:=false down_cam_enable:=true' ENTER
tmux send-keys -t 'vtol21:vtol-cv' 'sleep 8; roslaunch env_percept vtol-cv.launch namespace:=raspi' ENTER
tmux attach -t 'vtol21'
exit 0
