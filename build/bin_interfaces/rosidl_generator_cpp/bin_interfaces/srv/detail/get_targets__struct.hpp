// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from bin_interfaces:srv/GetTargets.idl
// generated code does not contain a copyright notice

#ifndef BIN_INTERFACES__SRV__DETAIL__GET_TARGETS__STRUCT_HPP_
#define BIN_INTERFACES__SRV__DETAIL__GET_TARGETS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__bin_interfaces__srv__GetTargets_Request __attribute__((deprecated))
#else
# define DEPRECATED__bin_interfaces__srv__GetTargets_Request __declspec(deprecated)
#endif

namespace bin_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetTargets_Request_
{
  using Type = GetTargets_Request_<ContainerAllocator>;

  explicit GetTargets_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  explicit GetTargets_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  // field types and members
  using _structure_needs_at_least_one_member_type =
    uint8_t;
  _structure_needs_at_least_one_member_type structure_needs_at_least_one_member;


  // constant declarations

  // pointer types
  using RawPtr =
    bin_interfaces::srv::GetTargets_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const bin_interfaces::srv::GetTargets_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<bin_interfaces::srv::GetTargets_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<bin_interfaces::srv::GetTargets_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      bin_interfaces::srv::GetTargets_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<bin_interfaces::srv::GetTargets_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      bin_interfaces::srv::GetTargets_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<bin_interfaces::srv::GetTargets_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<bin_interfaces::srv::GetTargets_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<bin_interfaces::srv::GetTargets_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__bin_interfaces__srv__GetTargets_Request
    std::shared_ptr<bin_interfaces::srv::GetTargets_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__bin_interfaces__srv__GetTargets_Request
    std::shared_ptr<bin_interfaces::srv::GetTargets_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetTargets_Request_ & other) const
  {
    if (this->structure_needs_at_least_one_member != other.structure_needs_at_least_one_member) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetTargets_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetTargets_Request_

// alias to use template instance with default allocator
using GetTargets_Request =
  bin_interfaces::srv::GetTargets_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace bin_interfaces


// Include directives for member types
// Member 'target'
#include "geometry_msgs/msg/detail/point_stamped__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__bin_interfaces__srv__GetTargets_Response __attribute__((deprecated))
#else
# define DEPRECATED__bin_interfaces__srv__GetTargets_Response __declspec(deprecated)
#endif

namespace bin_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetTargets_Response_
{
  using Type = GetTargets_Response_<ContainerAllocator>;

  explicit GetTargets_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : target(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->found = false;
    }
  }

  explicit GetTargets_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : target(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->found = false;
    }
  }

  // field types and members
  using _found_type =
    bool;
  _found_type found;
  using _target_type =
    geometry_msgs::msg::PointStamped_<ContainerAllocator>;
  _target_type target;

  // setters for named parameter idiom
  Type & set__found(
    const bool & _arg)
  {
    this->found = _arg;
    return *this;
  }
  Type & set__target(
    const geometry_msgs::msg::PointStamped_<ContainerAllocator> & _arg)
  {
    this->target = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    bin_interfaces::srv::GetTargets_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const bin_interfaces::srv::GetTargets_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<bin_interfaces::srv::GetTargets_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<bin_interfaces::srv::GetTargets_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      bin_interfaces::srv::GetTargets_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<bin_interfaces::srv::GetTargets_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      bin_interfaces::srv::GetTargets_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<bin_interfaces::srv::GetTargets_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<bin_interfaces::srv::GetTargets_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<bin_interfaces::srv::GetTargets_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__bin_interfaces__srv__GetTargets_Response
    std::shared_ptr<bin_interfaces::srv::GetTargets_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__bin_interfaces__srv__GetTargets_Response
    std::shared_ptr<bin_interfaces::srv::GetTargets_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetTargets_Response_ & other) const
  {
    if (this->found != other.found) {
      return false;
    }
    if (this->target != other.target) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetTargets_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetTargets_Response_

// alias to use template instance with default allocator
using GetTargets_Response =
  bin_interfaces::srv::GetTargets_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace bin_interfaces

namespace bin_interfaces
{

namespace srv
{

struct GetTargets
{
  using Request = bin_interfaces::srv::GetTargets_Request;
  using Response = bin_interfaces::srv::GetTargets_Response;
};

}  // namespace srv

}  // namespace bin_interfaces

#endif  // BIN_INTERFACES__SRV__DETAIL__GET_TARGETS__STRUCT_HPP_
