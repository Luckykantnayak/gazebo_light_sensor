#ifndef GAZEBO_LIGHT_SENSOR__LIGHT_SENSOR_PLUGIN_HPP_
#define GAZEBO_LIGHT_SENSOR__LIGHT_SENSOR_PLUGIN_HPP_

#include "gazebo_light_sensor/visibility_control.h"
#include "gazebo_light_sensor/node_parameters_interface.hpp"
#include "gazebo_light_sensor/custom_gazebo_ros_camera.hpp"
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/illuminance.hpp>
namespace gazebo
{

  class LightSensorPlugin : public gazebo_plugins::GazeboRosCamera
  {
    public:
      LightSensorPlugin();

      virtual ~LightSensorPlugin();
      void Load(gazebo::sensors::SensorPtr _parent, sdf::ElementPtr _sdf);
    protected:  void OnNewFrame(const unsigned char *_image,
        unsigned int _width, unsigned int _height,
        unsigned int _depth, const std::string &_format) override;
    std::shared_ptr<rclcpp::Node> ros_node_ = rclcpp::Node::make_shared("light_sensor_plugin");
    rclcpp::Publisher<sensor_msgs::msg::Illuminance>::SharedPtr sensor_pub_;

    double _fov;
    double _range;
  };

}  // namespace gazebo_light_sensor

#endif  // GAZEBO_LIGHT_SENSOR__LIGHT_SENSOR_PLUGIN_HPP_
