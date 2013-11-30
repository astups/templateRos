/**
 *	@author Julien Lechalupé
 *	ASTUPS 2013
 *	Publisher class template for ROS
 */

#include <ros/ros.h>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include "nodemanager.hpp"

template <class T>
class MyRosSubscriber
{
	private:
		/**
		 *	Private Method
		 *	Listen callback, called when piece of data received
		 */
		void listenCallback(const boost::shared_ptr<T>& ptrData)
		{
			if ( ptrData != NULL )
			{
				_data = (*ptrData);
				_isAvailable = true;
			}
		}

	protected:
		ros::Subscriber _sub;
		T 				_data;
		bool 			_isAvailable;

	public:

		/**
		 *	Constructor
		 *	@param bufferSize Size of the sending buffer
		 *	@param publisherName Name of the subscriber topic
		 *	@param callback Function pointer on the callback function
		 */
		MyRosSubscriber(const std::string& subscriberName,int bufferSize = 64, void(* callback)(const boost::shared_ptr<T>&) = NULL)
		{
			if ( callback == NULL )
			{
				_sub = NodeManager::getInstance().subscribe(subscriberName,bufferSize,&MyRosSubscriber::listenCallback,this);
				//_sub = boost::bind(NodeManager::getInstance().subscribe, subscriberName, bufferSize, &MyRosSubscriber::listenCallback);
			}
			else
			{
				_sub = NodeManager::getInstance().subscribe(subscriberName,bufferSize,callback);
			}
			
			_isAvailable = false;
		}


		/**
		 *	Destructor
		 */
		~MyRosSubscriber()
		{
			_sub.shutdown();
		}

		/**
		 *	Getter
		 *	Get the data received and filtered by the function selector
		 *	@return Data received
		 */
		T getData() throw(std::string) 
		{
			if ( !_isAvailable )
			{
				throw(std::string("Error: no data available"));
			}

			_isAvailable = false;

			return _data;
		}

		/**
		 *	Getter
		 *	Get boolean representing data availability
		 *	@return True if data available else otherwise
		 */
		bool isDataAvailable() const
		{
			return _isAvailable;
		}

		/**
		 *	Static method
		 *	Call all the subscriber callbacks via ROS
		 *	callAllCallbacks => (isDataAvailable <- if (dataReceived) true else false )
		 */
		static void executeCallbacks()
		{
			ros::spinOnce();
		}
};
	
