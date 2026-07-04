// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from bin_interfaces:srv/GetTargets.idl
// generated code does not contain a copyright notice

#ifndef BIN_INTERFACES__SRV__DETAIL__GET_TARGETS__TRAITS_HPP_
#define BIN_INTERFACES__SRV__DETAIL__GET_TARGETS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "bin_interfaces/srv/detail/get_targets__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace bin_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetTargets_Request & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetTargets_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetTargets_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace bin_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use bin_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const bin_interfaces::srv::GetTargets_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  bin_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use bin_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const bin_interfaces::srv::GetTargets_Request & msg)
{
  return bin_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<bin_interfaces::srv::GetTargets_Request>()
{
  return "bin_interfaces::srv::GetTargets_Request";
}

template<>
inline const char * name<bin_interfaces::srv::GetTargets_Request>()
{
  return "bin_interfaces/srv/GetTargets_Request";
}

template<>
struct has_fixed_size<bin_interfaces::srv::GetTargets_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<bin_interfaces::srv::GetTargets_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<bin_interfaces::srv::GetTargets_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'target'
#include "geometry_msgs/msg/detail/point_stamped__traits.hpp"

namespace bin_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetTargets_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: found
  {
    out << "found: ";
    rosidl_generator_traits::value_to_yaml(msg.found, out);
    out << ", ";
  }

  // member: target
  {
    out << "target: ";
    to_flow_style_yaml(msg.target, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetTargets_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: found
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "found: ";
    rosidl_generator_traits::value_to_yaml(msg.found, out);
    out << "\n";
  }

  // member: target
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target:\n";
    to_block_style_yaml(msg.target, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetTargets_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace bin_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use bin_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const bin_interfaces::srv::GetTargets_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  bin_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use bin_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const bin_interfaces::srv::GetTargets_Response & msg)
{
  return bin_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<bin_interfaces::srv::GetTargets_Response>()
{
  return "bin_interfaces::srv::GetTargets_Response";
}

template<>
inline const char * name<bin_interfaces::srv::GetTargets_Response>()
{
  return "bin_interfaces/srv/GetTargets_Response";
}

template<>
struct has_fixed_size<bin_interfaces::srv::GetTargets_Response>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::PointStamped>::value> {};

template<>
struct has_bounded_size<bin_interfaces::srv::GetTargets_Response>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::PointStamped>::value> {};

template<>
struct is_message<bin_interfaces::srv::GetTargets_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<bin_interfaces::srv::GetTargets>()
{
  return "bin_interfaces::srv::GetTargets";
}

template<>
inline const char * name<bin_interfaces::srv::GetTargets>()
{
  return "bin_interfaces/srv/GetTargets";
}

template<>
struct has_fixed_size<bin_interfaces::srv::GetTargets>
  : std::integral_constant<
    bool,
    has_fixed_size<bin_interfaces::srv::GetTargets_Request>::value &&
    has_fixed_size<bin_interfaces::srv::GetTargets_Response>::value
  >
{
};

template<>
struct has_bounded_size<bin_interfaces::srv::GetTargets>
  : std::integral_constant<
    bool,
    has_bounded_size<bin_interfaces::srv::GetTargets_Request>::value &&
    has_bounded_size<bin_interfaces::srv::GetTargets_Response>::value
  >
{
};

template<>
struct is_service<bin_interfaces::srv::GetTargets>
  : std::true_type
{
};

template<>
struct is_service_request<bin_interfaces::srv::GetTargets_Request>
  : std::true_type
{
};

template<>
struct is_service_response<bin_interfaces::srv::GetTargets_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // BIN_INTERFACES__SRV__DETAIL__GET_TARGETS__TRAITS_HPP_
