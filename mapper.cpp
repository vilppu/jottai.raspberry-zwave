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

const std::optional<std::string> GetPropertyType(const int commandClassId, const std::string &valueUnits)
{
	// http://www.openzwave.com/dev/group__CommandClass.html
	switch (commandClassId)
	{
	case 0x71:
		return {}; // Alarm COMMAND_CLASS_NOTIFICATION
	case 0x22:
		return {}; // ApplicationStatus COMMAND_CLASS_APPLICATION_STATUS
	case 0x85:
		return {}; // Association COMMAND_CLASS_ASSOCIATION
	case 0x9b:
		return {}; // AssociationCommandConfiguration COMMAND_CLASS_ASSOCIATION_COMMAND_CONFIGURATION
	case 0x66:
		return {}; // BarrierOperator COMMAND_CLASS_BARRIER_OPERATOR
	case 0x20:
		return {}; // Basic COMMAND_CLASS_BASIC
	case 0x50:
		return {}; // BasicWindowCovering COMMAND_CLASS_BASIC_WINDOW_COVERING
	case 0x80:
		return {}; // Battery COMMAND_CLASS_BATTERY
	case 0x5B:
		return {}; // CentralScene COMMAND_CLASS_CENTRAL_SCENE
	case 0x46:
		return {}; // ClimateControlSchedule COMMAND_CLASS_CLIMATE_CONTROL_SCHEDULE
	case 0x81:
		return {}; // Clock COMMAND_CLASS_CLOCK
	case 0x33:
		return {}; // Color COMMAND_CLASS_COLOR
	case 0x70:
		return {}; // Configuration COMMAND_CLASS_CONFIGURATION
	case 0x21:
		return {}; // ControllerReplication COMMAND_CLASS_CONTROLLER_REPLICATION
	case 0x56:
		return {}; // CRC16Encap COMMAND_CLASS_CRC_16_ENCAP
	case 0x5a:
		return {}; // DeviceResetLocally COMMAND_CLASS_DEVICE_RESET_LOCALLY
	case 0x62:
		return {}; // DoorLock COMMAND_CLASS_DOOR_LOCK
	case 0x4C:
		return {}; // DoorLockLogging COMMAND_CLASS_DOOR_LOCK_LOGGING
	case 0x90:
		return {}; // EnergyProduction COMMAND_CLASS_ENERGY_PRODUCTION
	case 0x82:
		return {}; // Hail COMMAND_CLASS_HAIL
	case 0x87:
		return {}; // Indicator COMMAND_CLASS_INDICATOR
	case 0x89:
		return {}; // Language COMMAND_CLASS_LANGUAGE
	case 0x76:
		return {}; // Lock COMMAND_CLASS_LOCK
	case 0x91:
		return {}; // ManufacturerProprietary COMMAND_CLASS_PROPRIETARY
	case 0x72:
		return {}; // ManufacturerSpecific COMMAND_CLASS_MANUFACTURER_SPECIFIC
	case 0x32:
		return {}; // Meter COMMAND_CLASS_METER
	case 0x35:
		return {}; // MeterPulse COMMAND_CLASS_METER_PULSE
	case 0x8E:
		return {}; // MultiChannelAssociation COMMAND_CLASS_MULTI_CHANNEL_ASSOCIATION
	case 0x8f:
		return {}; // MultiCmd COMMAND_CLASS_MULTI_CMD
	case 0x60:
		return {}; // MultiInstance COMMAND_CLASS_MULTI_INSTANCE
	case 0x77:
		return {}; // NodeNaming COMMAND_CLASS_NODE_NAMING
	case 0x00:
		return {}; // NoOperation COMMAND_CLASS_NO_OPERATION
	case 0x73:
		return {}; // Powerlevel COMMAND_CLASS_POWERLEVEL
	case 0x88:
		return {}; // Proprietary COMMAND_CLASS_PROPRIETARY
	case 0x75:
		return {}; // Protection COMMAND_CLASS_PROTECTION
	case 0x2B:
		return {}; // SceneActivation COMMAND_CLASS_SCENEACTIVATION
	case 0x98:
		return {}; // Security COMMAND_CLASS_SECURITY
	case 0x9c:
		return {}; // SensorAlarm COMMAND_CLASS_SENSOR_ALARM
	case 0x30:
		return {}; // SensorBinary COMMAND_CLASS_SENSOR_BINARY
	case 0x31:
		if (valueUnits == "C")
		{
			return "Temperature";
		}
		else if (valueUnits == "MM")
		{
			return "SeismicIntensity";
		}
		else if (valueUnits == "Lux")
		{
			return "Luminance";
		}
		return {}; // SensorMultilevel COMMAND_CLASS_SENSOR_MULTILEVEL
	case 0x79:
		return {}; // SoundSwitch COMMAND_CLASS_SOUND_SWITCH
	case 0x27:
		return {}; // SwitchAll COMMAND_CLASS_SWITCH_ALL
	case 0x25:
		return "TwoWaySwitch"; // SwitchBinary COMMAND_CLASS_SWITCH_BINARY
	case 0x26:
		return {}; // SwitchMultilevel COMMAND_CLASS_SWITCH_MULTILEVEL
	case 0x28:
		return {}; // SwitchToggleBinary COMMAND_CLASS_SWITCH_TOGGLE_BINARY
	case 0x29:
		return {}; // SwitchToggleMultilevel COMMAND_CLASS_SWITCH_TOGGLE_MULTILEVEL
	case 0x44:
		return {}; // ThermostatFanMode COMMAND_CLASS_THERMOSTAT_FAN_MODE
	case 0x45:
		return {}; // ThermostatFanState COMMAND_CLASS_THERMOSTAT_FAN_STATE
	case 0x40:
		return {}; // ThermostatMode COMMAND_CLASS_THERMOSTAT_MOD
	case 0x42:
		return {}; // ThermostatOperatingState COMMAND_CLASS_THERMOSTAT_OPERATING_STATE
	case 0x43:
		return {}; // ThermostatSetpoint COMMAND_CLASS_THERMOSTAT_SETPOINT
	case 0x8B:
		return {}; // TimeParameters COMMAND_CLASS_TIME_PARAMETERS
	case 0x63:
		return {}; // UserCode COMMAND_CLASS_USER_CODE
	case 0x86:
		return {}; // Version COMMAND_CLASS_VERSION
	case 0x84:
		return {}; // WakeUp COMMAND_CLASS_WAKE_UP
	case 0x5E:
		return {}; // ZWavePlusInfo COMMAND_CLASS_ZWAVEPLUS_INFO
	default:
		return "";
	}
}

const std::string ToValueType(const std::string type)
{
	if (type == "bool")
	{
		return "Boolean";
	}
	else if (type == "int")
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

	const std::optional<DeviceDatum> deviceDatum =
		propertyType.has_value()
			? std::optional(DeviceDatum(
				  propertyId,
				  propertyType.value(),
				  propertyName,
				  propertyDescription,
				  unitOfMeasurement,
				  valueType,
				  value,
				  value,
				  minimumValue,
				  maximumValue))
			: std::nullopt;

	const std::vector<DeviceDatum> deviceData =
		deviceDatum.has_value()
			? std::vector<DeviceDatum>({deviceDatum.value()})
			: std::vector<DeviceDatum>({});

	return DeviceData(
		gatewayId,
		deviceId,
		protocol,
		OpenZWave::Manager::Get()->GetNodeManufacturerName(homeId, nodeId),
		OpenZWave::Manager::Get()->GetNodeProductName(homeId, nodeId),
		deviceData,
		batteryVoltage,
		rssi,
		timestamp);
}
