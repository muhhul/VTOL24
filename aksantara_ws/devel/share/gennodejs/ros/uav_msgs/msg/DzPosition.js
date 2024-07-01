// Auto-generated. Do not edit!

// (in-package uav_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class DzPosition {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.dist_x = null;
      this.dist_y = null;
    }
    else {
      if (initObj.hasOwnProperty('dist_x')) {
        this.dist_x = initObj.dist_x
      }
      else {
        this.dist_x = 0.0;
      }
      if (initObj.hasOwnProperty('dist_y')) {
        this.dist_y = initObj.dist_y
      }
      else {
        this.dist_y = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type DzPosition
    // Serialize message field [dist_x]
    bufferOffset = _serializer.float64(obj.dist_x, buffer, bufferOffset);
    // Serialize message field [dist_y]
    bufferOffset = _serializer.float64(obj.dist_y, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type DzPosition
    let len;
    let data = new DzPosition(null);
    // Deserialize message field [dist_x]
    data.dist_x = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [dist_y]
    data.dist_y = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 16;
  }

  static datatype() {
    // Returns string type for a message object
    return 'uav_msgs/DzPosition';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '548475a5e014d2e321e9481e359821fc';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 dist_x
    float64 dist_y
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new DzPosition(null);
    if (msg.dist_x !== undefined) {
      resolved.dist_x = msg.dist_x;
    }
    else {
      resolved.dist_x = 0.0
    }

    if (msg.dist_y !== undefined) {
      resolved.dist_y = msg.dist_y;
    }
    else {
      resolved.dist_y = 0.0
    }

    return resolved;
    }
};

module.exports = DzPosition;
