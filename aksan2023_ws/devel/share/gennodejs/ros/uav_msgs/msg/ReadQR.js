// Auto-generated. Do not edit!

// (in-package uav_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class ReadQR {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.data = null;
      this.location = null;
    }
    else {
      if (initObj.hasOwnProperty('data')) {
        this.data = initObj.data
      }
      else {
        this.data = '';
      }
      if (initObj.hasOwnProperty('location')) {
        this.location = initObj.location
      }
      else {
        this.location = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ReadQR
    // Serialize message field [data]
    bufferOffset = _serializer.string(obj.data, buffer, bufferOffset);
    // Serialize message field [location]
    // Serialize the length for message field [location]
    bufferOffset = _serializer.uint32(obj.location.length, buffer, bufferOffset);
    obj.location.forEach((val) => {
      bufferOffset = geometry_msgs.msg.Point.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ReadQR
    let len;
    let data = new ReadQR(null);
    // Deserialize message field [data]
    data.data = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [location]
    // Deserialize array length for message field [location]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.location = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.location[i] = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += _getByteLength(object.data);
    length += 24 * object.location.length;
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'uav_msgs/ReadQR';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '0b97356b914a0ea80b810a8e728c804b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string data
    #offset in meters
    geometry_msgs/Point[] location
    
    ================================================================================
    MSG: geometry_msgs/Point
    # This contains the position of a point in free space
    float64 x
    float64 y
    float64 z
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new ReadQR(null);
    if (msg.data !== undefined) {
      resolved.data = msg.data;
    }
    else {
      resolved.data = ''
    }

    if (msg.location !== undefined) {
      resolved.location = new Array(msg.location.length);
      for (let i = 0; i < resolved.location.length; ++i) {
        resolved.location[i] = geometry_msgs.msg.Point.Resolve(msg.location[i]);
      }
    }
    else {
      resolved.location = []
    }

    return resolved;
    }
};

module.exports = ReadQR;
