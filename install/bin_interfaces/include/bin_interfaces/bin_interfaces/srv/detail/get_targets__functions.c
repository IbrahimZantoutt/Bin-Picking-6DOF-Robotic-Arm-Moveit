// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from bin_interfaces:srv/GetTargets.idl
// generated code does not contain a copyright notice
#include "bin_interfaces/srv/detail/get_targets__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
bin_interfaces__srv__GetTargets_Request__init(bin_interfaces__srv__GetTargets_Request * msg)
{
  if (!msg) {
    return false;
  }
  // structure_needs_at_least_one_member
  return true;
}

void
bin_interfaces__srv__GetTargets_Request__fini(bin_interfaces__srv__GetTargets_Request * msg)
{
  if (!msg) {
    return;
  }
  // structure_needs_at_least_one_member
}

bool
bin_interfaces__srv__GetTargets_Request__are_equal(const bin_interfaces__srv__GetTargets_Request * lhs, const bin_interfaces__srv__GetTargets_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // structure_needs_at_least_one_member
  if (lhs->structure_needs_at_least_one_member != rhs->structure_needs_at_least_one_member) {
    return false;
  }
  return true;
}

bool
bin_interfaces__srv__GetTargets_Request__copy(
  const bin_interfaces__srv__GetTargets_Request * input,
  bin_interfaces__srv__GetTargets_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // structure_needs_at_least_one_member
  output->structure_needs_at_least_one_member = input->structure_needs_at_least_one_member;
  return true;
}

