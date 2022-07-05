cmake_minimum_required(VERSION 3.5)
project(gazebo_light_sensor)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


# find dependencies
find_package(gazebo REQUIRED)
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_ros REQUIRED)
find_package(gazebo_ros REQUIRED)
find_package(gazebo_plugins REQUIRED)
find_package(gazebo_msgs REQUIRED)
find_package(gazebo_dev REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)

find_package(camera_info_manager REQUIRED)
find_package(image_transport REQUIRED)
find_package(std_msgs REQUIRED)

include_directories(include)
include_directories(${GAZEBO_INCLUDE_DIRS} ${gazebo_plugins_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS} ${gazebo_plugins_LIBRARY_DIRS})

# gazebo_ros_camera
add_library(custom_gazebo_ros_camera SHARED
  src/custom_gazebo_ros_camera.cpp
)
target_include_directories(custom_gazebo_ros_camera PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_target_dependencies(custom_gazebo_ros_camera
  "camera_info_manager"
  "gazebo_dev"
  "gazebo_ros"
  "image_transport"
  "rclcpp"
  "sensor_msgs"
  "std_msgs"
)
target_link_libraries(custom_gazebo_ros_camera
  CameraPlugin
  DepthCameraPlugin
  MultiCameraPlugin
)
ament_export_libraries(custom_gazebo_ros_camera)
target_compile_definitions(custom_gazebo_ros_camera PRIVATE "GAZEBO_LIGHT_SENSOR_BUILDING_LIBRARY")
if(ENABLE_PROFILER)
  target_include_directories(custom_gazebo_ros_camera PUBLIC ${ignition-common3_INCLUDE_DIRS})
  target_link_libraries(custom_gazebo_ros_camera ${ignition-common3_LIBRARIES})
endif()

# light_sensor_plugin
add_library(light_sensor_plugin src/light_sensor_plugin.cpp)
target_include_directories(light_sensor_plugin PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
ament_target_dependencies(
  light_sensor_plugin
  "gazebo_ros"
  "gazebo_plugins"
  "gazebo_msgs"
  "gazebo_dev"
  "rclcpp"
  "sensor_msgs"
)
target_link_libraries(light_sensor_plugin
  custom_gazebo_ros_camera
)
ament_export_libraries(light_sensor_plugin)
# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_definitions(light_sensor_plugin PRIVATE "GAZEBO_LIGHT_SENSOR_BUILDING_LIBRARY")

# ament_export_dependencies(rclcpp)
# ament_export_dependencies(gazebo_dev)
# ament_export_dependencies(gazebo_msgs)
# ament_export_dependencies(gazebo_ros)



install(
  DIRECTORY include/
  DESTINATION include
)
install(
  TARGETS light_sensor_plugin custom_gazebo_ros_camera
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
install(DIRECTORY
  worlds
  DESTINATION share/${PROJECT_NAME}/
)
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_include_directories(
  include
)

# ament_export_targets(
#   export_${PROJECT_NAME}
# )

ament_package()
