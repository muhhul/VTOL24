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

class DetectObjectRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.name = null;
    }
    else {
      if (initObj.hasOwnProperty('name')) {
        this.name = initObj.name
      }
      else {
        this.name = '';
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type DetectObjectRequest
    // Serialize message field [name]
    bufferOffset = _serializer.string(obj.name, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type DetectObjectRequest
    let len;
    let data = new DetectObjectRequest(null);
    // Deserialize message field [name]
    data.name = _deserializer.string(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += _getByteLength(object.name);
    return length + 4;
  }

  static datatype() {
    // Returns string type for a service object
    return 'uav_msgs/DetectObjectRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c1f3d28f1b044c871e6eff2e9fc3c667';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string name
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new DetectObjectRequest(null);
    if (msg.name !== undefined) {
      resolved.name = msg.name;
    }
    else {
      resolved.name = ''
    }

    return resolved;
    }
};

class DetectObjectResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.scanELP = null;
      this.scanDZ = null;
      this.scanQRPos = null;
      this.scanDistX = null;
      this.scanGate = null;
    }
    else {
      if (initObj.hasOwnProperty('scanELP')) {
        this.scanELP = initObj.scanELP
      }
      else {
        this.scanELP = false;
      }
      if (initObj.hasOwnProperty('scanDZ')) {
        this.scanDZ = initObj.scanDZ
      }
      else {
        this.scanDZ = false;
      }
      if (initObj.hasOwnProperty('scanQRPos')) {
        this.scanQRPos = initObj.scanQRPos
      }
      else {
        this.scanQRPos = false;
      }
      if (initObj.hasOwnProperty('scanDistX')) {
        this.scanDistX = initObj.scanDistX
      }
      else {
        this.scanDistX = false;
      }
      if (initObj.hasOwnProperty('scanGate')) {
        this.scanGate = initObj.scanGate
      }
      else {
        this.scanGate = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type DetectObjectResponse
    // Serialize message field [scanELP]
    bufferOffset = _serializer.bool(obj.scanELP, buffer, bufferOffset);
    // Serialize message field [scanDZ]
    bufferOffset = _serializer.bool(obj.scanDZ, buffer, bufferOffset);
    // Serialize message field [scanQRPos]
    bufferOffset = _serializer.bool(obj.scanQRPos, buffer, bufferOffset);
    // Serialize message field [scanDistX]
    bufferOffset = _serializer.bool(obj.scanDistX, buffer, bufferOffset);
    // Serialize message field [scanGate]
    bufferOffset = _serializer.bool(obj.scanGate, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type DetectObjectResponse
    let len;
    let data = new DetectObjectResponse(null);
    // Deserialize message field [scanELP]
    data.scanELP = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [scanDZ]
    data.scanDZ = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [scanQRPos]
    data.scanQRPos = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [scanDistX]
    data.scanDistX = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [scanGate]
    data.scanGate = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 5;
  }

  static datatype() {
    // Returns string type for a service object
    return 'uav_msgs/DetectObjectResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'efc51c7c5fc2dd12a6aad86f62636a56';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool scanELP
    bool scanDZ
    bool scanQRPos
    bool scanDistX
    bool scanGate
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new DetectObjectResponse(null);
    if (msg.scanELP !== undefined) {
      resolved.scanELP = msg.scanELP;
    }
    else {
      resolved.scanELP = false
    }

    if (msg.scanDZ !== undefined) {
      resolved.scanDZ = msg.scanDZ;
    }
    else {
      resolved.scanDZ = false
    }

    if (msg.scanQRPos !== undefined) {
      resolved.scanQRPos = msg.scanQRPos;
    }
    else {
      resolved.scanQRPos = false
    }

    if (msg.scanDistX !== undefined) {
      resolved.scanDistX = msg.scanDistX;
    }
    else {
      resolved.scanDistX = false
    }

    if (msg.scanGate !== undefined) {
      resolved.scanGate = msg.scanGate;
    }
    else {
      resolved.scanGate = false
    }

    return resolved;
    }
};

module.exports = {
  Request: DetectObjectRequest,
  Response: DetectObjectResponse,
  md5sum() { return 'a025889287f882ec66648bcea0082302'; },
  datatype() { return 'uav_msgs/DetectObject'; }
};
