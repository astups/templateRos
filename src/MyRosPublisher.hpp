/**
 *	@author Julien Lechalupé
 *	ASTUPS 2013
 *	Publisher class template for ROS
 */

#include <ros/ros.h>
#include <string>
#include "nodemanager.hpp"

template <class T>
class MyRosPublisher
{
	protected:
		ros::Publisher 	_pub;

	public:

		/**
		 *	Constructor
		 *	@param nd Application NodeHandler
		 *	@param bufferSize Size of the sending buffer
		 *	@param publisherName Name of the publisher topic
		 */
		MyRosPublisher(const std::string& publisherName, int bufferSize = 64)
		{
			_pub = NodeManager::getInstance().advertise<T>(publisherName.c_str(),bufferSize);
		}


		/**
		 *	Destructor
		 */
		~MyRosPublisher()
		{
			_pub.shutdown();
		}

		/**
		 *	Publishing routine
		 *	Publish message on the ros network under the name of the topic publisherName
		 *	@param message Data to send
		 */
		void publish(const T& message) const
		{
			_pub.publish(message);
		}
};
