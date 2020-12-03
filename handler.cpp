#pragma once
#include "dependencies.cpp"

void Log(const std::string message, OpenZWave::Notification const& notification)
{
	std::cout<<"Home "<<notification.GetHomeId()<<":"<<message<<std::endl;
}

struct Handler
{
	Agent agent;
	std::mutex mutex;
	std::mutex initializationWaiterMutex;
	std::condition_variable initializationWaiter;
	std::unique_ptr<State> state = std::make_unique<State>();

	void WaitUntilInitializationHandled()
	{
		std::unique_lock initializationWaiterLock(initializationWaiterMutex);

		initializationWaiter.wait(initializationWaiterLock);
	}

	State OnValueAdded(OpenZWave::Notification const& notification)
	{
		Log("OnValueAdded", notification);

		auto newState = ReduceValueAdded(notification, *state);

		return newState;
	}

	State OnValueRemoved(OpenZWave::Notification const& notification)
	{
		Log("OnValueRemoved", notification);
		
		auto newState = ReduceValueRemoved(notification, *state);

		return newState;
	}

	State OnValueChanged(OpenZWave::Notification const& notification)
	{
		Log("OnValueChanged", notification);
		
		auto newState = ReduceValueChanged(notification, *state);

		return newState;
	}

	State OnValueRefreshed(OpenZWave::Notification const& notification)
	{
		Log("OnValueRefreshed", notification);
		
		auto newState = ReduceValueRefreshed(notification, *state);

		return newState;
	}

	State OnGroup(OpenZWave::Notification const& notification)
	{
		Log("OnGroup", notification);
		
		auto newState = ReduceGroup(notification, *state);

		return newState;
	}

	State OnNodeNew(OpenZWave::Notification const& notification)
	{
		Log("OnNodeNew", notification);
		
		auto newState = ReduceNodeNew(notification, *state);

		return newState;
	}

	State OnNodeAdded(OpenZWave::Notification const& notification)
	{
		Log("OnNodeAdded", notification);
		
		auto newState = ReduceNodeAdded(notification, *state);

		return newState;
	}

	State OnNodeRemoved(OpenZWave::Notification const& notification)
	{
		Log("OnNodeRemoved", notification);
		
		auto newState = ReduceNodeRemoved(notification, *state);

		return newState;
	}

	State OnNodeProtocolInfo(OpenZWave::Notification const& notification)
	{
		Log("OnNodeProtocolInfo", notification);
		
		auto newState = ReduceNodeProtocolInfo(notification, *state);

		return newState;
	}

	State OnNodeNaming(OpenZWave::Notification const& notification)
	{
		Log("OnNodeNaming", notification);
		
		auto newState = ReduceNodeNaming(notification, *state);

		return newState;
	}

	State OnNodeEvent(OpenZWave::Notification const& notification)
	{
		Log("OnNodeEvent", notification);
		
		auto newState = ReduceNodeEvent(notification, *state);

		return newState;
	}

	State OnPollingDisabled(OpenZWave::Notification const& notification)
	{
		Log("OnPollingDisabled", notification);
		
		auto newState = ReducePollingDisabled(notification, *state);

		return newState;
	}

	State OnPollingEnabled(OpenZWave::Notification const& notification)
	{
		Log("OnPollingEnabled", notification);
		
		auto newState = ReducePollingEnabled(notification, *state);

		return newState;
	}

	State OnSceneEvent(OpenZWave::Notification const& notification)
	{
		Log("OnSceneEvent", notification);
		
		auto newState = ReduceSceneEvent(notification, *state);

		return newState;
	}

	State OnCreateButton(OpenZWave::Notification const& notification)
	{
		Log("OnCreateButton", notification);
		
		auto newState = ReduceCreateButton(notification, *state);

		return newState;
	}

	State OnDeleteButton(OpenZWave::Notification const& notification)
	{
		Log("OnDeleteButton", notification);
		
		auto newState = ReduceDeleteButton(notification, *state);

		return newState;
	}

	State OnButtonOn(OpenZWave::Notification const& notification)
	{
		Log("OnButtonOn", notification);
		
		auto newState = ReduceButtonOn(notification, *state);

		return newState;
	}

	State OnButtonOff(OpenZWave::Notification const& notification)
	{
		Log("OnButtonOff", notification);
		
		auto newState = ReduceButtonOff(notification, *state);

		return newState;
	}

	State OnDriverReady(OpenZWave::Notification const& notification)
	{
		Log("OnDriverReady", notification);
		
		const auto newState = ReduceDriverReady(notification, *state);
		const auto homeId = notification.GetHomeId();
		const auto home = newState.homes.find(homeId)->second;
		const auto gatewayId = std::to_string(homeId);
		
		agent.SendGatewayActiveEvent(gatewayId);

		return newState;
	}

	State OnDriverFailed(OpenZWave::Notification const& notification)
	{
		Log("OnDriverFailed", notification);
		
		auto newState = ReduceDriverFailed(notification, *state);

		initializationWaiter.notify_one();

		return newState;
	}

	State OnDriverReset(OpenZWave::Notification const& notification)
	{
		Log("OnDriverReset", notification);
		
		auto newState = ReduceDriverReset(notification, *state);

		return newState;
	}

	State OnEssentialNodeQueriesComplete(OpenZWave::Notification const& notification)
	{
		Log("OnEssentialNodeQueriesComplete", notification);
		
		auto newState = ReduceEssentialNodeQueriesComplete(notification, *state);

		return newState;
	}

	State OnNodeQueriesComplete(OpenZWave::Notification const& notification)
	{
		Log("OnNodeQueriesComplete", notification);
		
		auto newState = ReduceValueAdded(notification, *state);

		return newState;
	}

