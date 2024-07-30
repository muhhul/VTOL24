;; Auto-generated. Do not edit!


(when (boundp 'uav_msgs::ReadQR)
  (if (not (find-package "UAV_MSGS"))
    (make-package "UAV_MSGS"))
  (shadow 'ReadQR (find-package "UAV_MSGS")))
(unless (find-package "UAV_MSGS::READQR")
  (make-package "UAV_MSGS::READQR"))

(in-package "ROS")
;;//! \htmlinclude ReadQR.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass uav_msgs::ReadQR
  :super ros::object
  :slots (_data _location ))

(defmethod uav_msgs::ReadQR
  (:init
   (&key
    ((:data __data) "")
    ((:location __location) ())
    )
   (send-super :init)
   (setq _data (string __data))
   (setq _location __location)
   self)
  (:data
   (&optional __data)
   (if __data (setq _data __data)) _data)
  (:location
   (&rest __location)
   (if (keywordp (car __location))
       (send* _location __location)
     (progn
       (if __location (setq _location (car __location)))
       _location)))
  (:serialization-length
   ()
   (+
    ;; string _data
    4 (length _data)
    ;; geometry_msgs/Point[] _location
    (apply #'+ (send-all _location :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _data
       (write-long (length _data) s) (princ _data s)
     ;; geometry_msgs/Point[] _location
     (write-long (length _location) s)
     (dolist (elem _location)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _data
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _data (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; geometry_msgs/Point[] _location
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _location (let (r) (dotimes (i n) (push (instance geometry_msgs::Point :init) r)) r))
     (dolist (elem- _location)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get uav_msgs::ReadQR :md5sum-) "0b97356b914a0ea80b810a8e728c804b")
(setf (get uav_msgs::ReadQR :datatype-) "uav_msgs/ReadQR")
(setf (get uav_msgs::ReadQR :definition-)
      "string data
#offset in meters
geometry_msgs/Point[] location

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :uav_msgs/ReadQR "0b97356b914a0ea80b810a8e728c804b")


