; Auto-generated. Do not edit!


(cl:in-package uav_msgs-msg)


;//! \htmlinclude DzPosition.msg.html

(cl:defclass <DzPosition> (roslisp-msg-protocol:ros-message)
  ((dist_x
    :reader dist_x
    :initarg :dist_x
    :type cl:float
    :initform 0.0)
   (dist_y
    :reader dist_y
    :initarg :dist_y
    :type cl:float
    :initform 0.0))
)

(cl:defclass DzPosition (<DzPosition>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <DzPosition>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'DzPosition)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name uav_msgs-msg:<DzPosition> is deprecated: use uav_msgs-msg:DzPosition instead.")))

(cl:ensure-generic-function 'dist_x-val :lambda-list '(m))
(cl:defmethod dist_x-val ((m <DzPosition>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav_msgs-msg:dist_x-val is deprecated.  Use uav_msgs-msg:dist_x instead.")
  (dist_x m))

(cl:ensure-generic-function 'dist_y-val :lambda-list '(m))
(cl:defmethod dist_y-val ((m <DzPosition>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav_msgs-msg:dist_y-val is deprecated.  Use uav_msgs-msg:dist_y instead.")
  (dist_y m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <DzPosition>) ostream)
  "Serializes a message object of type '<DzPosition>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'dist_x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'dist_y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <DzPosition>) istream)
  "Deserializes a message object of type '<DzPosition>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'dist_x) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'dist_y) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<DzPosition>)))
  "Returns string type for a message object of type '<DzPosition>"
  "uav_msgs/DzPosition")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DzPosition)))
  "Returns string type for a message object of type 'DzPosition"
  "uav_msgs/DzPosition")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<DzPosition>)))
  "Returns md5sum for a message object of type '<DzPosition>"
  "548475a5e014d2e321e9481e359821fc")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'DzPosition)))
  "Returns md5sum for a message object of type 'DzPosition"
  "548475a5e014d2e321e9481e359821fc")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<DzPosition>)))
  "Returns full string definition for message of type '<DzPosition>"
  (cl:format cl:nil "float64 dist_x~%float64 dist_y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'DzPosition)))
  "Returns full string definition for message of type 'DzPosition"
  (cl:format cl:nil "float64 dist_x~%float64 dist_y~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <DzPosition>))
  (cl:+ 0
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <DzPosition>))
  "Converts a ROS message object to a list"
  (cl:list 'DzPosition
    (cl:cons ':dist_x (dist_x msg))
    (cl:cons ':dist_y (dist_y msg))
))
