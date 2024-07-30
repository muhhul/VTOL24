// Generated by gencpp from file uav_msgs/PilotOverrideRequest.msg
// DO NOT EDIT!


#ifndef UAV_MSGS_MESSAGE_PILOTOVERRIDEREQUEST_H
#define UAV_MSGS_MESSAGE_PILOTOVERRIDEREQUEST_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace uav_msgs
{
template <class ContainerAllocator>
struct PilotOverrideRequest_
{
  typedef PilotOverrideRequest_<ContainerAllocator> Type;

  PilotOverrideRequest_()
    : what()  {
    }
  PilotOverrideRequest_(const ContainerAllocator& _alloc)
    : what(_alloc)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _what_type;
  _what_type what;





  typedef boost::shared_ptr< ::uav_msgs::PilotOverrideRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::uav_msgs::PilotOverrideRequest_<ContainerAllocator> const> ConstPtr;

}; // struct PilotOverrideRequest_

typedef ::uav_msgs::PilotOverrideRequest_<std::allocator<void> > PilotOverrideRequest;

typedef boost::shared_ptr< ::uav_msgs::PilotOverrideRequest > PilotOverrideRequestPtr;
typedef boost::shared_ptr< ::uav_msgs::PilotOverrideRequest const> PilotOverrideRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::uav_msgs::PilotOverrideRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::uav_msgs::PilotOverrideRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::uav_msgs::PilotOverrideRequest_<ContainerAllocator1> & lhs, const ::uav_msgs::PilotOverrideRequest_<ContainerAllocator2> & rhs)
{
  return lhs.what == rhs.what;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::uav_msgs::PilotOverrideRequest_<ContainerAllocator1> & lhs, const ::uav_msgs::PilotOverrideRequest_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace uav_msgs

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::uav_msgs::PilotOverrideRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::uav_msgs::PilotOverrideRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::uav_msgs::PilotOverrideRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::uav_msgs::PilotOverrideRequest_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::uav_msgs::PilotOverrideRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::uav_msgs::PilotOverrideRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::uav_msgs::PilotOverrideRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "e93b05a1e536de6994950b45e76bd1de";
  }

  static const char* value(const ::uav_msgs::PilotOverrideRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xe93b05a1e536de69ULL;
  static const uint64_t static_value2 = 0x94950b45e76bd1deULL;
};

template<class ContainerAllocator>
struct DataType< ::uav_msgs::PilotOverrideRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "uav_msgs/PilotOverrideRequest";
  }

  static const char* value(const ::uav_msgs::PilotOverrideRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::uav_msgs::PilotOverrideRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# Available: LAND_SERV, RTL\n"
"string what\n"
;
  }

  static const char* value(const ::uav_msgs::PilotOverrideRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::uav_msgs::PilotOverrideRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.what);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct PilotOverrideRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::uav_msgs::PilotOverrideRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::uav_msgs::PilotOverrideRequest_<ContainerAllocator>& v)
  {
    s << indent << "what: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.what);
  }
};

} // namespace message_operations
} // namespace ros

#endif // UAV_MSGS_MESSAGE_PILOTOVERRIDEREQUEST_H
