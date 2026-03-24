# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_cam_cpp_components_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED cam_cpp_components_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(cam_cpp_components_FOUND FALSE)
  elseif(NOT cam_cpp_components_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(cam_cpp_components_FOUND FALSE)
  endif()
  return()
endif()
set(_cam_cpp_components_CONFIG_INCLUDED TRUE)

# output package information
if(NOT cam_cpp_components_FIND_QUIETLY)
  message(STATUS "Found cam_cpp_components: 0.1.0 (${cam_cpp_components_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'cam_cpp_components' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${cam_cpp_components_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(cam_cpp_components_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${cam_cpp_components_DIR}/${_extra}")
endforeach()
