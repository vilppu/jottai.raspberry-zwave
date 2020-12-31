#pragma once
#include "dependencies.cpp"

void LogNotification(const std::string message, OpenZWave::Notification const &notification)
{
}

void LogNode(const std::string message, OpenZWave::Notification const &notification)
{
	std::cout << "-- " << message << " " << (int)notification.GetNodeId() << " --" << std::endl;
}

void LogNodeValue(const std::string message, OpenZWave::Notification const &notification)
{
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

	State OnValueAdded(OpenZWave::Notification const &notification)
	{
		LogNodeValue("OnValueAdded", notification);

		const auto newState = Reduce(notification, *state);
		const auto homeId = notification.GetHomeId();
		const auto gatewayId = std::to_string(homeId);
		const auto sensorData = ToSensorData(notification);

		agent.SendDeviceData(gatewayId, sensorData);

		return newState;
	}

	State OnValueRemoved(OpenZWave::Notification const &notification)
	{
		LogNodeValue("OnValueRemoved", notification);

		auto newState = Reduce(notification, *state);

		return newState;
	}

	State OnValueChanged(OpenZWave::Notification const &notification)
	{
		LogNodeValue("OnValueChanged", notification);

		const auto newState = Reduce(notification, *state);
		const auto homeId = notification.GetHomeId();
		const auto gatewayId = std::to_string(homeId);
		const auto sensorData = ToSensorData(notification);

		agent.SendDeviceData(gatewayId, sensorData);

		return newState;
	}

	State OnValueRefreshed(OpenZWave::Notification const &notification)
	{
		LogNodeValue("OnValueRefreshed", notification);

		const auto newState = Reduce(notification, *state);
		const auto homeId = notification.GetHomeId();
		const auto gatewayId = std::to_string(homeId);
		const auto sensorData = ToSensorData(notification);

		agent.SendDeviceData(gatewayId, sensorData);

		return newState;
	}

	State OnGroup(OpenZWave::Notification const &notification)
	{
		LogNotification("OnGroup", notification);

		auto newState = Reduce(notification, *state);

		return newState;
	}

	State OnNodeNew(OpenZWave::Notification const &notification)
	{
		LogNotification("OnNodeNew", notification);

		auto newState = Reduce(notification, *state);

		return newState;
	}

	State OnNodeAdded(OpenZWave::Notification const &notification)
	{
		LogNode("OnNodeAdded", notification);

		auto newState = Reduce(notification, *state);

		return newState;
	}

	State OnNodeRemoved(OpenZWave::Notification const &notification)
	{
		LogNotification("OnNodeRemoved", notification);

		auto newState = Reduce(notification, *state);

		return newState;
	}

	State OnNodeProtocolInfo(OpenZWave::Notification const &notification)
	{
		LogNotification("OnNodeProtocolInfo", notification);

		auto newState = Reduce(notification, *state);

		return newState;
	}

	State OnNodeNaming(OpenZWave::Notification const &notification)
	{
		LogNotification("OnNodeNaming", notification);

		auto newState = Reduce(notification, *state);

		return newState;
	}

	State OnNodeEvent(OpenZWave::Notification const &notification)
	{
		LogNotification("OnNodeEvent", notification);

		auto newState = Reduce(notification, *state);

		return newState;
	}

	State OnPollingDisabled(OpenZWave::Notification const &notification)
	{
		LogNotification("OnPollingDisabled", notification);

		auto newState = Reduce(notification, *state);

		return newState;
	}

	State OnPollingEnabled(OpenZWave::Notification const &notification)
	{
		LogNotification("OnPollingEnabled", notification);

		auto newState = Reduce(notification, *state);

		return newState;
	}

	State OnSceneEvent(OpenZWave::Notification const &notification)
	{
		LogNotification("OnSceneEvent", notification);

		auto newState = Reduce(notification, *state);

		return newState;
	}

	State OnCreateButton(OpenZWave::Notification const &notification)
	{
		LogNotification("OnCreateButton", notification);

		auto newState = Reduce(notification, *state);

		return newState;
	}

	State OnDeleteButton(OpenZWave::Notification const &notification)
	{
		LogNotification("OnDeleteButton", notification);

		auto newState = Reduce(notification, *state);

		return newState;
	}

	State OnButtonOn(OpenZWave::Notification const &notification)
	{
		LogNotification("OnButtonOn", notification);

		auto newState = Reduce(notification, *state);

		return newState;
	}

	State OnButtonOff(OpenZWave::Notification const &notification)
	{
		LogNotification("OnButtonOff", notification);

		auto newState = Reduce(notification, *state);

		return newState;
	}

	State OnDriverReady(OpenZWave::Notification const &notification)
	{
		LogNotification("OnDriverReady", notification);

		auto newState = Reduce(notification, *state);

		return newState;
	}

	State OnDriverFailed(OpenZWave::Notification const &notification)
	{
		LogNotification("OnDriverFailed", notification);

		auto newState = Reduce(notification, *state);

		initializationWaiter.notify_one();

		return newState;
	}

	State OnDriverReset(OpenZWave::Notification const &notification)
	{
		LogNotification("OnDriverReset", notification);

		auto newState = Reduce(notification, *state);

		return newState;
	}

	State OnEssentialNodeQueriesComplete(OpenZWave::Notification const &notification)
	{
		LogNotification("OnEssentialNodeQueriesComplete", notification);

		auto newState = Reduce(notification, *state);

		return newState;
	}

	State OnNodeQueriesComplete(OpenZWave::Notification const &notification)
	{
		LogNotification("OnNodeQueriesComplete", notification);

		auto newState = Reduce(notification, *state);

		return newState;
	}

	State OnAwakeNodesQueried(OpenZWave::Notification const &notification)
	{
		LogNotification("OnAwakeNodesQueried", notification);

		auto newState = Reduce(notification, *state);

		return newState;
	}

	State OnAllNodesQueriedSomeDead(OpenZWave::Notification const &notification)
	{
		LogNotification("OnAllNodesQueriedSomeDead", notification);

		auto newState = Reduce(notification, *state);

		initializationWaiter.notify_one();

		return newState;
	}

	State OnAllNodesQueried(OpenZWave::Notification const &notification)
	{
		LogNotification("OnAllNodesQueried", notification);

		auto newState = Reduce(notification, *state);

		initializationWaiter.notify_one();

		return newState;
	}

	State OnNotification(OpenZWave::Notification const &notification)
	{
		LogNotification("OnNotification", notification);

		auto newState = Reduce(notification, *state);

		return newState;
	}

	State OnDriverRemoved(OpenZWave::Notification const &notification)
	{
		LogNotification("OnDriverRemoved", notification);

		auto newState = Reduce(notification, *state);

		return newState;
	}

	State OnControllerCommand(OpenZWave::Notification const &notification)
	{
		LogNotification("OnControllerCommand", notification);

		auto newState = Reduce(notification, *state);

		return newState;
	}

	State OnNodeReset(OpenZWave::Notification const &notification)
	{
		LogNotification("OnNodeReset", notification);

		auto newState = Reduce(notification, *state);

		return newState;
	}

	State OnUserAlerts(OpenZWave::Notification const &notification)
	{
		LogNotification("OnUserAlerts", notification);

		auto newState = Reduce(notification, *state);

		return newState;
	}

	State OnManufacturerSpecificDBReady(OpenZWave::Notification const &notification)
	{
		LogNotification("OnManufacturerSpecificDBReady", notification);

		auto newState = Reduce(notification, *state);

		return newState;
	}

	State Handle(OpenZWave::Notification const &notification)
	{
		switch (notification.GetType())
		{
		case OpenZWave::Notification::Type_ValueAdded:
			return OnValueAdded(notification);
		case OpenZWave::Notification::Type_ValueRemoved:
			return OnValueRemoved(notification);
		case OpenZWave::Notification::Type_ValueChanged:
			return OnValueChanged(notification);
		case OpenZWave::Notification::Type_ValueRefreshed:
			return OnValueRefreshed(notification);
		case OpenZWave::Notification::Type_Group:
			return OnGroup(notification);
		case OpenZWave::Notification::Type_NodeNew:
			return OnNodeNew(notification);
		case OpenZWave::Notification::Type_NodeAdded:
			return OnNodeAdded(notification);
		case OpenZWave::Notification::Type_NodeRemoved:
			return OnNodeRemoved(notification);
		case OpenZWave::Notification::Type_NodeProtocolInfo:
			return OnNodeProtocolInfo(notification);
		case OpenZWave::Notification::Type_NodeNaming:
			return OnNodeNaming(notification);
		case OpenZWave::Notification::Type_NodeEvent:
			return OnNodeEvent(notification);
		case OpenZWave::Notification::Type_PollingDisabled:
			return OnPollingDisabled(notification);
		case OpenZWave::Notification::Type_PollingEnabled:
			return OnPollingEnabled(notification);
		case OpenZWave::Notification::Type_SceneEvent:
			return OnSceneEvent(notification);
		case OpenZWave::Notification::Type_CreateButton:
			return OnCreateButton(notification);
		case OpenZWave::Notification::Type_DeleteButton:
			return OnDeleteButton(notification);
		case OpenZWave::Notification::Type_ButtonOn:
			return OnButtonOn(notification);
		case OpenZWave::Notification::Type_ButtonOff:
			return OnButtonOff(notification);
		case OpenZWave::Notification::Type_DriverReady:
			return OnDriverReady(notification);
		case OpenZWave::Notification::Type_DriverFailed:
			return OnDriverFailed(notification);
		case OpenZWave::Notification::Type_DriverReset:
			return OnDriverReset(notification);
		case OpenZWave::Notification::Type_EssentialNodeQueriesComplete:
			return OnEssentialNodeQueriesComplete(notification);
		case OpenZWave::Notification::Type_NodeQueriesComplete:
			return OnNodeQueriesComplete(notification);
		case OpenZWave::Notification::Type_AwakeNodesQueried:
			return OnAwakeNodesQueried(notification);
		case OpenZWave::Notification::Type_AllNodesQueriedSomeDead:
			return OnAllNodesQueriedSomeDead(notification);
		case OpenZWave::Notification::Type_AllNodesQueried:
			return OnAllNodesQueried(notification);
		case OpenZWave::Notification::Type_Notification:
			return OnNotification(notification);
		case OpenZWave::Notification::Type_DriverRemoved:
			return OnDriverRemoved(notification);
		case OpenZWave::Notification::Type_ControllerCommand:
			return OnControllerCommand(notification);
		case OpenZWave::Notification::Type_NodeReset:
			return OnNodeReset(notification);
		case OpenZWave::Notification::Type_UserAlerts:
			return OnUserAlerts(notification);
		case OpenZWave::Notification::Type_ManufacturerSpecificDBReady:
			return OnManufacturerSpecificDBReady(notification);
		default:
			return *state;
		}
	}

	void HandleAndSetState(OpenZWave::Notification const &notification)
	{
		std::scoped_lock lock(mutex);

		auto newState = Handle(notification);

		state = std::make_unique<State>(newState);
	}

	static void Handle(OpenZWave::Notification const *notification, void *context)
	{
		auto handler = static_cast<Handler *>(context);

		handler->HandleAndSetState(*notification);
	}

	static void HandleDevicePropertyChangeRequest(Handler *self)
	{
		std::cout << "Handling device property change requests" << std::endl;

		while (!exiting)
		{
			auto devicePropertyChangeRequest = self->agent.GetDevicePropertyChangeRequest();

			if (devicePropertyChangeRequest.isRequested)
			{
				std::scoped_lock lock(self->mutex);

				const auto homeId = std::stoul(devicePropertyChangeRequest.gatewayId);
				const auto nodeId = std::stoul(devicePropertyChangeRequest.deviceId);
				const auto id = std::stoull(devicePropertyChangeRequest.propertyId);
				const auto valueId = self->state->GetValueId(homeId, nodeId, id);
				const auto on = devicePropertyChangeRequest.propertyValue == "True";

				std::cout << "Changin device property " << devicePropertyChangeRequest.propertyId
						  << " to " << devicePropertyChangeRequest.propertyValue
						  << std::endl;

				OpenZWave::Manager::Get()->SetValue(valueId, on);
			}
			else
			{
				std::cout << "No requests" << std::endl;
			}
		}
	}
};
