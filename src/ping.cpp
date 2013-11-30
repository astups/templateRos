/*
 *	Author: Lechalupé Julien
 *	Date: 10/19/2013
 *	Description: Tests for ROS - ASTUPS
 */

#include <ros/ros.h>
#include <unistd.h>
#include "MyRosSubscriber.hpp"
#include "MyRosPublisher.hpp"

#include <std_msgs/String.h>

int main(int argc, char** argv)
{
	ros::init(argc,argv,"Ping");

	MyRosSubscriber<std_msgs::String> sub("Pong");
	MyRosPublisher<std_msgs::String> pub("Ping");

	std_msgs::String message;
	bool ping = true;

	while(ros::ok())
	{
		if ( ping )
		{
			message.data = "Ping";
			pub.publish(message);
			ROS_INFO(" [Send] Ping");
			ping = false;
		}
		else
		{
			if( sub.isDataAvailable() )
			{
				message = sub.getData();
				ROS_INFO(" [Receive] %s",message.data.c_str());
				ping = true;
			}
		}

		ROS_INFO("loop");

		ros::spinOnce();

		sleep(1);
	}

	return 0;
}
