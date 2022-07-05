#ifndef GAZEBO_LIGHT_SENSOR__VISIBILITY_CONTROL_H_
#define GAZEBO_LIGHT_SENSOR__VISIBILITY_CONTROL_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define GAZEBO_LIGHT_SENSOR_EXPORT __attribute__ ((dllexport))
    #define GAZEBO_LIGHT_SENSOR_IMPORT __attribute__ ((dllimport))
  #else
    #define GAZEBO_LIGHT_SENSOR_EXPORT __declspec(dllexport)
    #define GAZEBO_LIGHT_SENSOR_IMPORT __declspec(dllimport)
  #endif
  #ifdef GAZEBO_LIGHT_SENSOR_BUILDING_LIBRARY
    #define GAZEBO_LIGHT_SENSOR_PUBLIC GAZEBO_LIGHT_SENSOR_EXPORT
  #else
    #define GAZEBO_LIGHT_SENSOR_PUBLIC GAZEBO_LIGHT_SENSOR_IMPORT
  #endif
  #define GAZEBO_LIGHT_SENSOR_PUBLIC_TYPE GAZEBO_LIGHT_SENSOR_PUBLIC
  #define GAZEBO_LIGHT_SENSOR_LOCAL
#else
  #define GAZEBO_LIGHT_SENSOR_EXPORT __attribute__ ((visibility("default")))
  #define GAZEBO_LIGHT_SENSOR_IMPORT
  #if __GNUC__ >= 4
    #define GAZEBO_LIGHT_SENSOR_PUBLIC __attribute__ ((visibility("default")))
    #define GAZEBO_LIGHT_SENSOR_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define GAZEBO_LIGHT_SENSOR_PUBLIC
    #define GAZEBO_LIGHT_SENSOR_LOCAL
  #endif
  #define GAZEBO_LIGHT_SENSOR_PUBLIC_TYPE
#endif

#endif  // GAZEBO_LIGHT_SENSOR__VISIBILITY_CONTROL_H_
