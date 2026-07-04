#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[link(name = "bin_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__bin_interfaces__srv__GetTargets_Request() -> *const std::ffi::c_void;
}

#[link(name = "bin_interfaces__rosidl_generator_c")]
extern "C" {
    fn bin_interfaces__srv__GetTargets_Request__init(msg: *mut GetTargets_Request) -> bool;
    fn bin_interfaces__srv__GetTargets_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetTargets_Request>, size: usize) -> bool;
    fn bin_interfaces__srv__GetTargets_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetTargets_Request>);
    fn bin_interfaces__srv__GetTargets_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetTargets_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<GetTargets_Request>) -> bool;
}

// Corresponds to bin_interfaces__srv__GetTargets_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetTargets_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub structure_needs_at_least_one_member: u8,

}



impl Default for GetTargets_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !bin_interfaces__srv__GetTargets_Request__init(&mut msg as *mut _) {
        panic!("Call to bin_interfaces__srv__GetTargets_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetTargets_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { bin_interfaces__srv__GetTargets_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { bin_interfaces__srv__GetTargets_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { bin_interfaces__srv__GetTargets_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetTargets_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetTargets_Request where Self: Sized {
  const TYPE_NAME: &'static str = "bin_interfaces/srv/GetTargets_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__bin_interfaces__srv__GetTargets_Request() }
  }
}


#[link(name = "bin_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__bin_interfaces__srv__GetTargets_Response() -> *const std::ffi::c_void;
}

#[link(name = "bin_interfaces__rosidl_generator_c")]
extern "C" {
    fn bin_interfaces__srv__GetTargets_Response__init(msg: *mut GetTargets_Response) -> bool;
    fn bin_interfaces__srv__GetTargets_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetTargets_Response>, size: usize) -> bool;
    fn bin_interfaces__srv__GetTargets_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetTargets_Response>);
    fn bin_interfaces__srv__GetTargets_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetTargets_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<GetTargets_Response>) -> bool;
}

// Corresponds to bin_interfaces__srv__GetTargets_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetTargets_Response {
    /// true if a cube is currently detected
    pub found: bool,

    /// cube position, in the robot_base frame
    pub target: geometry_msgs::msg::rmw::PointStamped,

}



impl Default for GetTargets_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !bin_interfaces__srv__GetTargets_Response__init(&mut msg as *mut _) {
        panic!("Call to bin_interfaces__srv__GetTargets_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetTargets_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { bin_interfaces__srv__GetTargets_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { bin_interfaces__srv__GetTargets_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { bin_interfaces__srv__GetTargets_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetTargets_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetTargets_Response where Self: Sized {
  const TYPE_NAME: &'static str = "bin_interfaces/srv/GetTargets_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__bin_interfaces__srv__GetTargets_Response() }
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


