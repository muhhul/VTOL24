; Auto-generated. Do not edit!


(cl:in-package uav_msgs-srv)


;//! \htmlinclude SetCurrent-request.msg.html

(cl:defclass <SetCurrent-request> (roslisp-msg-protocol:ros-message)
  ((data
    :reader data
    :initarg :data
    :type cl:integer
    :initform 0))
)

(cl:defclass SetCurrent-request (<SetCurrent-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetCurrent-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetCurrent-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name uav_msgs-srv:<SetCurrent-request> is deprecated: use uav_msgs-srv:SetCurrent-request instead.")))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <SetCurrent-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav_msgs-srv:data-val is deprecated.  Use uav_msgs-srv:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetCurrent-request>) ostream)
  "Serializes a message object of type '<SetCurrent-request>"
  (cl:let* ((signed (cl:slot-value msg 'data)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetCurrent-request>) istream)
  "Deserializes a message object of type '<SetCurrent-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'data) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetCurrent-request>)))
  "Returns string type for a service object of type '<SetCurrent-request>"
  "uav_msgs/SetCurrentRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetCurrent-request)))
  "Returns string type for a service object of type 'SetCurrent-request"
  "uav_msgs/SetCurrentRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetCurrent-request>)))
  "Returns md5sum for a message object of type '<SetCurrent-request>"
  "65058a332cdf9eddf11f34077a0b92a4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetCurrent-request)))
  "Returns md5sum for a message object of type 'SetCurrent-request"
  "65058a332cdf9eddf11f34077a0b92a4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetCurrent-request>)))
  "Returns full string definition for message of type '<SetCurrent-request>"
  (cl:format cl:nil "int32 data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetCurrent-request)))
  "Returns full string definition for message of type 'SetCurrent-request"
  (cl:format cl:nil "int32 data~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetCurrent-request>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetCurrent-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SetCurrent-request
    (cl:cons ':data (data msg))
))
;//! \htmlinclude SetCurrent-response.msg.html

(cl:defclass <SetCurrent-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SetCurrent-response (<SetCurrent-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SetCurrent-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SetCurrent-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name uav_msgs-srv:<SetCurrent-response> is deprecated: use uav_msgs-srv:SetCurrent-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SetCurrent-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav_msgs-srv:success-val is deprecated.  Use uav_msgs-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SetCurrent-response>) ostream)
  "Serializes a message object of type '<SetCurrent-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SetCurrent-response>) istream)
  "Deserializes a message object of type '<SetCurrent-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SetCurrent-response>)))
  "Returns string type for a service object of type '<SetCurrent-response>"
  "uav_msgs/SetCurrentResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetCurrent-response)))
  "Returns string type for a service object of type 'SetCurrent-response"
  "uav_msgs/SetCurrentResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SetCurrent-response>)))
  "Returns md5sum for a message object of type '<SetCurrent-response>"
  "65058a332cdf9eddf11f34077a0b92a4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SetCurrent-response)))
  "Returns md5sum for a message object of type 'SetCurrent-response"
  "65058a332cdf9eddf11f34077a0b92a4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SetCurrent-response>)))
  "Returns full string definition for message of type '<SetCurrent-response>"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SetCurrent-response)))
  "Returns full string definition for message of type 'SetCurrent-response"
  (cl:format cl:nil "bool success~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SetCurrent-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SetCurrent-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SetCurrent-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SetCurrent)))
  'SetCurrent-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SetCurrent)))
  'SetCurrent-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SetCurrent)))
  "Returns string type for a service object of type '<SetCurrent>"
  "uav_msgs/SetCurrent")