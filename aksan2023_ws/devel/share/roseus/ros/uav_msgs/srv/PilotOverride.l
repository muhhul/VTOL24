;; Auto-generated. Do not edit!


(when (boundp 'uav_msgs::PilotOverride)
  (if (not (find-package "UAV_MSGS"))
    (make-package "UAV_MSGS"))
  (shadow 'PilotOverride (find-package "UAV_MSGS")))
(unless (find-package "UAV_MSGS::PILOTOVERRIDE")
  (make-package "UAV_MSGS::PILOTOVERRIDE"))
(unless (find-package "UAV_MSGS::PILOTOVERRIDEREQUEST")
  (make-package "UAV_MSGS::PILOTOVERRIDEREQUEST"))
(unless (find-package "UAV_MSGS::PILOTOVERRIDERESPONSE")
  (make-package "UAV_MSGS::PILOTOVERRIDERESPONSE"))

(in-package "ROS")





(defclass uav_msgs::PilotOverrideRequest
  :super ros::object
  :slots (_what ))

(defmethod uav_msgs::PilotOverrideRequest
  (:init
   (&key
    ((:what __what) "")
    )
   (send-super :init)
   (setq _what (string __what))
   self)
  (:what
   (&optional __what)
   (if __what (setq _what __what)) _what)
  (:serialization-length
   ()
   (+
    ;; string _what
    4 (length _what)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _what
       (write-long (length _what) s) (princ _what s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _what
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _what (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass uav_msgs::PilotOverrideResponse
  :super ros::object
  :slots (_result ))

(defmethod uav_msgs::PilotOverrideResponse
  (:init
   (&key
    ((:result __result) 0)
    )
   (send-super :init)
   (setq _result (round __result))
   self)
  (:result
   (&optional __result)
   (if __result (setq _result __result)) _result)
  (:serialization-length
   ()
   (+
    ;; uint8 _result
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _result
       (write-byte _result s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _result
     (setq _result (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(defclass uav_msgs::PilotOverride
  :super ros::object
  :slots ())

(setf (get uav_msgs::PilotOverride :md5sum-) "019550d9794152b525bf949a5e4ab378")
(setf (get uav_msgs::PilotOverride :datatype-) "uav_msgs/PilotOverride")
(setf (get uav_msgs::PilotOverride :request) uav_msgs::PilotOverrideRequest)
(setf (get uav_msgs::PilotOverride :response) uav_msgs::PilotOverrideResponse)

(defmethod uav_msgs::PilotOverrideRequest
  (:response () (instance uav_msgs::PilotOverrideResponse :init)))

(setf (get uav_msgs::PilotOverrideRequest :md5sum-) "019550d9794152b525bf949a5e4ab378")
(setf (get uav_msgs::PilotOverrideRequest :datatype-) "uav_msgs/PilotOverrideRequest")
(setf (get uav_msgs::PilotOverrideRequest :definition-)
      "# Available: LAND_SERV, RTL
string what
---
uint8 result

")

(setf (get uav_msgs::PilotOverrideResponse :md5sum-) "019550d9794152b525bf949a5e4ab378")
(setf (get uav_msgs::PilotOverrideResponse :datatype-) "uav_msgs/PilotOverrideResponse")
(setf (get uav_msgs::PilotOverrideResponse :definition-)
      "# Available: LAND_SERV, RTL
string what
---
uint8 result

")



(provide :uav_msgs/PilotOverride "019550d9794152b525bf949a5e4ab378")


