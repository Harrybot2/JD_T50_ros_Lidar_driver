/*********************************************************************
 *This is demo for ROS refering to xv_11_laser_driver.
 roslaunch LH_laser_driver LH_laser_publisher _frame_id:=LH_laser _port:=/dev/ttyUSB0 _baud_rate:=230400 _firmware_version:=2
echo LOCONH >/dev/ttyUSB0 //with intensity
echo LNCONH >/dev/ttyUSB0 //without intensity
echo LSTARH >/dev/ttyUSB0 //working begins
echo LSTOPH >/dev/ttyUSB0 //working stops
echo LRESTH >/dev/ttyUSB0 //working stops
echo LSRPM:xxxH >/dev/ttyUSB0 //set motor RPM
 *********************************************************************/

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <boost/asio.hpp>
#include <LH_laser_driver/LH_laser.h>
#include <std_msgs/UInt16.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "LH_laser_publisher");
  ros::NodeHandle n;
  ros::NodeHandle priv_nh("~");

  std::string port;
  int baud_rate;
  std::string frame_id;
  int firmware_number;
 
  std_msgs::UInt16 rpms; 

  priv_nh.param("port", port, std::string("/dev/ttyUSB0"));
  priv_nh.param("baud_rate", baud_rate, 230400);
  priv_nh.param("frame_id", frame_id, std::string("LH_laser"));
  priv_nh.param("firmware_version", firmware_number, 2);

  boost::asio::io_service io;
  ROS_INFO("1..The information before try");
  try {
    LH_laser_driver::LHLaser laser(port, baud_rate, firmware_number, io);
    ros::Publisher laser_pub = n.advertise<sensor_msgs::LaserScan>("scan", 1500);
    ros::Publisher motor_pub = n.advertise<std_msgs::UInt16>("rpms",1500);
    ROS_INFO("2..The information before scan");
    while (ros::ok()) {
      sensor_msgs::LaserScan::Ptr scan(new sensor_msgs::LaserScan);
      ROS_INFO("3..The information before try{2}");
      scan->header.frame_id = frame_id;
      ROS_INFO("4..The information before try{2}");
      scan->header.stamp = ros::Time::now();
      ROS_INFO("5..The information before try{2}");
      laser.poll(scan);
      ROS_INFO("6..The information before try{2}");
      rpms.data=laser.rpms;
      laser_pub.publish(scan);
      motor_pub.publish(rpms);
      ROS_INFO("rpms.data:[%d]",rpms.data);
    }
    laser.close();
    return 0;
  }catch (boost::system::system_error ex){
    ROS_INFO("4..The information before try{2}");
    ROS_ERROR("LH_laser Error:%s", ex.what());
    return -1;
  }
}
