// Generated by gencpp from file uav_msgs/DetectQR.msg
// DO NOT EDIT!


#ifndef UAV_MSGS_MESSAGE_DETECTQR_H
#define UAV_MSGS_MESSAGE_DETECTQR_H

#include <ros/service_traits.h>


#include <uav_msgs/DetectQRRequest.h>
#include <uav_msgs/DetectQRResponse.h>


namespace uav_msgs
{

struct DetectQR
{

typedef DetectQRRequest Request;
typedef DetectQRResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct DetectQR
} // namespace uav_msgs


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::uav_msgs::DetectQR > {
  static const char* value()
  {
    return "35ea94070a2b21ef0ad43c5c3a092789";
  }

  static const char* value(const ::uav_msgs::DetectQR&) { return value(); }
};

template<>
struct DataType< ::uav_msgs::DetectQR > {
  static const char* value()
  {
    return "uav_msgs/DetectQR";
  }

  static const char* value(const ::uav_msgs::DetectQR&) { return value(); }
};


// service_traits::MD5Sum< ::uav_msgs::DetectQRRequest> should match
// service_traits::MD5Sum< ::uav_msgs::DetectQR >
template<>
struct MD5Sum< ::uav_msgs::DetectQRRequest>
{
  static const char* value()
  {
    return MD5Sum< ::uav_msgs::DetectQR >::value();
  }
  static const char* value(const ::uav_msgs::DetectQRRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::uav_msgs::DetectQRRequest> should match
// service_traits::DataType< ::uav_msgs::DetectQR >
template<>
struct DataType< ::uav_msgs::DetectQRRequest>
{
  static const char* value()
  {
    return DataType< ::uav_msgs::DetectQR >::value();
  }
  static const char* value(const ::uav_msgs::DetectQRRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::uav_msgs::DetectQRResponse> should match
// service_traits::MD5Sum< ::uav_msgs::DetectQR >
template<>
struct MD5Sum< ::uav_msgs::DetectQRResponse>
{
  static const char* value()
  {
    return MD5Sum< ::uav_msgs::DetectQR >::value();
  }
  static const char* value(const ::uav_msgs::DetectQRResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::uav_msgs::DetectQRResponse> should match
// service_traits::DataType< ::uav_msgs::DetectQR >
template<>
struct DataType< ::uav_msgs::DetectQRResponse>
{
  static const char* value()
  {
    return DataType< ::uav_msgs::DetectQR >::value();
  }
  static const char* value(const ::uav_msgs::DetectQRResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // UAV_MSGS_MESSAGE_DETECTQR_H