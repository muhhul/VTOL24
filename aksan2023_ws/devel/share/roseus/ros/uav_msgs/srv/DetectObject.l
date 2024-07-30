;; Auto-generated. Do not edit!


(when (boundp 'uav_msgs::DetectObject)
  (if (not (find-package "UAV_MSGS"))
    (make-package "UAV_MSGS"))
  (shadow 'DetectObject (find-package "UAV_MSGS")))
(unless (find-package "UAV_MSGS::DETECTOBJECT")
  (make-package "UAV_MSGS::DETECTOBJECT"))
(unless (find-package "UAV_MSGS::DETECTOBJECTREQUEST")
  (make-package "UAV_MSGS::DETECTOBJECTREQUEST"))
(unless (find-package "UAV_MSGS::DETECTOBJECTRESPONSE")
  (make-package "UAV_MSGS::DETECTOBJECTRESPONSE"))

(in-package "ROS")





(defclass uav_msgs::DetectObjectRequest
  :super ros::object
  :slots (_name ))

(defmethod uav_msgs::DetectObjectRequest
  (:init
   (&key
    ((:name __name) "")
    )
   (send-super :init)
   (setq _name (string __name))
   self)
  (:name
   (&optional __name)
   (if __name (setq _name __name)) _name)
  (:serialization-length
   ()
   (+
    ;; string _name
    4 (length _name)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _name
       (write-long (length _name) s) (princ _name s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass uav_msgs::DetectObjectResponse
  :super ros::object
  :slots (_scanELP _scanDZ _scanQRPos _scanDistX _scanGate ))

(defmethod uav_msgs::DetectObjectResponse
  (:init
   (&key
    ((:scanELP __scanELP) nil)
    ((:scanDZ __scanDZ) nil)
    ((:scanQRPos __scanQRPos) nil)
    ((:scanDistX __scanDistX) nil)
    ((:scanGate __scanGate) nil)
    )
   (send-super :init)
   (setq _scanELP __scanELP)
   (setq _scanDZ __scanDZ)
   (setq _scanQRPos __scanQRPos)
   (setq _scanDistX __scanDistX)
   (setq _scanGate __scanGate)
   self)
  (:scanELP
   (&optional (__scanELP :null))
   (if (not (eq __scanELP :null)) (setq _scanELP __scanELP)) _scanELP)
  (:scanDZ
   (&optional (__scanDZ :null))
   (if (not (eq __scanDZ :null)) (setq _scanDZ __scanDZ)) _scanDZ)
  (:scanQRPos
   (&optional (__scanQRPos :null))
   (if (not (eq __scanQRPos :null)) (setq _scanQRPos __scanQRPos)) _scanQRPos)
  (:scanDistX
   (&optional (__scanDistX :null))
   (if (not (eq __scanDistX :null)) (setq _scanDistX __scanDistX)) _scanDistX)
  (:scanGate
   (&optional (__scanGate :null))
   (if (not (eq __scanGate :null)) (setq _scanGate __scanGate)) _scanGate)
  (:serialization-length
   ()
   (+
    ;; bool _scanELP
    1
    ;; bool _scanDZ
    1
    ;; bool _scanQRPos
    1
    ;; bool _scanDistX
    1
    ;; bool _scanGate
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _scanELP
       (if _scanELP (write-byte -1 s) (write-byte 0 s))
     ;; bool _scanDZ
       (if _scanDZ (write-byte -1 s) (write-byte 0 s))
     ;; bool _scanQRPos
       (if _scanQRPos (write-byte -1 s) (write-byte 0 s))
     ;; bool _scanDistX
       (if _scanDistX (write-byte -1 s) (write-byte 0 s))
     ;; bool _scanGate
       (if _scanGate (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _scanELP
     (setq _scanELP (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _scanDZ
     (setq _scanDZ (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _scanQRPos
     (setq _scanQRPos (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _scanDistX
     (setq _scanDistX (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _scanGate
     (setq _scanGate (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass uav_msgs::DetectObject
  :super ros::object
  :slots ())

(setf (get uav_msgs::DetectObject :md5sum-) "a025889287f882ec66648bcea0082302")
(setf (get uav_msgs::DetectObject :datatype-) "uav_msgs/DetectObject")
(setf (get uav_msgs::DetectObject :request) uav_msgs::DetectObjectRequest)
(setf (get uav_msgs::DetectObject :response) uav_msgs::DetectObjectResponse)

(defmethod uav_msgs::DetectObjectRequest
  (:response () (instance uav_msgs::DetectObjectResponse :init)))

(setf (get uav_msgs::DetectObjectRequest :md5sum-) "a025889287f882ec66648bcea0082302")
(setf (get uav_msgs::DetectObjectRequest :datatype-) "uav_msgs/DetectObjectRequest")
(setf (get uav_msgs::DetectObjectRequest :definition-)
      "string name
---
bool scanELP
bool scanDZ
bool scanQRPos
bool scanDistX
bool scanGate

")

(setf (get uav_msgs::DetectObjectResponse :md5sum-) "a025889287f882ec66648bcea0082302")
(setf (get uav_msgs::DetectObjectResponse :datatype-) "uav_msgs/DetectObjectResponse")
(setf (get uav_msgs::DetectObjectResponse :definition-)
      "string name
---
bool scanELP
bool scanDZ
bool scanQRPos
bool scanDistX
bool scanGate

")



(provide :uav_msgs/DetectObject "a025889287f882ec66648bcea0082302")