	State OnAwakeNodesQueried(OpenZWave::Notification const& notification)
	{
		Log("OnAwakeNodesQueried", notification);
		
		auto newState = ReduceAwakeNodesQueried(notification, *state);

		return newState;
	}

	State OnAllNodesQueriedSomeDead(OpenZWave::Notification const& notification)
	{
		Log("OnAllNodesQueriedSomeDead", notification);
		
		auto newState = ReduceAllNodesQueriedSomeDead(notification, *state);

		initializationWaiter.notify_one();

		return newState;
	}

	State OnAllNodesQueried(OpenZWave::Notification const& notification)
	{
		Log("OnAllNodesQueried", notification);
		
		auto newState = ReduceAllNodesQueried(notification, *state);

		initializationWaiter.notify_one();

		return newState;
	}

	State OnNotification(OpenZWave::Notification const& notification)
	{
		Log("OnNotification", notification);
		
		auto newState = ReduceNotification(notification, *state);

		return newState;
	}

	State OnDriverRemoved(OpenZWave::Notification const& notification)
	{
		Log("OnDriverRemoved", notification);
		
		auto newState = ReduceDriverRemoved(notification, *state);

		return newState;
	}

	State OnControllerCommand(OpenZWave::Notification const& notification)
	{
		Log("OnControllerCommand", notification);
		
		auto newState = ReduceControllerCommand(notification, *state);

		return newState;
	}

	State OnNodeReset(OpenZWave::Notification const& notification)
	{
		Log("OnNodeReset", notification);
		
		auto newState = ReduceNodeReset(notification, *state);

		return newState;
	}

	State OnUserAlerts(OpenZWave::Notification const& notification)
	{
		Log("OnUserAlerts", notification);
		
		auto newState = ReduceUserAlerts(notification, *state);

		return newState;
	}

	State OnManufacturerSpecificDBReady(OpenZWave::Notification const& notification)
	{
		Log("OnManufacturerSpecificDBReady", notification);
		
		auto newState = ReduceManufacturerSpecificDBReady(notification, *state);

		return newState;
	}

	State Handle(OpenZWave::Notification const& notification)
	{
		std::cout<<"Notification: "<<notification.GetType()<<std::endl;

		switch(notification.GetType())
		{
			case OpenZWave::Notification::Type_ValueAdded: return OnValueAdded(notification);
			case OpenZWave::Notification::Type_ValueRemoved: return OnValueRemoved(notification);
			case OpenZWave::Notification::Type_ValueChanged: return OnValueChanged(notification);
			case OpenZWave::Notification::Type_ValueRefreshed: return OnValueRefreshed(notification);
			case OpenZWave::Notification::Type_Group: return OnGroup(notification);
			case OpenZWave::Notification::Type_NodeNew: return OnNodeNew(notification);
			case OpenZWave::Notification::Type_NodeAdded: return OnNodeAdded(notification);
			case OpenZWave::Notification::Type_NodeRemoved: return OnNodeRemoved(notification);
			case OpenZWave::Notification::Type_NodeProtocolInfo: return OnNodeProtocolInfo(notification);
			case OpenZWave::Notification::Type_NodeNaming: return OnNodeNaming(notification);
			case OpenZWave::Notification::Type_NodeEvent: return OnNodeEvent(notification);
			case OpenZWave::Notification::Type_PollingDisabled: return OnPollingDisabled(notification);
			case OpenZWave::Notification::Type_PollingEnabled: return OnPollingEnabled(notification);
			case OpenZWave::Notification::Type_SceneEvent: return OnSceneEvent(notification);
			case OpenZWave::Notification::Type_CreateButton: return OnCreateButton(notification);
			case OpenZWave::Notification::Type_DeleteButton: return OnDeleteButton(notification);
			case OpenZWave::Notification::Type_ButtonOn: return OnButtonOn(notification);
			case OpenZWave::Notification::Type_ButtonOff: return OnButtonOff(notification);
			case OpenZWave::Notification::Type_DriverReady: return OnDriverReady(notification);
			case OpenZWave::Notification::Type_DriverFailed: return OnDriverFailed(notification);
			case OpenZWave::Notification::Type_DriverReset: return OnDriverReset(notification);
			case OpenZWave::Notification::Type_EssentialNodeQueriesComplete: return OnEssentialNodeQueriesComplete(notification);
			case OpenZWave::Notification::Type_NodeQueriesComplete: return OnNodeQueriesComplete(notification);
			case OpenZWave::Notification::Type_AwakeNodesQueried: return OnAwakeNodesQueried(notification);
			case OpenZWave::Notification::Type_AllNodesQueriedSomeDead: return OnAllNodesQueriedSomeDead(notification);
			case OpenZWave::Notification::Type_AllNodesQueried: return OnAllNodesQueried(notification);
			case OpenZWave::Notification::Type_Notification: return OnNotification(notification);
			case OpenZWave::Notification::Type_DriverRemoved: return OnDriverRemoved(notification);
			case OpenZWave::Notification::Type_ControllerCommand: return OnControllerCommand(notification);
			case OpenZWave::Notification::Type_NodeReset: return OnNodeReset(notification);
			case OpenZWave::Notification::Type_UserAlerts: return OnUserAlerts(notification);
			case OpenZWave::Notification::Type_ManufacturerSpecificDBReady: return OnManufacturerSpecificDBReady(notification);
			default: return *state;
		}
	}

	void HandleAndSetState(OpenZWave::Notification const& notification)
	{
		std::scoped_lock lock(mutex);

		auto newState = Handle(notification);

		state = std::make_unique<State>(newState);
	}

	static void Handle(OpenZWave::Notification const* notification, void* context)
	{
		auto handler = static_cast<Handler*>(context);

		handler->HandleAndSetState(*notification);
	}
};
