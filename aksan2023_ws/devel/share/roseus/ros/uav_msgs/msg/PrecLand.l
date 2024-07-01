;; Auto-generated. Do not edit!


(when (boundp 'uav_msgs::PrecLand)
  (if (not (find-package "UAV_MSGS"))
    (make-package "UAV_MSGS"))
  (shadow 'PrecLand (find-package "UAV_MSGS")))
(unless (find-package "UAV_MSGS::PRECLAND")
  (make-package "UAV_MSGS::PRECLAND"))

(in-package "ROS")
;;//! \htmlinclude PrecLand.msg.html


(defclass uav_msgs::PrecLand
  :super ros::object
  :slots (_size_x _size_y _angle_x _angle_y _distance ))

(defmethod uav_msgs::PrecLand
  (:init
   (&key
    ((:size_x __size_x) 0.0)
    ((:size_y __size_y) 0.0)
    ((:angle_x __angle_x) 0.0)
    ((:angle_y __angle_y) 0.0)
    ((:distance __distance) 0.0)
    )
   (send-super :init)
   (setq _size_x (float __size_x))
   (setq _size_y (float __size_y))
   (setq _angle_x (float __angle_x))
   (setq _angle_y (float __angle_y))
   (setq _distance (float __distance))
   self)
  (:size_x
   (&optional __size_x)
   (if __size_x (setq _size_x __size_x)) _size_x)
  (:size_y
   (&optional __size_y)
   (if __size_y (setq _size_y __size_y)) _size_y)
  (:angle_x
   (&optional __angle_x)
   (if __angle_x (setq _angle_x __angle_x)) _angle_x)
  (:angle_y
   (&optional __angle_y)
   (if __angle_y (setq _angle_y __angle_y)) _angle_y)
  (:distance
   (&optional __distance)
   (if __distance (setq _distance __distance)) _distance)
  (:serialization-length
   ()
   (+
    ;; float64 _size_x
    8
    ;; float64 _size_y
    8
    ;; float64 _angle_x
    8
    ;; float64 _angle_y
    8
    ;; float64 _distance
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _size_x
       (sys::poke _size_x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _size_y
       (sys::poke _size_y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _angle_x
       (sys::poke _angle_x (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _angle_y
       (sys::poke _angle_y (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _distance
       (sys::poke _distance (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _size_x
     (setq _size_x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _size_y
     (setq _size_y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _angle_x
     (setq _angle_x (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _angle_y
     (setq _angle_y (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _distance
     (setq _distance (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get uav_msgs::PrecLand :md5sum-) "af195082e2bf6647fe0e1655a101af72")
(setf (get uav_msgs::PrecLand :datatype-) "uav_msgs/PrecLand")
(setf (get uav_msgs::PrecLand :definition-)
      "float64 size_x
float64 size_y
float64 angle_x
float64 angle_y
float64 distance

")



(provide :uav_msgs/PrecLand "af195082e2bf6647fe0e1655a101af72")


