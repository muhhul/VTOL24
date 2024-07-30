; Auto-generated. Do not edit!


(cl:in-package uav_msgs-msg)


;//! \htmlinclude ReadQR.msg.html

(cl:defclass <ReadQR> (roslisp-msg-protocol:ros-message)
  ((data
    :reader data
    :initarg :data
    :type cl:string
    :initform "")
   (location
    :reader location
    :initarg :location
    :type (cl:vector geometry_msgs-msg:Point)
   :initform (cl:make-array 0 :element-type 'geometry_msgs-msg:Point :initial-element (cl:make-instance 'geometry_msgs-msg:Point))))
)

(cl:defclass ReadQR (<ReadQR>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ReadQR>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ReadQR)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name uav_msgs-msg:<ReadQR> is deprecated: use uav_msgs-msg:ReadQR instead.")))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <ReadQR>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav_msgs-msg:data-val is deprecated.  Use uav_msgs-msg:data instead.")
  (data m))

(cl:ensure-generic-function 'location-val :lambda-list '(m))
(cl:defmethod location-val ((m <ReadQR>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav_msgs-msg:location-val is deprecated.  Use uav_msgs-msg:location instead.")
  (location m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ReadQR>) ostream)
  "Serializes a message object of type '<ReadQR>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'data))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'data))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'location))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'location))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ReadQR>) istream)
  "Deserializes a message object of type '<ReadQR>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'data) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'data) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'location) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'location)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:Point))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ReadQR>)))
  "Returns string type for a message object of type '<ReadQR>"
  "uav_msgs/ReadQR")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ReadQR)))
  "Returns string type for a message object of type 'ReadQR"
  "uav_msgs/ReadQR")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ReadQR>)))
  "Returns md5sum for a message object of type '<ReadQR>"
  "0b97356b914a0ea80b810a8e728c804b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ReadQR)))
  "Returns md5sum for a message object of type 'ReadQR"
  "0b97356b914a0ea80b810a8e728c804b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ReadQR>)))
  "Returns full string definition for message of type '<ReadQR>"
  (cl:format cl:nil "string data~%#offset in meters~%geometry_msgs/Point[] location~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ReadQR)))
  "Returns full string definition for message of type 'ReadQR"
  (cl:format cl:nil "string data~%#offset in meters~%geometry_msgs/Point[] location~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ReadQR>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'data))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'location) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ReadQR>))
  "Converts a ROS message object to a list"
  (cl:list 'ReadQR
    (cl:cons ':data (data msg))
    (cl:cons ':location (location msg))
))
