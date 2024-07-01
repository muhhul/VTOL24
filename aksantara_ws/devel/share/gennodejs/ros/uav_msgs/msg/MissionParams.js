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

class MissionParams {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.bools = null;
      this.ints = null;
      this.strings = null;
      this.doubles = null;
    }
    else {
      if (initObj.hasOwnProperty('bools')) {
        this.bools = initObj.bools
      }
      else {
        this.bools = [];
      }
      if (initObj.hasOwnProperty('ints')) {
        this.ints = initObj.ints
      }
      else {
        this.ints = [];
      }
      if (initObj.hasOwnProperty('strings')) {
        this.strings = initObj.strings
      }
      else {
        this.strings = [];
      }
      if (initObj.hasOwnProperty('doubles')) {
        this.doubles = initObj.doubles
      }
      else {
        this.doubles = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type MissionParams
    // Serialize message field [bools]
    bufferOffset = _arraySerializer.bool(obj.bools, buffer, bufferOffset, null);
    // Serialize message field [ints]
    bufferOffset = _arraySerializer.int16(obj.ints, buffer, bufferOffset, null);
    // Serialize message field [strings]
    bufferOffset = _arraySerializer.string(obj.strings, buffer, bufferOffset, null);
    // Serialize message field [doubles]
    bufferOffset = _arraySerializer.float64(obj.doubles, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type MissionParams
    let len;
    let data = new MissionParams(null);
    // Deserialize message field [bools]
    data.bools = _arrayDeserializer.bool(buffer, bufferOffset, null)
    // Deserialize message field [ints]
    data.ints = _arrayDeserializer.int16(buffer, bufferOffset, null)
    // Deserialize message field [strings]
    data.strings = _arrayDeserializer.string(buffer, bufferOffset, null)
    // Deserialize message field [doubles]
    data.doubles = _arrayDeserializer.float64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.bools.length;
    length += 2 * object.ints.length;
    object.strings.forEach((val) => {
      length += 4 + _getByteLength(val);
    });
    length += 8 * object.doubles.length;
    return length + 16;
  }

  static datatype() {
    // Returns string type for a message object
    return 'uav_msgs/MissionParams';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'bc0a18721b20b19e0ac5fce7cb2d9e52';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool[] bools
    int16[] ints
    string[] strings
    float64[] doubles
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new MissionParams(null);
    if (msg.bools !== undefined) {
      resolved.bools = msg.bools;
    }
    else {
      resolved.bools = []
    }

    if (msg.ints !== undefined) {
      resolved.ints = msg.ints;
    }
    else {
      resolved.ints = []
    }

    if (msg.strings !== undefined) {
      resolved.strings = msg.strings;
    }
    else {
      resolved.strings = []
    }

    if (msg.doubles !== undefined) {
      resolved.doubles = msg.doubles;
    }
    else {
      resolved.doubles = []
    }

    return resolved;
    }
};

module.exports = MissionParams;
