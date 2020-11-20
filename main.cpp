#include <pthread.h>
#include "Options.h"
#include "Manager.h"
#include "Driver.h"
#include "Node.h"
#include "Group.h"
#include "Notification.h"
#include "value_classes/ValueStore.h"
#include "value_classes/Value.h"
#include "value_classes/ValueBool.h"
#include "platform/Log.h"
#include "Defs.h"
#include <map>
#include <iostream>

struct Node
{
	Node(uint32 nodeId)
	: nodeId(nodeId)
	{}

	const uint32 nodeId;
};

struct Home
{
	Home(uint32 homeId)
	: homeId(homeId)
	{}

	const uint32 homeId;
	std::map<uint32, Node> Nodes;
};

struct State
{
	State()
	{		
		pthread_mutexattr_t mutexattr;

		pthread_mutexattr_init(&mutexattr);
		pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE);
		pthread_mutex_init(&Mutex, &mutexattr);
		pthread_mutexattr_destroy(&mutexattr);		
	}

	~State()
	{
		pthread_mutex_destroy(&Mutex);
		std::cout<<"Destroying state"<<std::endl;
	}

	pthread_mutex_t Mutex;
	const std::map<uint32, Home> Homes;
};

void OnNotification(OpenZWave::Notification const& notification, State& state)
{
	pthread_mutex_lock(&state.Mutex);

	switch(notification.GetType() )
	{
		case OpenZWave::Notification::Type_ValueAdded: break;
		case OpenZWave::Notification::Type_ValueRemoved: break;
		case OpenZWave::Notification::Type_ValueChanged: break;
		case OpenZWave::Notification::Type_ValueRefreshed: break;
		case OpenZWave::Notification::Type_Group: break;
		case OpenZWave::Notification::Type_NodeNew: break;
		case OpenZWave::Notification::Type_NodeAdded: break;
		case OpenZWave::Notification::Type_NodeRemoved: break;
		case OpenZWave::Notification::Type_NodeProtocolInfo: break;
		case OpenZWave::Notification::Type_NodeNaming: break;
		case OpenZWave::Notification::Type_NodeEvent: break;
		case OpenZWave::Notification::Type_PollingDisabled: break;
		case OpenZWave::Notification::Type_PollingEnabled: break;
		case OpenZWave::Notification::Type_SceneEvent: break;
		case OpenZWave::Notification::Type_CreateButton: break;
		case OpenZWave::Notification::Type_DeleteButton: break;
		case OpenZWave::Notification::Type_ButtonOn: break;
		case OpenZWave::Notification::Type_ButtonOff: break;
		case OpenZWave::Notification::Type_DriverReady: break;
		case OpenZWave::Notification::Type_DriverFailed: break;
		case OpenZWave::Notification::Type_DriverReset: break;
		case OpenZWave::Notification::Type_EssentialNodeQueriesComplete: break;
		case OpenZWave::Notification::Type_NodeQueriesComplete: break;
		case OpenZWave::Notification::Type_AwakeNodesQueried: break;
		case OpenZWave::Notification::Type_AllNodesQueriedSomeDead: break;
		case OpenZWave::Notification::Type_AllNodesQueried: break;
		case OpenZWave::Notification::Type_Notification: break;
		case OpenZWave::Notification::Type_DriverRemoved: break;
		case OpenZWave::Notification::Type_ControllerCommand: break;
		case OpenZWave::Notification::Type_NodeReset: break;
		case OpenZWave::Notification::Type_UserAlerts: break;
		case OpenZWave::Notification::Type_ManufacturerSpecificDBReady: break;
	}

	pthread_mutex_unlock(&state.Mutex);
}

void OnNotification(OpenZWave::Notification const* notification, void* context)
{
	OnNotification(*notification, *static_cast<State*>(context));
}

int main( int argc, char* argv[] )
{
	auto port = "/dev/ttyACM01";

	auto state = State();	
	
	std::cout<<"Starting Jottai ..."<<std::endl;

	OpenZWave::Options::Create( "./open-zwave/config/", "", "" );
	OpenZWave::Options::Get()->AddOptionInt("SaveLogLevel", OpenZWave::LogLevel_Detail );
	OpenZWave::Options::Get()->AddOptionInt("QueueLogLevel", OpenZWave::LogLevel_Debug );
	OpenZWave::Options::Get()->AddOptionInt("DumpTrigger", OpenZWave::LogLevel_Error );
	OpenZWave::Options::Get()->AddOptionInt("PollInterval", 500 );
	OpenZWave::Options::Get()->AddOptionBool("IntervalBetweenPolls", true );
	OpenZWave::Options::Get()->AddOptionBool("ValidateValueChanges", true);
	OpenZWave::Options::Get()->Lock();
	OpenZWave::Manager::Create();
	OpenZWave::Manager::Get()->AddWatcher( OnNotification, NULL );
	OpenZWave::Manager::Get()->AddDriver( port );		
	OpenZWave::Manager::Get()->RemoveDriver(port);
	OpenZWave::Manager::Get()->RemoveWatcher(OnNotification, NULL);
	OpenZWave::Manager::Destroy();
	OpenZWave::Options::Destroy();

	return 0;
}
