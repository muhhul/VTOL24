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

class PrecLoit {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.size_x = null;
      this.size_y = null;
      this.angle_x = null;
      this.angle_y = null;
      this.distance = null;
    }
    else {
      if (initObj.hasOwnProperty('size_x')) {
        this.size_x = initObj.size_x
      }
      else {
        this.size_x = 0.0;
      }
      if (initObj.hasOwnProperty('size_y')) {
        this.size_y = initObj.size_y
      }
      else {
        this.size_y = 0.0;
      }
      if (initObj.hasOwnProperty('angle_x')) {
        this.angle_x = initObj.angle_x
      }
      else {
        this.angle_x = 0.0;
      }
      if (initObj.hasOwnProperty('angle_y')) {
        this.angle_y = initObj.angle_y
      }
      else {
        this.angle_y = 0.0;
      }
      if (initObj.hasOwnProperty('distance')) {
        this.distance = initObj.distance
      }
      else {
        this.distance = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type PrecLoit
    // Serialize message field [size_x]
    bufferOffset = _serializer.float64(obj.size_x, buffer, bufferOffset);
    // Serialize message field [size_y]
    bufferOffset = _serializer.float64(obj.size_y, buffer, bufferOffset);
    // Serialize message field [angle_x]
    bufferOffset = _serializer.float64(obj.angle_x, buffer, bufferOffset);
    // Serialize message field [angle_y]
    bufferOffset = _serializer.float64(obj.angle_y, buffer, bufferOffset);
    // Serialize message field [distance]
    bufferOffset = _serializer.float64(obj.distance, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type PrecLoit
    let len;
    let data = new PrecLoit(null);
    // Deserialize message field [size_x]
    data.size_x = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [size_y]
    data.size_y = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [angle_x]
    data.angle_x = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [angle_y]
    data.angle_y = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [distance]
    data.distance = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 40;
  }

  static datatype() {
    // Returns string type for a message object
    return 'uav_msgs/PrecLoit';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'af195082e2bf6647fe0e1655a101af72';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 size_x
    float64 size_y
    float64 angle_x
    float64 angle_y
    float64 distance
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new PrecLoit(null);
    if (msg.size_x !== undefined) {
      resolved.size_x = msg.size_x;
    }
    else {
      resolved.size_x = 0.0
    }

    if (msg.size_y !== undefined) {
      resolved.size_y = msg.size_y;
    }
    else {
      resolved.size_y = 0.0
    }

    if (msg.angle_x !== undefined) {
      resolved.angle_x = msg.angle_x;
    }
    else {
      resolved.angle_x = 0.0
    }

    if (msg.angle_y !== undefined) {
      resolved.angle_y = msg.angle_y;
    }
    else {
      resolved.angle_y = 0.0
    }

    if (msg.distance !== undefined) {
      resolved.distance = msg.distance;
    }
    else {
      resolved.distance = 0.0
    }

    return resolved;
    }
};

module.exports = PrecLoit;
