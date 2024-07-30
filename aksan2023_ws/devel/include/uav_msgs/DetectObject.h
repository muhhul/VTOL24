// Generated by gencpp from file uav_msgs/DetectObject.msg
// DO NOT EDIT!


#ifndef UAV_MSGS_MESSAGE_DETECTOBJECT_H
#define UAV_MSGS_MESSAGE_DETECTOBJECT_H

#include <ros/service_traits.h>


#include <uav_msgs/DetectObjectRequest.h>
#include <uav_msgs/DetectObjectResponse.h>


namespace uav_msgs
{

struct DetectObject
{

typedef DetectObjectRequest Request;
typedef DetectObjectResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct DetectObject
} // namespace uav_msgs


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::uav_msgs::DetectObject > {
  static const char* value()
  {
    return "a025889287f882ec66648bcea0082302";
  }

  static const char* value(const ::uav_msgs::DetectObject&) { return value(); }
};

template<>
struct DataType< ::uav_msgs::DetectObject > {
  static const char* value()
  {
    return "uav_msgs/DetectObject";
  }

  static const char* value(const ::uav_msgs::DetectObject&) { return value(); }
};


// service_traits::MD5Sum< ::uav_msgs::DetectObjectRequest> should match
// service_traits::MD5Sum< ::uav_msgs::DetectObject >
template<>
struct MD5Sum< ::uav_msgs::DetectObjectRequest>
{
  static const char* value()
  {
    return MD5Sum< ::uav_msgs::DetectObject >::value();
  }
  static const char* value(const ::uav_msgs::DetectObjectRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::uav_msgs::DetectObjectRequest> should match
// service_traits::DataType< ::uav_msgs::DetectObject >
template<>
struct DataType< ::uav_msgs::DetectObjectRequest>
{
  static const char* value()
  {
    return DataType< ::uav_msgs::DetectObject >::value();
  }
  static const char* value(const ::uav_msgs::DetectObjectRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::uav_msgs::DetectObjectResponse> should match
// service_traits::MD5Sum< ::uav_msgs::DetectObject >
template<>
struct MD5Sum< ::uav_msgs::DetectObjectResponse>
{
  static const char* value()
  {
    return MD5Sum< ::uav_msgs::DetectObject >::value();
  }
  static const char* value(const ::uav_msgs::DetectObjectResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::uav_msgs::DetectObjectResponse> should match
// service_traits::DataType< ::uav_msgs::DetectObject >
template<>
struct DataType< ::uav_msgs::DetectObjectResponse>
{
  static const char* value()
  {
    return DataType< ::uav_msgs::DetectObject >::value();
  }
  static const char* value(const ::uav_msgs::DetectObjectResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // UAV_MSGS_MESSAGE_DETECTOBJECT_H
