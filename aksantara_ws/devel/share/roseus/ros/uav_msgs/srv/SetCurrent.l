;; Auto-generated. Do not edit!


(when (boundp 'uav_msgs::SetCurrent)
  (if (not (find-package "UAV_MSGS"))
    (make-package "UAV_MSGS"))
  (shadow 'SetCurrent (find-package "UAV_MSGS")))
(unless (find-package "UAV_MSGS::SETCURRENT")
  (make-package "UAV_MSGS::SETCURRENT"))
(unless (find-package "UAV_MSGS::SETCURRENTREQUEST")
  (make-package "UAV_MSGS::SETCURRENTREQUEST"))
(unless (find-package "UAV_MSGS::SETCURRENTRESPONSE")
  (make-package "UAV_MSGS::SETCURRENTRESPONSE"))

(in-package "ROS")





(defclass uav_msgs::SetCurrentRequest
  :super ros::object
  :slots (_data ))

(defmethod uav_msgs::SetCurrentRequest
  (:init
   (&key
    ((:data __data) 0)
    )
   (send-super :init)
   (setq _data (round __data))
   self)
  (:data
   (&optional __data)
   (if __data (setq _data __data)) _data)
  (:serialization-length
   ()
   (+
    ;; int32 _data
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _data
       (write-long _data s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _data
     (setq _data (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(defclass uav_msgs::SetCurrentResponse
  :super ros::object
  :slots (_success ))

(defmethod uav_msgs::SetCurrentResponse
  (:init
   (&key
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _success __success)
   self)
  (:success
   (&optional (__success :null))
   (if (not (eq __success :null)) (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; bool _success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass uav_msgs::SetCurrent
  :super ros::object
  :slots ())

(setf (get uav_msgs::SetCurrent :md5sum-) "65058a332cdf9eddf11f34077a0b92a4")
(setf (get uav_msgs::SetCurrent :datatype-) "uav_msgs/SetCurrent")
(setf (get uav_msgs::SetCurrent :request) uav_msgs::SetCurrentRequest)
(setf (get uav_msgs::SetCurrent :response) uav_msgs::SetCurrentResponse)

(defmethod uav_msgs::SetCurrentRequest
  (:response () (instance uav_msgs::SetCurrentResponse :init)))

(setf (get uav_msgs::SetCurrentRequest :md5sum-) "65058a332cdf9eddf11f34077a0b92a4")
(setf (get uav_msgs::SetCurrentRequest :datatype-) "uav_msgs/SetCurrentRequest")
(setf (get uav_msgs::SetCurrentRequest :definition-)
      "int32 data
---
bool success

")

(setf (get uav_msgs::SetCurrentResponse :md5sum-) "65058a332cdf9eddf11f34077a0b92a4")
(setf (get uav_msgs::SetCurrentResponse :datatype-) "uav_msgs/SetCurrentResponse")
(setf (get uav_msgs::SetCurrentResponse :definition-)
      "int32 data
---
bool success

")



(provide :uav_msgs/SetCurrent "65058a332cdf9eddf11f34077a0b92a4")


