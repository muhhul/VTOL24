// Generated by gencpp from file uav_msgs/PilotOverrideResponse.msg
// DO NOT EDIT!


#ifndef UAV_MSGS_MESSAGE_PILOTOVERRIDERESPONSE_H
#define UAV_MSGS_MESSAGE_PILOTOVERRIDERESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace uav_msgs
{
template <class ContainerAllocator>
struct PilotOverrideResponse_
{
  typedef PilotOverrideResponse_<ContainerAllocator> Type;

  PilotOverrideResponse_()
    : result(0)  {
    }
  PilotOverrideResponse_(const ContainerAllocator& _alloc)
    : result(0)  {
  (void)_alloc;
    }



   typedef uint8_t _result_type;
  _result_type result;





  typedef boost::shared_ptr< ::uav_msgs::PilotOverrideResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::uav_msgs::PilotOverrideResponse_<ContainerAllocator> const> ConstPtr;

}; // struct PilotOverrideResponse_

typedef ::uav_msgs::PilotOverrideResponse_<std::allocator<void> > PilotOverrideResponse;

typedef boost::shared_ptr< ::uav_msgs::PilotOverrideResponse > PilotOverrideResponsePtr;
typedef boost::shared_ptr< ::uav_msgs::PilotOverrideResponse const> PilotOverrideResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::uav_msgs::PilotOverrideResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::uav_msgs::PilotOverrideResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::uav_msgs::PilotOverrideResponse_<ContainerAllocator1> & lhs, const ::uav_msgs::PilotOverrideResponse_<ContainerAllocator2> & rhs)
{
  return lhs.result == rhs.result;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::uav_msgs::PilotOverrideResponse_<ContainerAllocator1> & lhs, const ::uav_msgs::PilotOverrideResponse_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace uav_msgs

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::uav_msgs::PilotOverrideResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::uav_msgs::PilotOverrideResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::uav_msgs::PilotOverrideResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::uav_msgs::PilotOverrideResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::uav_msgs::PilotOverrideResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::uav_msgs::PilotOverrideResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::uav_msgs::PilotOverrideResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "25458147911545c320c4c0a299eff763";
  }

  static const char* value(const ::uav_msgs::PilotOverrideResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x25458147911545c3ULL;
  static const uint64_t static_value2 = 0x20c4c0a299eff763ULL;
};

template<class ContainerAllocator>
struct DataType< ::uav_msgs::PilotOverrideResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "uav_msgs/PilotOverrideResponse";
  }

  static const char* value(const ::uav_msgs::PilotOverrideResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::uav_msgs::PilotOverrideResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "uint8 result\n"
"\n"
;
  }

  static const char* value(const ::uav_msgs::PilotOverrideResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::uav_msgs::PilotOverrideResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.result);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct PilotOverrideResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::uav_msgs::PilotOverrideResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::uav_msgs::PilotOverrideResponse_<ContainerAllocator>& v)
  {
    s << indent << "result: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.result);
  }
};

} // namespace message_operations
} // namespace ros

#endif // UAV_MSGS_MESSAGE_PILOTOVERRIDERESPONSE_H