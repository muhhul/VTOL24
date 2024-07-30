; Auto-generated. Do not edit!


(cl:in-package uav_msgs-srv)


;//! \htmlinclude DetectObject-request.msg.html

(cl:defclass <DetectObject-request> (roslisp-msg-protocol:ros-message)
  ((name
    :reader name
    :initarg :name
    :type cl:string
    :initform ""))
)

(cl:defclass DetectObject-request (<DetectObject-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <DetectObject-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'DetectObject-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name uav_msgs-srv:<DetectObject-request> is deprecated: use uav_msgs-srv:DetectObject-request instead.")))

(cl:ensure-generic-function 'name-val :lambda-list '(m))
(cl:defmethod name-val ((m <DetectObject-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav_msgs-srv:name-val is deprecated.  Use uav_msgs-srv:name instead.")
  (name m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <DetectObject-request>) ostream)
  "Serializes a message object of type '<DetectObject-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'name))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <DetectObject-request>) istream)
  "Deserializes a message object of type '<DetectObject-request>"
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<DetectObject-request>)))
  "Returns string type for a service object of type '<DetectObject-request>"
  "uav_msgs/DetectObjectRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DetectObject-request)))
  "Returns string type for a service object of type 'DetectObject-request"
  "uav_msgs/DetectObjectRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<DetectObject-request>)))
  "Returns md5sum for a message object of type '<DetectObject-request>"
  "a025889287f882ec66648bcea0082302")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'DetectObject-request)))
  "Returns md5sum for a message object of type 'DetectObject-request"
  "a025889287f882ec66648bcea0082302")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<DetectObject-request>)))
  "Returns full string definition for message of type '<DetectObject-request>"
  (cl:format cl:nil "string name~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'DetectObject-request)))
  "Returns full string definition for message of type 'DetectObject-request"
  (cl:format cl:nil "string name~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <DetectObject-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'name))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <DetectObject-request>))
  "Converts a ROS message object to a list"
  (cl:list 'DetectObject-request
    (cl:cons ':name (name msg))
))
;//! \htmlinclude DetectObject-response.msg.html

(cl:defclass <DetectObject-response> (roslisp-msg-protocol:ros-message)
  ((scanELP
    :reader scanELP
    :initarg :scanELP
    :type cl:boolean
    :initform cl:nil)
   (scanDZ
    :reader scanDZ
    :initarg :scanDZ
    :type cl:boolean
    :initform cl:nil)
   (scanQRPos
    :reader scanQRPos
    :initarg :scanQRPos
    :type cl:boolean
    :initform cl:nil)
   (scanDistX
    :reader scanDistX
    :initarg :scanDistX
    :type cl:boolean
    :initform cl:nil)
   (scanGate
    :reader scanGate
    :initarg :scanGate
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass DetectObject-response (<DetectObject-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <DetectObject-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'DetectObject-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name uav_msgs-srv:<DetectObject-response> is deprecated: use uav_msgs-srv:DetectObject-response instead.")))

(cl:ensure-generic-function 'scanELP-val :lambda-list '(m))
(cl:defmethod scanELP-val ((m <DetectObject-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav_msgs-srv:scanELP-val is deprecated.  Use uav_msgs-srv:scanELP instead.")
  (scanELP m))

(cl:ensure-generic-function 'scanDZ-val :lambda-list '(m))
(cl:defmethod scanDZ-val ((m <DetectObject-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav_msgs-srv:scanDZ-val is deprecated.  Use uav_msgs-srv:scanDZ instead.")
  (scanDZ m))

(cl:ensure-generic-function 'scanQRPos-val :lambda-list '(m))
(cl:defmethod scanQRPos-val ((m <DetectObject-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav_msgs-srv:scanQRPos-val is deprecated.  Use uav_msgs-srv:scanQRPos instead.")
  (scanQRPos m))

(cl:ensure-generic-function 'scanDistX-val :lambda-list '(m))
(cl:defmethod scanDistX-val ((m <DetectObject-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav_msgs-srv:scanDistX-val is deprecated.  Use uav_msgs-srv:scanDistX instead.")
  (scanDistX m))

(cl:ensure-generic-function 'scanGate-val :lambda-list '(m))
(cl:defmethod scanGate-val ((m <DetectObject-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader uav_msgs-srv:scanGate-val is deprecated.  Use uav_msgs-srv:scanGate instead.")
  (scanGate m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <DetectObject-response>) ostream)
  "Serializes a message object of type '<DetectObject-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'scanELP) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'scanDZ) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'scanQRPos) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'scanDistX) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'scanGate) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <DetectObject-response>) istream)
  "Deserializes a message object of type '<DetectObject-response>"
    (cl:setf (cl:slot-value msg 'scanELP) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'scanDZ) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'scanQRPos) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'scanDistX) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'scanGate) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<DetectObject-response>)))
  "Returns string type for a service object of type '<DetectObject-response>"
  "uav_msgs/DetectObjectResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DetectObject-response)))
  "Returns string type for a service object of type 'DetectObject-response"
  "uav_msgs/DetectObjectResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<DetectObject-response>)))
  "Returns md5sum for a message object of type '<DetectObject-response>"
  "a025889287f882ec66648bcea0082302")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'DetectObject-response)))
  "Returns md5sum for a message object of type 'DetectObject-response"
  "a025889287f882ec66648bcea0082302")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<DetectObject-response>)))
  "Returns full string definition for message of type '<DetectObject-response>"
  (cl:format cl:nil "bool scanELP~%bool scanDZ~%bool scanQRPos~%bool scanDistX~%bool scanGate~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'DetectObject-response)))
  "Returns full string definition for message of type 'DetectObject-response"
  (cl:format cl:nil "bool scanELP~%bool scanDZ~%bool scanQRPos~%bool scanDistX~%bool scanGate~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <DetectObject-response>))
  (cl:+ 0
     1
     1
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <DetectObject-response>))
  "Converts a ROS message object to a list"
  (cl:list 'DetectObject-response
    (cl:cons ':scanELP (scanELP msg))
    (cl:cons ':scanDZ (scanDZ msg))
    (cl:cons ':scanQRPos (scanQRPos msg))
    (cl:cons ':scanDistX (scanDistX msg))
    (cl:cons ':scanGate (scanGate msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'DetectObject)))
  'DetectObject-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'DetectObject)))
  'DetectObject-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DetectObject)))
  "Returns string type for a service object of type '<DetectObject>"
  "uav_msgs/DetectObject")