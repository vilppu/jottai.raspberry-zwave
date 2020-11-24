#include "Defs.h"
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

State OnValueAdded(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnValueRemoved(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnValueChanged(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnValueRefreshed(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnGroup(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnNodeNew(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnNodeAdded(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnNodeRemoved(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnNodeProtocolInfo(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnNodeNaming(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnNodeEvent(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnPollingDisabled(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnPollingEnabled(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnSceneEvent(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnCreateButton(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnDeleteButton(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnButtonOn(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnButtonOff(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnDriverReady(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnDriverFailed(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnDriverReset(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnEssentialNodeQueriesComplete(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnNodeQueriesComplete(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnAwakeNodesQueried(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnAllNodesQueriedSomeDead(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnAllNodesQueried(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnNotification(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnDriverRemoved(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnControllerCommand(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnNodeReset(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnUserAlerts(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State OnManufacturerSpecificDBReady(OpenZWave::Notification const& notification, State state)
{
	return state;
}

State UpdateState(OpenZWave::Notification const& notification, State state)
{
	switch(notification.GetType() )
	{
		case OpenZWave::Notification::Type_ValueAdded: return OnValueAdded(notification, state);
        case OpenZWave::Notification::Type_ValueRemoved: return OnValueRemoved(notification, state);
        case OpenZWave::Notification::Type_ValueChanged: return OnValueChanged(notification, state);
        case OpenZWave::Notification::Type_ValueRefreshed: return OnValueRefreshed(notification, state);
        case OpenZWave::Notification::Type_Group: return OnGroup(notification, state);
        case OpenZWave::Notification::Type_NodeNew: return OnNodeNew(notification, state);
        case OpenZWave::Notification::Type_NodeAdded: return OnNodeAdded(notification, state);
        case OpenZWave::Notification::Type_NodeRemoved: return OnNodeRemoved(notification, state);
        case OpenZWave::Notification::Type_NodeProtocolInfo: return OnNodeProtocolInfo(notification, state);
        case OpenZWave::Notification::Type_NodeNaming: return OnNodeNaming(notification, state);
        case OpenZWave::Notification::Type_NodeEvent: return OnNodeEvent(notification, state);
        case OpenZWave::Notification::Type_PollingDisabled: return OnPollingDisabled(notification, state);
        case OpenZWave::Notification::Type_PollingEnabled: return OnPollingEnabled(notification, state);
        case OpenZWave::Notification::Type_SceneEvent: return OnSceneEvent(notification, state);
        case OpenZWave::Notification::Type_CreateButton: return OnCreateButton(notification, state);
        case OpenZWave::Notification::Type_DeleteButton: return OnDeleteButton(notification, state);
        case OpenZWave::Notification::Type_ButtonOn: return OnButtonOn(notification, state);
        case OpenZWave::Notification::Type_ButtonOff: return OnButtonOff(notification, state);
        case OpenZWave::Notification::Type_DriverReady: return OnDriverReady(notification, state);
        case OpenZWave::Notification::Type_DriverFailed: return OnDriverFailed(notification, state);
        case OpenZWave::Notification::Type_DriverReset: return OnDriverReset(notification, state);
        case OpenZWave::Notification::Type_EssentialNodeQueriesComplete: return OnEssentialNodeQueriesComplete(notification, state);
        case OpenZWave::Notification::Type_NodeQueriesComplete: return OnNodeQueriesComplete(notification, state);
        case OpenZWave::Notification::Type_AwakeNodesQueried: return OnAwakeNodesQueried(notification, state);
        case OpenZWave::Notification::Type_AllNodesQueriedSomeDead: return OnAllNodesQueriedSomeDead(notification, state);
        case OpenZWave::Notification::Type_AllNodesQueried: return OnAllNodesQueried(notification, state);
        case OpenZWave::Notification::Type_Notification: return OnNotification(notification, state);
        case OpenZWave::Notification::Type_DriverRemoved: return OnDriverRemoved(notification, state);
        case OpenZWave::Notification::Type_ControllerCommand: return OnControllerCommand(notification, state);
        case OpenZWave::Notification::Type_NodeReset: return OnNodeReset(notification, state);
        case OpenZWave::Notification::Type_UserAlerts: return OnUserAlerts(notification, state);
        case OpenZWave::Notification::Type_ManufacturerSpecificDBReady: return OnManufacturerSpecificDBReady(notification, state);
		default: return state;
	}
}

State UpdateState(OpenZWave::Notification const* notification, State currentState)
{
	return UpdateState(*notification, currentState);
}

void EnqueuePostState(State state)
{	
}

void OnNotification(OpenZWave::Notification const* notification, StateHolder* stateHolder)
{
	auto stateProvider = [notification, stateHolder]()
		{
			return UpdateState(*notification, *stateHolder->state);
		};

	EnqueuePostState(SetState(*stateHolder, stateProvider));
}

void OnNotification(OpenZWave::Notification const* notification, void* context)
{
	OnNotification(notification, static_cast<StateHolder*>(context));
}
