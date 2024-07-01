;; Auto-generated. Do not edit!


(when (boundp 'uav_msgs::DzPosition)
  (if (not (find-package "UAV_MSGS"))
    (make-package "UAV_MSGS"))
  (shadow 'DzPosition (find-package "UAV_MSGS")))
(unless (find-package "UAV_MSGS::DZPOSITION")
  (make-package "UAV_MSGS::DZPOSITION"))

(in-package "ROS")
;;//! \htmlinclude DzPosition.msg.html


(defclass uav_msgs::DzPosition
  :super ros::object
  :slots (_dist_x _dist_y ))

(defmethod uav_msgs::DzPosition
  (:init
   (&key
    ((:dist_x __dist_x) 0.0)
    ((:dist_y __dist_y) 0.0)
    )
   (send-super :init)
   (setq _dist_x (float __dist_x))
   (setq _dist_y (float __dist_y))
   self)
  (:dist_x
   (&optional __dist_x)
   (if __dist_x (setq _dist_x __dist_x)) _dist_x)
  (:dist_y
   (&optional __dist_y)
   (if __dist_y (setq _dist_y __dist_y)) _dist_y)
  (:serialization-length
   ()
   (+
    ;; float64 _dist_x
    8
    ;; float64 _dist_y
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _dist_x
       (sys::poke _dist_x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _dist_y
       (sys::poke _dist_y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _dist_x
     (setq _dist_x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _dist_y
     (setq _dist_y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get uav_msgs::DzPosition :md5sum-) "548475a5e014d2e321e9481e359821fc")
(setf (get uav_msgs::DzPosition :datatype-) "uav_msgs/DzPosition")
(setf (get uav_msgs::DzPosition :definition-)
      "float64 dist_x
float64 dist_y

")



(provide :uav_msgs/DzPosition "548475a5e014d2e321e9481e359821fc")


