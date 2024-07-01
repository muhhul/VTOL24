;; Auto-generated. Do not edit!


(when (boundp 'uav_msgs::MissionParams)
  (if (not (find-package "UAV_MSGS"))
    (make-package "UAV_MSGS"))
  (shadow 'MissionParams (find-package "UAV_MSGS")))
(unless (find-package "UAV_MSGS::MISSIONPARAMS")
  (make-package "UAV_MSGS::MISSIONPARAMS"))

(in-package "ROS")
;;//! \htmlinclude MissionParams.msg.html


(defclass uav_msgs::MissionParams
  :super ros::object
  :slots (_bools _ints _strings _doubles ))

(defmethod uav_msgs::MissionParams
  (:init
   (&key
    ((:bools __bools) (let (r) (dotimes (i 0) (push nil r)) r))
    ((:ints __ints) (make-array 0 :initial-element 0 :element-type :integer))
    ((:strings __strings) (let (r) (dotimes (i 0) (push "" r)) r))
    ((:doubles __doubles) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _bools __bools)
   (setq _ints __ints)
   (setq _strings __strings)
   (setq _doubles __doubles)
   self)
  (:bools
   (&optional __bools)
   (if __bools (setq _bools __bools)) _bools)
  (:ints
   (&optional __ints)
   (if __ints (setq _ints __ints)) _ints)
  (:strings
   (&optional __strings)
   (if __strings (setq _strings __strings)) _strings)
  (:doubles
   (&optional __doubles)
   (if __doubles (setq _doubles __doubles)) _doubles)
  (:serialization-length
   ()
   (+
    ;; bool[] _bools
    (* 1    (length _bools)) 4
    ;; int16[] _ints
    (* 2    (length _ints)) 4
    ;; string[] _strings
    (apply #'+ (mapcar #'(lambda (x) (+ 4 (length x))) _strings)) 4
    ;; float64[] _doubles
    (* 8    (length _doubles)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool[] _bools
     (write-long (length _bools) s)
     (dotimes (i (length _bools))
       (if (elt _bools i) (write-byte -1 s) (write-byte 0 s))
       )
     ;; int16[] _ints
     (write-long (length _ints) s)
     (dotimes (i (length _ints))
       (write-word (elt _ints i) s)
       )
     ;; string[] _strings
     (write-long (length _strings) s)
     (dolist (elem _strings)
       (write-long (length elem) s) (princ elem s)
       )
     ;; float64[] _doubles
     (write-long (length _doubles) s)
     (dotimes (i (length _doubles))
       (sys::poke (elt _doubles i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool[] _bools
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _bools (make-list n))
     (dotimes (i n)
     (setf (elt _bools i) (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
     ))
   ;; int16[] _ints
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _ints (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _ints i) (sys::peek buf ptr- :short)) (incf ptr- 2)
     ))
   ;; string[] _strings
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _strings (make-list n))
     (dotimes (i n)
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setf (elt _strings i) (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
     ))
   ;; float64[] _doubles
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _doubles (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _doubles i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(setf (get uav_msgs::MissionParams :md5sum-) "bc0a18721b20b19e0ac5fce7cb2d9e52")
(setf (get uav_msgs::MissionParams :datatype-) "uav_msgs/MissionParams")
(setf (get uav_msgs::MissionParams :definition-)
      "bool[] bools
int16[] ints
string[] strings
float64[] doubles

")



(provide :uav_msgs/MissionParams "bc0a18721b20b19e0ac5fce7cb2d9e52")


