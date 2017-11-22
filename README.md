# JD_T50_ros_Lidar_driver
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
