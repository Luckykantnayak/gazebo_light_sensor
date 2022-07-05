#include "gazebo_light_sensor/light_sensor_plugin.hpp"
#include <gazebo/common/Plugin.hh>
#include <string>

#include <gazebo/sensors/Sensor.hh>
#include <gazebo/sensors/CameraSensor.hh>
#include <gazebo/sensors/SensorTypes.hh>
#include <sensor_msgs/msg/illuminance.hpp>

namespace gazebo
{
GZ_REGISTER_SENSOR_PLUGIN(LightSensorPlugin)
LightSensorPlugin::LightSensorPlugin()
:_fov(6),_range(10)
{

}

LightSensorPlugin::~LightSensorPlugin()
{
  RCLCPP_DEBUG_STREAM(ros_node_->get_logger(), "Camera unloaded");
}
void LightSensorPlugin::Load(gazebo::sensors::SensorPtr _parent, sdf::ElementPtr _sdf) {
  if(!rclcpp::ok())
  {
    RCLCPP_FATAL_STREAM(ros_node_->get_logger(),"A ROS node for Gazebo has not been initialized, unable to load plugin. "
        << "Load the Gazebo system plugin 'libgazebo_ros_api_plugin.so' in the gazebo_ros package)");
    return;
  }

  sensor_pub_ = ros_node_->create_publisher<sensor_msgs::msg::Illuminance>("lightSensor",1);
  GazeboRosCamera::Load(_parent,_sdf);


}
void LightSensorPlugin::OnNewFrame(const unsigned char *_image,
    unsigned int _width, unsigned int _height,
    unsigned int _depth, const std::string &_format) {





    sensor_msgs::msg::Illuminance msg;
    msg.header.stamp = rclcpp::Clock().now();
    msg.header.frame_id = "";
    //msg.header.seq = seq;

    int startingPix = _width * ( (int)(_height/2) - (int)( _fov/2)) - (int)(_fov/2);

    double illum = 0;
    for (int i=0; i<_fov ; ++i)
    {
      int index = startingPix + i*_width;
      for (int j=0; j<_fov ; ++j)
        illum += _image[index+j];
    }

    msg.illuminance = illum/(_fov*_fov);
    msg.variance = 0.0;

    sensor_pub_->publish(msg);
   }



}  // namespace gazebo_light_sensor
