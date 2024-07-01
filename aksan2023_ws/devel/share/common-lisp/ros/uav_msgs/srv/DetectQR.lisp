; Auto-generated. Do not edit!


(cl:in-package uav_msgs-srv)


;//! \htmlinclude DetectQR-request.msg.html

(cl:defclass <DetectQR-request> (roslisp-msg-protocol:ros-message)
  ((name
    :reader name
    :initarg :name
    :type cl:string
    :initform ""))
)

(cl:defclass DetectQR-request (<DetectQR-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <DetectQR-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'DetectQR-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name uav_msgs-srv:<DetectQR-request> is deprecated: use uav_msgs-srv:DetectQR-request instead.")))

(cl:ensure-generic-function 'name-val :lambda-list '(m))
(cl:defmethod name-val ((m <DetectQR-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav_msgs-srv:name-val is deprecated.  Use uav_msgs-srv:name instead.")
  (name m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <DetectQR-request>) ostream)
  "Serializes a message object of type '<DetectQR-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'name))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <DetectQR-request>) istream)
  "Deserializes a message object of type '<DetectQR-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<DetectQR-request>)))
  "Returns string type for a service object of type '<DetectQR-request>"
  "uav_msgs/DetectQRRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DetectQR-request)))
  "Returns string type for a service object of type 'DetectQR-request"
  "uav_msgs/DetectQRRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<DetectQR-request>)))
  "Returns md5sum for a message object of type '<DetectQR-request>"
  "35ea94070a2b21ef0ad43c5c3a092789")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'DetectQR-request)))
  "Returns md5sum for a message object of type 'DetectQR-request"
  "35ea94070a2b21ef0ad43c5c3a092789")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<DetectQR-request>)))
  "Returns full string definition for message of type '<DetectQR-request>"
  (cl:format cl:nil "string name~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'DetectQR-request)))
  "Returns full string definition for message of type 'DetectQR-request"
  (cl:format cl:nil "string name~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <DetectQR-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'name))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <DetectQR-request>))
  "Converts a ROS message object to a list"
  (cl:list 'DetectQR-request
    (cl:cons ':name (name msg))
))
;//! \htmlinclude DetectQR-response.msg.html

(cl:defclass <DetectQR-response> (roslisp-msg-protocol:ros-message)
  ((scanQR
    :reader scanQR
    :initarg :scanQR
    :type cl:boolean
    :initform cl:nil)
   (data
    :reader data
    :initarg :data
    :type cl:string
    :initform ""))
)

(cl:defclass DetectQR-response (<DetectQR-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <DetectQR-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'DetectQR-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name uav_msgs-srv:<DetectQR-response> is deprecated: use uav_msgs-srv:DetectQR-response instead.")))

(cl:ensure-generic-function 'scanQR-val :lambda-list '(m))
(cl:defmethod scanQR-val ((m <DetectQR-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav_msgs-srv:scanQR-val is deprecated.  Use uav_msgs-srv:scanQR instead.")
  (scanQR m))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <DetectQR-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav_msgs-srv:data-val is deprecated.  Use uav_msgs-srv:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <DetectQR-response>) ostream)
  "Serializes a message object of type '<DetectQR-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'scanQR) 1 0)) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'data))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'data))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <DetectQR-response>) istream)
  "Deserializes a message object of type '<DetectQR-response>"
    (cl:setf (cl:slot-value msg 'scanQR) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'data) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'data) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<DetectQR-response>)))
  "Returns string type for a service object of type '<DetectQR-response>"
  "uav_msgs/DetectQRResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DetectQR-response)))
  "Returns string type for a service object of type 'DetectQR-response"
  "uav_msgs/DetectQRResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<DetectQR-response>)))
  "Returns md5sum for a message object of type '<DetectQR-response>"
  "35ea94070a2b21ef0ad43c5c3a092789")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'DetectQR-response)))
  "Returns md5sum for a message object of type 'DetectQR-response"
  "35ea94070a2b21ef0ad43c5c3a092789")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<DetectQR-response>)))
  "Returns full string definition for message of type '<DetectQR-response>"
  (cl:format cl:nil "bool scanQR~%string data~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'DetectQR-response)))
  "Returns full string definition for message of type 'DetectQR-response"
  (cl:format cl:nil "bool scanQR~%string data~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <DetectQR-response>))
  (cl:+ 0
     1
     4 (cl:length (cl:slot-value msg 'data))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <DetectQR-response>))
  "Converts a ROS message object to a list"
  (cl:list 'DetectQR-response
    (cl:cons ':scanQR (scanQR msg))
    (cl:cons ':data (data msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'DetectQR)))
  'DetectQR-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'DetectQR)))
  'DetectQR-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DetectQR)))
  "Returns string type for a service object of type '<DetectQR>"
  "uav_msgs/DetectQR")