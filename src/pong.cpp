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
	ros::init(argc,argv,"Pong");

	MyRosSubscriber<std_msgs::String> sub("Ping");
	MyRosPublisher<std_msgs::String> pub("Pong");

	std_msgs::String message;
	bool ping = true;

	while(ros::ok())
	{
		if ( !ping )
		{
			message.data = "Pong";
			pub.publish(message);
			ROS_INFO(" [Send] Pong");
			ping = true;
		}
		else
		{
			if( sub.isDataAvailable() )
			{
				message = sub.getData();
				ROS_INFO(" [Receive] %s",message.data.c_str());
				ping = false;
			}
		}

		ROS_INFO("loop");

		ros::spinOnce();

		sleep(1);
	}

	return 0;
}
