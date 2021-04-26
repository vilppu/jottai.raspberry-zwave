#pragma once
#include "dependencies.cpp"

std::string CurrentTime()
{
	time_t currentTime;
	time(&currentTime);

	char currentTimeBuffer[sizeof "0000-00-00T00:00:00Z"];
	strftime(currentTimeBuffer, sizeof currentTimeBuffer, "%FT%TZ", gmtime(&currentTime));

	return std::string(currentTimeBuffer);
}

const std::string GetPropertyType(const int commandClassId, const std::string& valueUnits)
{
	// http://www.openzwave.com/dev/group__CommandClass.html
	switch (commandClassId)
	{
	case 0x71:
		return "NotSpecified"; // Alarm COMMAND_CLASS_NOTIFICATION
	case 0x22:
		return "NotSpecified"; // ApplicationStatus COMMAND_CLASS_APPLICATION_STATUS
	case 0x85:
		return "NotSpecified"; // Association COMMAND_CLASS_ASSOCIATION
	case 0x9b:
		return "NotSpecified"; // AssociationCommandConfiguration COMMAND_CLASS_ASSOCIATION_COMMAND_CONFIGURATION
	case 0x66:
		return "NotSpecified"; // BarrierOperator COMMAND_CLASS_BARRIER_OPERATOR
	case 0x20:
		return "NotSpecified"; // Basic COMMAND_CLASS_BASIC
	case 0x50:
		return "NotSpecified"; // BasicWindowCovering COMMAND_CLASS_BASIC_WINDOW_COVERING
	case 0x80:
		return "NotSpecified"; // Battery COMMAND_CLASS_BATTERY
	case 0x5B:
		return "NotSpecified"; // CentralScene COMMAND_CLASS_CENTRAL_SCENE
	case 0x46:
		return "NotSpecified"; // ClimateControlSchedule COMMAND_CLASS_CLIMATE_CONTROL_SCHEDULE
	case 0x81:
		return "NotSpecified"; // Clock COMMAND_CLASS_CLOCK
	case 0x33:
		return "NotSpecified"; // Color COMMAND_CLASS_COLOR
	case 0x70:
		return "NotSpecified"; // Configuration COMMAND_CLASS_CONFIGURATION
	case 0x21:
		return "NotSpecified"; // ControllerReplication COMMAND_CLASS_CONTROLLER_REPLICATION
	case 0x56:
		return "NotSpecified"; // CRC16Encap COMMAND_CLASS_CRC_16_ENCAP
	case 0x5a:
		return "NotSpecified"; // DeviceResetLocally COMMAND_CLASS_DEVICE_RESET_LOCALLY
	case 0x62:
		return "NotSpecified"; // DoorLock COMMAND_CLASS_DOOR_LOCK
	case 0x4C:
		return "NotSpecified"; // DoorLockLogging COMMAND_CLASS_DOOR_LOCK_LOGGING
	case 0x90:
		return "NotSpecified"; // EnergyProduction COMMAND_CLASS_ENERGY_PRODUCTION
	case 0x82:
		return "NotSpecified"; // Hail COMMAND_CLASS_HAIL
	case 0x87:
		return "NotSpecified"; // Indicator COMMAND_CLASS_INDICATOR
	case 0x89:
		return "NotSpecified"; // Language COMMAND_CLASS_LANGUAGE
	case 0x76:
		return "NotSpecified"; // Lock COMMAND_CLASS_LOCK
	case 0x91:
		return "NotSpecified"; // ManufacturerProprietary COMMAND_CLASS_PROPRIETARY
	case 0x72:
		return "NotSpecified"; // ManufacturerSpecific COMMAND_CLASS_MANUFACTURER_SPECIFIC
	case 0x32:
		return "NotSpecified"; // Meter COMMAND_CLASS_METER
	case 0x35:
		return "NotSpecified"; // MeterPulse COMMAND_CLASS_METER_PULSE
	case 0x8E:
		return "NotSpecified"; // MultiChannelAssociation COMMAND_CLASS_MULTI_CHANNEL_ASSOCIATION
	case 0x8f:
		return "NotSpecified"; // MultiCmd COMMAND_CLASS_MULTI_CMD
	case 0x60:
		return "NotSpecified"; // MultiInstance COMMAND_CLASS_MULTI_INSTANCE
	case 0x77:
		return "NotSpecified"; // NodeNaming COMMAND_CLASS_NODE_NAMING
	case 0x00:
		return "NotSpecified"; // NoOperation COMMAND_CLASS_NO_OPERATION
	case 0x73:
		return "NotSpecified"; // Powerlevel COMMAND_CLASS_POWERLEVEL
	case 0x88:
		return "NotSpecified"; // Proprietary COMMAND_CLASS_PROPRIETARY
	case 0x75:
		return "NotSpecified"; // Protection COMMAND_CLASS_PROTECTION
	case 0x2B:
		return "NotSpecified"; // SceneActivation COMMAND_CLASS_SCENEACTIVATION
	case 0x98:
		return "NotSpecified"; // Security COMMAND_CLASS_SECURITY
	case 0x9c:
		return "NotSpecified"; // SensorAlarm COMMAND_CLASS_SENSOR_ALARM
	case 0x30:
		return "NotSpecified"; // SensorBinary COMMAND_CLASS_SENSOR_BINARY
	case 0x31:
		if(valueUnits == "C")
		{
			return "Temperature";
		}
		else if(valueUnits == "MM")
		{
			return "SeismicIntensity";
		}
		else if(valueUnits == "Lux")
		{
			return "Luminance";
		}
		return "NotSpecified"; // SensorMultilevel COMMAND_CLASS_SENSOR_MULTILEVEL
	case 0x79:
		return "NotSpecified"; // SoundSwitch COMMAND_CLASS_SOUND_SWITCH
	case 0x27:
		return "NotSpecified"; // SwitchAll COMMAND_CLASS_SWITCH_ALL
	case 0x25:
		return "TwoWaySwitch"; // SwitchBinary COMMAND_CLASS_SWITCH_BINARY
	case 0x26:
		return "NotSpecified"; // SwitchMultilevel COMMAND_CLASS_SWITCH_MULTILEVEL
	case 0x28:
		return "NotSpecified"; // SwitchToggleBinary COMMAND_CLASS_SWITCH_TOGGLE_BINARY
	case 0x29:
		return "NotSpecified"; // SwitchToggleMultilevel COMMAND_CLASS_SWITCH_TOGGLE_MULTILEVEL
	case 0x44:
		return "NotSpecified"; // ThermostatFanMode COMMAND_CLASS_THERMOSTAT_FAN_MODE
	case 0x45:
		return "NotSpecified"; // ThermostatFanState COMMAND_CLASS_THERMOSTAT_FAN_STATE
	case 0x40:
		return "NotSpecified"; // ThermostatMode COMMAND_CLASS_THERMOSTAT_MODE
	case 0x42:
		return "NotSpecified"; // ThermostatOperatingState COMMAND_CLASS_THERMOSTAT_OPERATING_STATE
	case 0x43:
		return "NotSpecified"; // ThermostatSetpoint COMMAND_CLASS_THERMOSTAT_SETPOINT
	case 0x8B:
		return "NotSpecified"; // TimeParameters COMMAND_CLASS_TIME_PARAMETERS
	case 0x63:
		return "NotSpecified"; // UserCode COMMAND_CLASS_USER_CODE
	case 0x86:
		return "NotSpecified"; // Version COMMAND_CLASS_VERSION
	case 0x84:
		return "NotSpecified"; // WakeUp COMMAND_CLASS_WAKE_UP
	case 0x5E:
		return "NotSpecified"; // ZWavePlusInfo COMMAND_CLASS_ZWAVEPLUS_INFO
	default:
		return "";
	}
}

