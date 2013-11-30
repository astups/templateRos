/**
 *	@author Julien Lechalupé
 *	ASTUPS 2013
 *	NodeHandle singleton manager
 */

#ifndef NODEMANAGER_INCLUDE
#define NODEMANAGER_INCLUDE 1

 class NodeManager
 {
 	private:
 		static ros::NodeHandle* _handle;

 		/**
		 *	Constructor
		 *	Prevents unwanted constructions (singleton)
		 */
 		NodeManager()
 		{
 			_handle = NULL;
 		}

 	public:
 		/**
 		 *	Getters
 		 *	Get the global reference of the NodeHandle
 		 *	Build automaticaly if the reference does not exist
 		 */
 		static ros::NodeHandle& getInstance()
 		{
 			if ( _handle == NULL )
 			{
 				_handle = new ros::NodeHandle();
 			}

 			return (*_handle);
 		}

 		/**
 		 *	Destructor
 		 */
 		~NodeManager()
 		{
 			if ( _handle != NULL )
 			{
 				delete _handle;
 			}
 		}
 };

ros::NodeHandle* NodeManager::_handle = NULL;

#endif
