/*
 *	Author: Lechalupé Julien
 *	Date: 10/19/2013
 *	Description: Tests for ROS - ASTUPS
 */

#include <ros/ros.h>
#include <unistd.h>
#include "MyRosSubscriber.hpp"

#include <std_msgs/String.h>

int main(int argc, char** argv)
{
	ros::init(argc,argv,"Hello_world");

	MyRosSubscriber<std_msgs::String> sub("Hello_World");

	std_msgs::String message;

	while(ros::ok())
	{
		ROS_INFO(" [SUB] Check data...");
		if ( sub.isDataAvailable() )
		{
			message = sub.getData();
			ROS_INFO(" [SUB] %s",message.data.c_str());
		}
		else
		{
			ROS_INFO(" [SUB] No data available...");
		}

		MyRosSubscriber<std_msgs::String>::executeCallbacks();

		sleep(1);
	}

	return 0;
}
