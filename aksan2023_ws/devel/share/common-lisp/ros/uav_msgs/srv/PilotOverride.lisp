; Auto-generated. Do not edit!


(cl:in-package uav_msgs-srv)


;//! \htmlinclude PilotOverride-request.msg.html

(cl:defclass <PilotOverride-request> (roslisp-msg-protocol:ros-message)
  ((what
    :reader what
    :initarg :what
    :type cl:string
    :initform ""))
)

(cl:defclass PilotOverride-request (<PilotOverride-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PilotOverride-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PilotOverride-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name uav_msgs-srv:<PilotOverride-request> is deprecated: use uav_msgs-srv:PilotOverride-request instead.")))

(cl:ensure-generic-function 'what-val :lambda-list '(m))
(cl:defmethod what-val ((m <PilotOverride-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav_msgs-srv:what-val is deprecated.  Use uav_msgs-srv:what instead.")
  (what m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PilotOverride-request>) ostream)
  "Serializes a message object of type '<PilotOverride-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'what))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'what))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PilotOverride-request>) istream)
  "Deserializes a message object of type '<PilotOverride-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'what) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'what) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PilotOverride-request>)))
  "Returns string type for a service object of type '<PilotOverride-request>"
  "uav_msgs/PilotOverrideRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PilotOverride-request)))
  "Returns string type for a service object of type 'PilotOverride-request"
  "uav_msgs/PilotOverrideRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PilotOverride-request>)))
  "Returns md5sum for a message object of type '<PilotOverride-request>"
  "019550d9794152b525bf949a5e4ab378")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PilotOverride-request)))
  "Returns md5sum for a message object of type 'PilotOverride-request"
  "019550d9794152b525bf949a5e4ab378")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PilotOverride-request>)))
  "Returns full string definition for message of type '<PilotOverride-request>"
  (cl:format cl:nil "# Available: LAND_SERV, RTL~%string what~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PilotOverride-request)))
  "Returns full string definition for message of type 'PilotOverride-request"
  (cl:format cl:nil "# Available: LAND_SERV, RTL~%string what~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PilotOverride-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'what))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PilotOverride-request>))
  "Converts a ROS message object to a list"
  (cl:list 'PilotOverride-request
    (cl:cons ':what (what msg))
))
;//! \htmlinclude PilotOverride-response.msg.html

(cl:defclass <PilotOverride-response> (roslisp-msg-protocol:ros-message)
  ((result
    :reader result
    :initarg :result
    :type cl:fixnum
    :initform 0))
)

(cl:defclass PilotOverride-response (<PilotOverride-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PilotOverride-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PilotOverride-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name uav_msgs-srv:<PilotOverride-response> is deprecated: use uav_msgs-srv:PilotOverride-response instead.")))

(cl:ensure-generic-function 'result-val :lambda-list '(m))
(cl:defmethod result-val ((m <PilotOverride-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav_msgs-srv:result-val is deprecated.  Use uav_msgs-srv:result instead.")
  (result m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PilotOverride-response>) ostream)
  "Serializes a message object of type '<PilotOverride-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'result)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PilotOverride-response>) istream)
  "Deserializes a message object of type '<PilotOverride-response>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'result)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PilotOverride-response>)))
  "Returns string type for a service object of type '<PilotOverride-response>"
  "uav_msgs/PilotOverrideResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PilotOverride-response)))
  "Returns string type for a service object of type 'PilotOverride-response"
  "uav_msgs/PilotOverrideResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PilotOverride-response>)))
  "Returns md5sum for a message object of type '<PilotOverride-response>"
  "019550d9794152b525bf949a5e4ab378")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PilotOverride-response)))
  "Returns md5sum for a message object of type 'PilotOverride-response"
  "019550d9794152b525bf949a5e4ab378")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PilotOverride-response>)))
  "Returns full string definition for message of type '<PilotOverride-response>"
  (cl:format cl:nil "uint8 result~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PilotOverride-response)))
  "Returns full string definition for message of type 'PilotOverride-response"
  (cl:format cl:nil "uint8 result~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PilotOverride-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PilotOverride-response>))
  "Converts a ROS message object to a list"
  (cl:list 'PilotOverride-response
    (cl:cons ':result (result msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'PilotOverride)))
  'PilotOverride-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'PilotOverride)))
  'PilotOverride-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PilotOverride)))
  "Returns string type for a service object of type '<PilotOverride>"
  "uav_msgs/PilotOverride")