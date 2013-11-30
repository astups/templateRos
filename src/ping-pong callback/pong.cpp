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

MyRosPublisher<std_msgs::String>* pub;

void callback(const boost::shared_ptr<std_msgs::String>& ptrData)
{
	if ( ptrData != NULL )
	{
		std_msgs::String message = *ptrData;

		ROS_INFO(" [Receive] %s",message.data.c_str());

		message.data = "Pong";
		pub->publish(message);
		ROS_INFO(" [Send] Pong");
	}
}

int main(int argc, char** argv)
{
	ros::init(argc,argv,"Pong");

	MyRosSubscriber<std_msgs::String> sub("Ping",64,&callback);

	pub = new MyRosPublisher<std_msgs::String>("Pong");

	while(ros::ok())
	{
		ROS_INFO("loop");

		ros::spinOnce();

		sleep(1);
	}

	delete pub;

	return 0;
}
