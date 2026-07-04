#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};




// Corresponds to bin_interfaces__srv__GetTargets_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetTargets_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub structure_needs_at_least_one_member: u8,

}



impl Default for GetTargets_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::GetTargets_Request::default())
  }
}

impl rosidl_runtime_rs::Message for GetTargets_Request {
  type RmwMsg = super::srv::rmw::GetTargets_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        structure_needs_at_least_one_member: msg.structure_needs_at_least_one_member,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      structure_needs_at_least_one_member: msg.structure_needs_at_least_one_member,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      structure_needs_at_least_one_member: msg.structure_needs_at_least_one_member,
    }
  }
}


// Corresponds to bin_interfaces__srv__GetTargets_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetTargets_Response {
    /// true if a cube is currently detected
    pub found: bool,

    /// cube position, in the robot_base frame
    pub target: geometry_msgs::msg::PointStamped,

}



impl Default for GetTargets_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::GetTargets_Response::default())
  }
}

impl rosidl_runtime_rs::Message for GetTargets_Response {
  type RmwMsg = super::srv::rmw::GetTargets_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        found: msg.found,
        target: geometry_msgs::msg::PointStamped::into_rmw_message(std::borrow::Cow::Owned(msg.target)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      found: msg.found,
        target: geometry_msgs::msg::PointStamped::into_rmw_message(std::borrow::Cow::Borrowed(&msg.target)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      found: msg.found,
      target: geometry_msgs::msg::PointStamped::from_rmw_message(msg.target),
    }
  }
}






#[link(name = "bin_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__bin_interfaces__srv__GetTargets() -> *const std::ffi::c_void;
}

// Corresponds to bin_interfaces__srv__GetTargets
#[allow(missing_docs, non_camel_case_types)]
pub struct GetTargets;

impl rosidl_runtime_rs::Service for GetTargets {
    type Request = GetTargets_Request;
    type Response = GetTargets_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__bin_interfaces__srv__GetTargets() }
    }
}