const std::string ToValueType(const std::string type)
{
	if(type == "bool")
	{
		return "Boolean";
	}
	else if(type == "int")
	{
		return "Integer";
	}
	else
	{
		return "Decimal";
	}
}

DeviceData ToSensorData(OpenZWave::Notification const &notification)
{
	const auto homeId = notification.GetHomeId();
	const auto nodeId = notification.GetNodeId();
	const auto valueId = notification.GetValueID();
	const auto gatewayId = std::to_string(homeId);
	const auto deviceId = std::to_string(nodeId);
	const auto propertyId = std::to_string(valueId.GetId());
	const auto propertyType = GetPropertyType(valueId.GetCommandClassId(), OpenZWave::Manager::Get()->GetValueUnits(valueId));
	const auto propertyName = OpenZWave::Manager::Get()->GetValueLabel(valueId);
	const auto propertyDescription = OpenZWave::Manager::Get()->GetValueHelp(valueId);
	const auto protocol = OpenZWave::Manager::Get()->IsNodeZWavePlus(homeId, nodeId) ? "ZWavePlus" : "ZWave";
	const auto unitOfMeasurement = OpenZWave::Manager::Get()->GetValueUnits(valueId);
	const auto valueType = ToValueType(valueId.GetTypeAsString());
	const auto minimumValue = std::to_string(OpenZWave::Manager::Get()->GetValueMin(valueId));
	const auto maximumValue = std::to_string(OpenZWave::Manager::Get()->GetValueMax(valueId));
	const auto batteryVoltage = "";
	const auto rssi = "";
	const auto now = std::chrono::system_clock::now();
	const auto timestamp = CurrentTime();

	std::string value;
	OpenZWave::Manager::Get()->GetValueAsString(valueId, &value);

	const DeviceDatum deviceDatum(
		propertyId,
		propertyType,
		propertyName,
		propertyDescription,
		unitOfMeasurement,
		valueType,
		value,
		value,
		minimumValue,
		maximumValue);

	return DeviceData(
		gatewayId,
		deviceId,
		protocol,
		OpenZWave::Manager::Get()->GetNodeManufacturerName(homeId, nodeId),
		OpenZWave::Manager::Get()->GetNodeProductName(homeId, nodeId),
		{deviceDatum},
		batteryVoltage,
		rssi,
		timestamp);
}
