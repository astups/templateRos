/*
 *	Author: Lechalupé Julien
 *	Date: 10/19/2013
 *	Description: Tests for ROS - ASTUPS
 */

#include <ros/ros.h>
#include <unistd.h>
#include "MyRosPublisher.hpp"

#include <std_msgs/String.h>

int main(int argc, char** argv)
{
	ros::init(argc,argv,"Hello_world_sub");

	MyRosPublisher<std_msgs::String> pub("Hello_World");

	std_msgs::String message;

	message.data = "Hello World [from Julien :)]";

	while(ros::ok())
	{
		pub.publish(message);

		ROS_INFO(" [PUB] Message...");

		sleep(1);
	}

	return 0;
}
