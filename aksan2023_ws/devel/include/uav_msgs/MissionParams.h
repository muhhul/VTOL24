// Generated by gencpp from file uav_msgs/MissionParams.msg
// DO NOT EDIT!


#ifndef UAV_MSGS_MESSAGE_MISSIONPARAMS_H
#define UAV_MSGS_MESSAGE_MISSIONPARAMS_H


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
struct MissionParams_
{
  typedef MissionParams_<ContainerAllocator> Type;

  MissionParams_()
    : bools()
    , ints()
    , strings()
    , doubles()  {
    }
  MissionParams_(const ContainerAllocator& _alloc)
    : bools(_alloc)
    , ints(_alloc)
    , strings(_alloc)
    , doubles(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<uint8_t>> _bools_type;
  _bools_type bools;

   typedef std::vector<int16_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int16_t>> _ints_type;
  _ints_type ints;

   typedef std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> _strings_type;
  _strings_type strings;

   typedef std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> _doubles_type;
  _doubles_type doubles;





  typedef boost::shared_ptr< ::uav_msgs::MissionParams_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::uav_msgs::MissionParams_<ContainerAllocator> const> ConstPtr;

}; // struct MissionParams_

typedef ::uav_msgs::MissionParams_<std::allocator<void> > MissionParams;

typedef boost::shared_ptr< ::uav_msgs::MissionParams > MissionParamsPtr;
typedef boost::shared_ptr< ::uav_msgs::MissionParams const> MissionParamsConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::uav_msgs::MissionParams_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::uav_msgs::MissionParams_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::uav_msgs::MissionParams_<ContainerAllocator1> & lhs, const ::uav_msgs::MissionParams_<ContainerAllocator2> & rhs)
{
  return lhs.bools == rhs.bools &&
    lhs.ints == rhs.ints &&
    lhs.strings == rhs.strings &&
    lhs.doubles == rhs.doubles;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::uav_msgs::MissionParams_<ContainerAllocator1> & lhs, const ::uav_msgs::MissionParams_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace uav_msgs

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::uav_msgs::MissionParams_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::uav_msgs::MissionParams_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::uav_msgs::MissionParams_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::uav_msgs::MissionParams_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::uav_msgs::MissionParams_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::uav_msgs::MissionParams_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::uav_msgs::MissionParams_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bc0a18721b20b19e0ac5fce7cb2d9e52";
  }

  static const char* value(const ::uav_msgs::MissionParams_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xbc0a18721b20b19eULL;
  static const uint64_t static_value2 = 0x0ac5fce7cb2d9e52ULL;
};

template<class ContainerAllocator>
struct DataType< ::uav_msgs::MissionParams_<ContainerAllocator> >
{
  static const char* value()
  {
    return "uav_msgs/MissionParams";
  }

  static const char* value(const ::uav_msgs::MissionParams_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::uav_msgs::MissionParams_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool[] bools\n"
"int16[] ints\n"
"string[] strings\n"
"float64[] doubles\n"
;
  }

  static const char* value(const ::uav_msgs::MissionParams_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::uav_msgs::MissionParams_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.bools);
      stream.next(m.ints);
      stream.next(m.strings);
      stream.next(m.doubles);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct MissionParams_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::uav_msgs::MissionParams_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::uav_msgs::MissionParams_<ContainerAllocator>& v)
  {
    s << indent << "bools[]" << std::endl;
    for (size_t i = 0; i < v.bools.size(); ++i)
    {
      s << indent << "  bools[" << i << "]: ";
      Printer<uint8_t>::stream(s, indent + "  ", v.bools[i]);
    }
    s << indent << "ints[]" << std::endl;
    for (size_t i = 0; i < v.ints.size(); ++i)
    {
      s << indent << "  ints[" << i << "]: ";
      Printer<int16_t>::stream(s, indent + "  ", v.ints[i]);
    }
    s << indent << "strings[]" << std::endl;
    for (size_t i = 0; i < v.strings.size(); ++i)
    {
      s << indent << "  strings[" << i << "]: ";
      Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.strings[i]);
    }
    s << indent << "doubles[]" << std::endl;
    for (size_t i = 0; i < v.doubles.size(); ++i)
    {
      s << indent << "  doubles[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.doubles[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // UAV_MSGS_MESSAGE_MISSIONPARAMS_H
