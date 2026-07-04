# generated from rosidl_generator_py/resource/_idl.py.em
# with input from bin_interfaces:srv/GetTargets.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_GetTargets_Request(type):
    """Metaclass of message 'GetTargets_Request'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('bin_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'bin_interfaces.srv.GetTargets_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__get_targets__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__get_targets__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__get_targets__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__get_targets__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__get_targets__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GetTargets_Request(metaclass=Metaclass_GetTargets_Request):
    """Message class 'GetTargets_Request'."""

    __slots__ = [
    ]

    _fields_and_field_types = {
    }

    SLOT_TYPES = (
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)


# Import statements for member types

import builtins  # noqa: E402, I100

# already imported above
# import rosidl_parser.definition


class Metaclass_GetTargets_Response(type):
    """Metaclass of message 'GetTargets_Response'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('bin_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'bin_interfaces.srv.GetTargets_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__get_targets__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__get_targets__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__get_targets__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__get_targets__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__get_targets__response

            from geometry_msgs.msg import PointStamped
            if PointStamped.__class__._TYPE_SUPPORT is None:
                PointStamped.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GetTargets_Response(metaclass=Metaclass_GetTargets_Response):
    """Message class 'GetTargets_Response'."""

    __slots__ = [
        '_found',
        '_target',
    ]

    _fields_and_field_types = {
        'found': 'boolean',
        'target': 'geometry_msgs/PointStamped',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'PointStamped'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.found = kwargs.get('found', bool())
        from geometry_msgs.msg import PointStamped
        self.target = kwargs.get('target', PointStamped())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.found != other.found:
            return False
        if self.target != other.target:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def found(self):
        """Message field 'found'."""
        return self._found

    @found.setter
    def found(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'found' field must be of type 'bool'"
        self._found = value

    @builtins.property
    def target(self):
        """Message field 'target'."""
        return self._target

    @target.setter
    def target(self, value):
        if __debug__:
            from geometry_msgs.msg import PointStamped
            assert \
                isinstance(value, PointStamped), \
                "The 'target' field must be a sub message of type 'PointStamped'"
        self._target = value


class Metaclass_GetTargets(type):
    """Metaclass of service 'GetTargets'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('bin_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'bin_interfaces.srv.GetTargets')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__get_targets

            from bin_interfaces.srv import _get_targets
            if _get_targets.Metaclass_GetTargets_Request._TYPE_SUPPORT is None:
                _get_targets.Metaclass_GetTargets_Request.__import_type_support__()
            if _get_targets.Metaclass_GetTargets_Response._TYPE_SUPPORT is None:
                _get_targets.Metaclass_GetTargets_Response.__import_type_support__()


class GetTargets(metaclass=Metaclass_GetTargets):
    from bin_interfaces.srv._get_targets import GetTargets_Request as Request
    from bin_interfaces.srv._get_targets import GetTargets_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
