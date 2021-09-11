#pragma once
#include "dependencies.cpp"

struct DeviceDatum
{
    DeviceDatum(
        const std::string propertyId,
        const std::string propertyType,
        const std::string propertyName,
        const std::string propertyDescription,
        const std::string unitOfMeasurement,
        const std::string valueType,
        const std::string value,
        const std::string formattedValue,
        const std::string minimumValue,
        const std::string maximumValue)
        : propertyId(propertyId),
          propertyType(propertyType),
          propertyName(propertyName),
          propertyDescription(propertyDescription),
          unitOfMeasurement(unitOfMeasurement),
          valueType(valueType),
          value(value),
          formattedValue(formattedValue),
          minimumValue(minimumValue),
          maximumValue(maximumValue)
    {
    }

    const std::string propertyId;
    const std::string propertyType;
    const std::string propertyName;
    const std::string propertyDescription;
    const std::string unitOfMeasurement;
    const std::string valueType;
    const std::string value;
    const std::string formattedValue;
    const std::string minimumValue;
    const std::string maximumValue;
};

struct DeviceData
{
    DeviceData(
        const std::string gatewayId,
        const std::string deviceId,
        const std::string protocol,
        const std::string manufacturerName,
        const std::string deviceName,
        const std::vector<DeviceDatum> data,
        const std::string batteryVoltage,
        const std::string rssi,
        const std::string timestamp)
        : gatewayId(gatewayId),
          deviceId(deviceId),
          protocol(protocol),
          manufacturerName(manufacturerName),
          deviceName(deviceName),
          data(data),
          batteryVoltage(batteryVoltage),
          rssi(rssi),
          timestamp(timestamp)
    {
    }

    const std::string gatewayId;
    const std::string deviceId;
    const std::string protocol;
    const std::string manufacturerName;
    const std::string deviceName;
    const std::vector<DeviceDatum> data;
    const std::string batteryVoltage;
    const std::string rssi;
    const std::string timestamp;
};

struct DevicePropertyChangeRequest
{
    DevicePropertyChangeRequest(
        const std::string gatewayId,
        const std::string deviceId,
        const std::string devicePartId,
        const std::string deviceStateType,
        const std::string valueType,
        const std::string state)
        : isRequested(true),
          gatewayId(gatewayId),
          deviceId(deviceId),
          devicePartId(devicePartId),
          deviceStateType(deviceStateType),
          valueType(valueType),
          state(state)
    {
    }

    DevicePropertyChangeRequest()
        : isRequested(false)
    {
    }

    static DevicePropertyChangeRequest Parse(const std::string json)
    {
        std::regex responseRegex("\\{\"gatewayId\":\"(\\w+)\",\"deviceId\":\"(\\w+)\",\"devicePartId\":\"(\\w+)\",\"deviceStateType\":\"(\\w+)\",\"valueType\":\"(\\w+)\",\"state\":(\\w+)\\}");
        std::smatch result;
        std::regex_match(json, result, responseRegex);

        std::cout << json << std::endl;
        std::cout << result.size() << std::endl;

        if (result.size() == 7)
        {
            const auto gatewayId = result[1];
            const auto deviceId = result[2];
            const auto devicePartId = result[3];
            const auto deviceStateType = result[4];
            const auto valueType = result[5];
            const auto state = result[6];

            return DevicePropertyChangeRequest(gatewayId, deviceId, devicePartId, deviceStateType, valueType, state);
        }
        return DevicePropertyChangeRequest();
    }

    const bool isRequested;
    const std::string gatewayId;
    const std::string deviceId;
    const std::string devicePartId;
    const std::string deviceStateType;
    const std::string valueType;
    const std::string state;
};

struct Agent
{
    Http http;
    const std::string path = "device-data";

    void SendDeviceData(std::string gatewayId, DeviceData sensorData)
    {
        if (sensorData.data.size() == 0)
        {
            return;
        }

        std::stringstream json;

        json
            << "{ "
            << "  \"gatewayId\": \"" << sensorData.gatewayId << "\","
            << "  \"deviceId\": \"" << sensorData.deviceId << "\","
            << "  \"protocol\": \"" << sensorData.protocol << "\","
            << "  \"manufacturerName\": \"" << sensorData.manufacturerName << "\","
            << "  \"batteryVoltage\": \"" << sensorData.batteryVoltage << "\","
            << "  \"rssi\": \"" << sensorData.rssi << "\","
            << "  \"timestamp\": \"" << sensorData.timestamp << "\","
            << "  \"data\": [";

        for (auto &datum : sensorData.data)
        {
            json
                << "  {"
                << "    \"propertyId\": \"" << datum.propertyId << "\","
                << "    \"propertyType\": \"" << datum.propertyType << "\","
                << "    \"propertyName\": \"" << datum.propertyName << "\","
                << "    \"propertyDescription\": \"" << datum.propertyDescription << "\","
                << "    \"unitOfMeasurement\": \"" << datum.unitOfMeasurement << "\","
                << "    \"valueType\": \"" << datum.valueType << "\","
                << "    \"value\": \"" << datum.value << "\","
                << "    \"formattedValue\": \"" << datum.formattedValue << "\","
                << "    \"minimumValue\": \"" << datum.minimumValue << "\","
                << "    \"maximumValue\": \"" << datum.maximumValue << "\""
                << "  }";

            if (&datum != &sensorData.data.back())
            {
                json << ",";
            }
        }

        json
            << "  ]"
            << "}";

        // std::cout<<json.str()<<std::endl;

        http.EnqueueHttpMessageToAgent(HttpRequest(path, json, true, 20));
    }

    DevicePropertyChangeRequest GetDevicePropertyChangeRequest()
    {
        const long serverTimeout = 60;

        auto [httpStatusCode, response] = SendToAgent(HttpRequest("change-device-state-request", "", false, serverTimeout + 10));

        if (httpStatusCode == 200)
        {
            return DevicePropertyChangeRequest::Parse(response);
        }
        else
        {
            return DevicePropertyChangeRequest();
        }
    }
};