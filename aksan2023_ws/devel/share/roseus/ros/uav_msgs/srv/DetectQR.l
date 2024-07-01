;; Auto-generated. Do not edit!


(when (boundp 'uav_msgs::DetectQR)
  (if (not (find-package "UAV_MSGS"))
    (make-package "UAV_MSGS"))
  (shadow 'DetectQR (find-package "UAV_MSGS")))
(unless (find-package "UAV_MSGS::DETECTQR")
  (make-package "UAV_MSGS::DETECTQR"))
(unless (find-package "UAV_MSGS::DETECTQRREQUEST")
  (make-package "UAV_MSGS::DETECTQRREQUEST"))
(unless (find-package "UAV_MSGS::DETECTQRRESPONSE")
  (make-package "UAV_MSGS::DETECTQRRESPONSE"))

(in-package "ROS")





(defclass uav_msgs::DetectQRRequest
  :super ros::object
  :slots (_name ))

(defmethod uav_msgs::DetectQRRequest
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

(defclass uav_msgs::DetectQRResponse
  :super ros::object
  :slots (_scanQR _data ))

(defmethod uav_msgs::DetectQRResponse
  (:init
   (&key
    ((:scanQR __scanQR) nil)
    ((:data __data) "")
    )
   (send-super :init)
   (setq _scanQR __scanQR)
   (setq _data (string __data))
   self)
  (:scanQR
   (&optional (__scanQR :null))
   (if (not (eq __scanQR :null)) (setq _scanQR __scanQR)) _scanQR)
  (:data
   (&optional __data)
   (if __data (setq _data __data)) _data)
  (:serialization-length
   ()
   (+
    ;; bool _scanQR
    1
    ;; string _data
    4 (length _data)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _scanQR
       (if _scanQR (write-byte -1 s) (write-byte 0 s))
     ;; string _data
       (write-long (length _data) s) (princ _data s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _scanQR
     (setq _scanQR (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; string _data
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _data (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass uav_msgs::DetectQR
  :super ros::object
  :slots ())

(setf (get uav_msgs::DetectQR :md5sum-) "35ea94070a2b21ef0ad43c5c3a092789")
(setf (get uav_msgs::DetectQR :datatype-) "uav_msgs/DetectQR")
(setf (get uav_msgs::DetectQR :request) uav_msgs::DetectQRRequest)
(setf (get uav_msgs::DetectQR :response) uav_msgs::DetectQRResponse)

(defmethod uav_msgs::DetectQRRequest
  (:response () (instance uav_msgs::DetectQRResponse :init)))

(setf (get uav_msgs::DetectQRRequest :md5sum-) "35ea94070a2b21ef0ad43c5c3a092789")
(setf (get uav_msgs::DetectQRRequest :datatype-) "uav_msgs/DetectQRRequest")
(setf (get uav_msgs::DetectQRRequest :definition-)
      "string name
---
bool scanQR
string data

")

(setf (get uav_msgs::DetectQRResponse :md5sum-) "35ea94070a2b21ef0ad43c5c3a092789")
(setf (get uav_msgs::DetectQRResponse :datatype-) "uav_msgs/DetectQRResponse")
(setf (get uav_msgs::DetectQRResponse :definition-)
      "string name
---
bool scanQR
string data

")



(provide :uav_msgs/DetectQR "35ea94070a2b21ef0ad43c5c3a092789")


