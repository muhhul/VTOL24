// Auto-generated. Do not edit!

// (in-package uav_msgs.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class PilotOverrideRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.what = null;
    }
    else {
      if (initObj.hasOwnProperty('what')) {
        this.what = initObj.what
      }
      else {
        this.what = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type PilotOverrideRequest
    // Serialize message field [what]
    bufferOffset = _serializer.string(obj.what, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type PilotOverrideRequest
    let len;
    let data = new PilotOverrideRequest(null);
    // Deserialize message field [what]
    data.what = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += _getByteLength(object.what);
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'uav_msgs/PilotOverrideRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'e93b05a1e536de6994950b45e76bd1de';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # Available: LAND_SERV, RTL
    string what
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new PilotOverrideRequest(null);
    if (msg.what !== undefined) {
      resolved.what = msg.what;
    }
    else {
      resolved.what = ''
    }

    return resolved;
    }
};

class PilotOverrideResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.result = null;
    }
    else {
      if (initObj.hasOwnProperty('result')) {
        this.result = initObj.result
      }
      else {
        this.result = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type PilotOverrideResponse
    // Serialize message field [result]
    bufferOffset = _serializer.uint8(obj.result, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type PilotOverrideResponse
    let len;
    let data = new PilotOverrideResponse(null);
    // Deserialize message field [result]
    data.result = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'uav_msgs/PilotOverrideResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '25458147911545c320c4c0a299eff763';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8 result
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new PilotOverrideResponse(null);
    if (msg.result !== undefined) {
      resolved.result = msg.result;
    }
    else {
      resolved.result = 0
    }

    return resolved;
    }
};

module.exports = {
  Request: PilotOverrideRequest,
  Response: PilotOverrideResponse,
  md5sum() { return '019550d9794152b525bf949a5e4ab378'; },
  datatype() { return 'uav_msgs/PilotOverride'; }
};
