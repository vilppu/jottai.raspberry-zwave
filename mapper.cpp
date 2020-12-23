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

DeviceData ToSensorData(OpenZWave::Notification const& notification)
{	
	const auto homeId = notification.GetHomeId();
	const auto nodeId = notification.GetNodeId();
	const auto valueId = notification.GetValueID();
	const auto gatewayId = std::to_string(homeId);
	const auto deviceId = std::to_string(nodeId);
	const auto propertyId = std::to_string(valueId.GetId());
    const auto propertyTypeId = std::to_string((int)valueId.GetCommandClassId());
    const auto propertyName = OpenZWave::Manager::Get()->GetValueLabel(valueId);
    const auto propertyDescription = OpenZWave::Manager::Get()->GetValueHelp(valueId);
    const auto protocol = OpenZWave::Manager::Get()->IsNodeZWavePlus(homeId, nodeId) ? "Z-Wave Plus" : "Z-Wave";
    const auto unitOfMeasurement = OpenZWave::Manager::Get()->GetValueUnits(valueId);
    const auto valueType = valueId.GetTypeAsString();    
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
		propertyTypeId,
		propertyName,
		propertyDescription,
		protocol,
		unitOfMeasurement,
		valueType,
		value,
		value,
		minimumValue,
		maximumValue
	);

	return DeviceData(
        gatewayId,
        "",
        deviceId,
        OpenZWave::Manager::Get()->GetNodeManufacturerName(homeId, nodeId),
        OpenZWave::Manager::Get()->GetNodeProductName(homeId, nodeId),
        { deviceDatum },
        batteryVoltage,
        rssi,
        timestamp);
}
