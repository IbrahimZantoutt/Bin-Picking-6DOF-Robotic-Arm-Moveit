// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from bin_interfaces:srv/GetTargets.idl
// generated code does not contain a copyright notice

#ifndef BIN_INTERFACES__SRV__DETAIL__GET_TARGETS__STRUCT_H_
#define BIN_INTERFACES__SRV__DETAIL__GET_TARGETS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/GetTargets in the package bin_interfaces.
typedef struct bin_interfaces__srv__GetTargets_Request
{
  uint8_t structure_needs_at_least_one_member;
} bin_interfaces__srv__GetTargets_Request;

// Struct for a sequence of bin_interfaces__srv__GetTargets_Request.
typedef struct bin_interfaces__srv__GetTargets_Request__Sequence
{
  bin_interfaces__srv__GetTargets_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} bin_interfaces__srv__GetTargets_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'target'
#include "geometry_msgs/msg/detail/point_stamped__struct.h"

/// Struct defined in srv/GetTargets in the package bin_interfaces.
typedef struct bin_interfaces__srv__GetTargets_Response
{
  /// true if a cube is currently detected
  bool found;
  /// cube position, in the robot_base frame
  geometry_msgs__msg__PointStamped target;
} bin_interfaces__srv__GetTargets_Response;

// Struct for a sequence of bin_interfaces__srv__GetTargets_Response.
typedef struct bin_interfaces__srv__GetTargets_Response__Sequence
{
  bin_interfaces__srv__GetTargets_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} bin_interfaces__srv__GetTargets_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // BIN_INTERFACES__SRV__DETAIL__GET_TARGETS__STRUCT_H_
