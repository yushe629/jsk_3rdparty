/*
    Description: The screen will display TVOC and CO2.
    Note: SGP30 needs 15 seconds to initialize calibration after power on.
*/

// Mainly copied from
// https://github.com/m5stack/M5-ProductExampleCodes/tree/master/Unit/TVOC/TVOC

#include <m5stack_ros.h>
#include <TVOC_SGP30.h>
#include <std_msgs/UInt16.h>
#include <sound_play/SoundRequestActionGoal.h>

std_msgs::UInt16 tvoc_msg;
ros::Publisher tvoc_pub("tvoc", &tvoc_msg);
std_msgs::UInt16 eco2_msg;
ros::Publisher eco2_pub("eco2", &eco2_msg);

void setup() {
  setupM5stackROS("M5Stack ROS TVOC SGP30");
  setupTVOCSGP30();
  nh.advertise(tvoc_pub);
  nh.advertise(eco2_pub);
}

void loop() {
  measureTVOCSGP30();

  tvoc_msg.data = sgp.TVOC;
  tvoc_pub.publish(&tvoc_msg);
  eco2_msg.data = sgp.eCO2;
  eco2_pub.publish(&eco2_msg);

  nh.spinOnce();
  delay(100);
}