bin_interfaces__srv__GetTargets_Request *
bin_interfaces__srv__GetTargets_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  bin_interfaces__srv__GetTargets_Request * msg = (bin_interfaces__srv__GetTargets_Request *)allocator.allocate(sizeof(bin_interfaces__srv__GetTargets_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(bin_interfaces__srv__GetTargets_Request));
  bool success = bin_interfaces__srv__GetTargets_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
bin_interfaces__srv__GetTargets_Request__destroy(bin_interfaces__srv__GetTargets_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    bin_interfaces__srv__GetTargets_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
bin_interfaces__srv__GetTargets_Request__Sequence__init(bin_interfaces__srv__GetTargets_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  bin_interfaces__srv__GetTargets_Request * data = NULL;

  if (size) {
    data = (bin_interfaces__srv__GetTargets_Request *)allocator.zero_allocate(size, sizeof(bin_interfaces__srv__GetTargets_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = bin_interfaces__srv__GetTargets_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        bin_interfaces__srv__GetTargets_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
bin_interfaces__srv__GetTargets_Request__Sequence__fini(bin_interfaces__srv__GetTargets_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      bin_interfaces__srv__GetTargets_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

bin_interfaces__srv__GetTargets_Request__Sequence *
bin_interfaces__srv__GetTargets_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  bin_interfaces__srv__GetTargets_Request__Sequence * array = (bin_interfaces__srv__GetTargets_Request__Sequence *)allocator.allocate(sizeof(bin_interfaces__srv__GetTargets_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = bin_interfaces__srv__GetTargets_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
bin_interfaces__srv__GetTargets_Request__Sequence__destroy(bin_interfaces__srv__GetTargets_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    bin_interfaces__srv__GetTargets_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
bin_interfaces__srv__GetTargets_Request__Sequence__are_equal(const bin_interfaces__srv__GetTargets_Request__Sequence * lhs, const bin_interfaces__srv__GetTargets_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!bin_interfaces__srv__GetTargets_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
bin_interfaces__srv__GetTargets_Request__Sequence__copy(
  const bin_interfaces__srv__GetTargets_Request__Sequence * input,
  bin_interfaces__srv__GetTargets_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(bin_interfaces__srv__GetTargets_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    bin_interfaces__srv__GetTargets_Request * data =
      (bin_interfaces__srv__GetTargets_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!bin_interfaces__srv__GetTargets_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          bin_interfaces__srv__GetTargets_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!bin_interfaces__srv__GetTargets_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `target`
#include "geometry_msgs/msg/detail/point_stamped__functions.h"

bool
bin_interfaces__srv__GetTargets_Response__init(bin_interfaces__srv__GetTargets_Response * msg)
{
  if (!msg) {
    return false;
  }
  // found
  // target
  if (!geometry_msgs__msg__PointStamped__init(&msg->target)) {
    bin_interfaces__srv__GetTargets_Response__fini(msg);
    return false;
  }
  return true;
}

void
bin_interfaces__srv__GetTargets_Response__fini(bin_interfaces__srv__GetTargets_Response * msg)
{
  if (!msg) {
    return;
  }
  // found
  // target
  geometry_msgs__msg__PointStamped__fini(&msg->target);
}

bool
bin_interfaces__srv__GetTargets_Response__are_equal(const bin_interfaces__srv__GetTargets_Response * lhs, const bin_interfaces__srv__GetTargets_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // found
  if (lhs->found != rhs->found) {
    return false;
  }
  // target
  if (!geometry_msgs__msg__PointStamped__are_equal(
      &(lhs->target), &(rhs->target)))
  {
    return false;
  }
  return true;
}

bool
bin_interfaces__srv__GetTargets_Response__copy(
  const bin_interfaces__srv__GetTargets_Response * input,
  bin_interfaces__srv__GetTargets_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // found
  output->found = input->found;
  // target
  if (!geometry_msgs__msg__PointStamped__copy(
      &(input->target), &(output->target)))
  {
    return false;
  }
  return true;
}

bin_interfaces__srv__GetTargets_Response *
bin_interfaces__srv__GetTargets_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  bin_interfaces__srv__GetTargets_Response * msg = (bin_interfaces__srv__GetTargets_Response *)allocator.allocate(sizeof(bin_interfaces__srv__GetTargets_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(bin_interfaces__srv__GetTargets_Response));
  bool success = bin_interfaces__srv__GetTargets_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
bin_interfaces__srv__GetTargets_Response__destroy(bin_interfaces__srv__GetTargets_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    bin_interfaces__srv__GetTargets_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
bin_interfaces__srv__GetTargets_Response__Sequence__init(bin_interfaces__srv__GetTargets_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  bin_interfaces__srv__GetTargets_Response * data = NULL;

  if (size) {
    data = (bin_interfaces__srv__GetTargets_Response *)allocator.zero_allocate(size, sizeof(bin_interfaces__srv__GetTargets_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = bin_interfaces__srv__GetTargets_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        bin_interfaces__srv__GetTargets_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
bin_interfaces__srv__GetTargets_Response__Sequence__fini(bin_interfaces__srv__GetTargets_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      bin_interfaces__srv__GetTargets_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

bin_interfaces__srv__GetTargets_Response__Sequence *
bin_interfaces__srv__GetTargets_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  bin_interfaces__srv__GetTargets_Response__Sequence * array = (bin_interfaces__srv__GetTargets_Response__Sequence *)allocator.allocate(sizeof(bin_interfaces__srv__GetTargets_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = bin_interfaces__srv__GetTargets_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
bin_interfaces__srv__GetTargets_Response__Sequence__destroy(bin_interfaces__srv__GetTargets_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    bin_interfaces__srv__GetTargets_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
bin_interfaces__srv__GetTargets_Response__Sequence__are_equal(const bin_interfaces__srv__GetTargets_Response__Sequence * lhs, const bin_interfaces__srv__GetTargets_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!bin_interfaces__srv__GetTargets_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
bin_interfaces__srv__GetTargets_Response__Sequence__copy(
  const bin_interfaces__srv__GetTargets_Response__Sequence * input,
  bin_interfaces__srv__GetTargets_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(bin_interfaces__srv__GetTargets_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    bin_interfaces__srv__GetTargets_Response * data =
      (bin_interfaces__srv__GetTargets_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!bin_interfaces__srv__GetTargets_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          bin_interfaces__srv__GetTargets_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!bin_interfaces__srv__GetTargets_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
