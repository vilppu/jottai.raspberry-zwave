#pragma once
#include "dependencies.cpp"

State ReduceValueAdded(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReduceValueRemoved(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReduceValueChanged(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReduceValueRefreshed(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReduceGroup(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReduceNodeNew(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReduceNodeAdded(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReduceNodeRemoved(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReduceNodeProtocolInfo(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReduceNodeNaming(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReduceNodeEvent(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReducePollingDisabled(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReducePollingEnabled(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReduceSceneEvent(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReduceCreateButton(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReduceDeleteButton(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReduceButtonOn(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReduceButtonOff(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReduceDriverReady(OpenZWave::Notification const& notification, const State state)
{
	const auto homeId = notification.GetHomeId();
	const auto newHome = Home::Empty(homeId);
	const auto updatedState = state.AddOrReplaceHome(newHome);
	
	return updatedState;
}

State ReduceDriverFailed(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReduceDriverReset(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReduceEssentialNodeQueriesComplete(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReduceNodeQueriesComplete(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReduceAwakeNodesQueried(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReduceAllNodesQueriedSomeDead(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReduceAllNodesQueried(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReduceNotification(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReduceDriverRemoved(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReduceControllerCommand(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReduceNodeReset(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReduceUserAlerts(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State ReduceManufacturerSpecificDBReady(OpenZWave::Notification const& notification, const State state)
{
	return state;
}

State Reduce(OpenZWave::Notification const& notification, const State state)
{
	switch(notification.GetType())
	{
		case OpenZWave::Notification::Type_ValueAdded: return ReduceValueAdded(notification, state);
		case OpenZWave::Notification::Type_ValueRemoved: return ReduceValueRemoved(notification, state);
		case OpenZWave::Notification::Type_ValueChanged: return ReduceValueChanged(notification, state);
		case OpenZWave::Notification::Type_ValueRefreshed: return ReduceValueRefreshed(notification, state);
		case OpenZWave::Notification::Type_Group: return ReduceGroup(notification, state);
		case OpenZWave::Notification::Type_NodeNew: return ReduceNodeNew(notification, state);
		case OpenZWave::Notification::Type_NodeAdded: return ReduceNodeAdded(notification, state);
		case OpenZWave::Notification::Type_NodeRemoved: return ReduceNodeRemoved(notification, state);
		case OpenZWave::Notification::Type_NodeProtocolInfo: return ReduceNodeProtocolInfo(notification, state);
		case OpenZWave::Notification::Type_NodeNaming: return ReduceNodeNaming(notification, state);
		case OpenZWave::Notification::Type_NodeEvent: return ReduceNodeEvent(notification, state);
		case OpenZWave::Notification::Type_PollingDisabled: return ReducePollingDisabled(notification, state);
		case OpenZWave::Notification::Type_PollingEnabled: return ReducePollingEnabled(notification, state);
		case OpenZWave::Notification::Type_SceneEvent: return ReduceSceneEvent(notification, state);
		case OpenZWave::Notification::Type_CreateButton: return ReduceCreateButton(notification, state);
		case OpenZWave::Notification::Type_DeleteButton: return ReduceDeleteButton(notification, state);
		case OpenZWave::Notification::Type_ButtonOn: return ReduceButtonOn(notification, state);
		case OpenZWave::Notification::Type_ButtonOff: return ReduceButtonOff(notification, state);
		case OpenZWave::Notification::Type_DriverReady: return ReduceDriverReady(notification, state);
		case OpenZWave::Notification::Type_DriverFailed: return ReduceDriverFailed(notification, state);
		case OpenZWave::Notification::Type_DriverReset: return ReduceDriverReset(notification, state);
		case OpenZWave::Notification::Type_EssentialNodeQueriesComplete: return ReduceEssentialNodeQueriesComplete(notification, state);
		case OpenZWave::Notification::Type_NodeQueriesComplete: return ReduceNodeQueriesComplete(notification, state);
		case OpenZWave::Notification::Type_AwakeNodesQueried: return ReduceAwakeNodesQueried(notification, state);
		case OpenZWave::Notification::Type_AllNodesQueriedSomeDead: return ReduceAllNodesQueriedSomeDead(notification, state);
		case OpenZWave::Notification::Type_AllNodesQueried: return ReduceAllNodesQueried(notification, state);
		case OpenZWave::Notification::Type_Notification: return ReduceNotification(notification, state);
		case OpenZWave::Notification::Type_DriverRemoved: return ReduceDriverRemoved(notification, state);
		case OpenZWave::Notification::Type_ControllerCommand: return ReduceControllerCommand(notification, state);
		case OpenZWave::Notification::Type_NodeReset: return ReduceNodeReset(notification, state);
		case OpenZWave::Notification::Type_UserAlerts: return ReduceUserAlerts(notification, state);
		case OpenZWave::Notification::Type_ManufacturerSpecificDBReady: return ReduceManufacturerSpecificDBReady(notification, state);
		default: return state;
	}
}
