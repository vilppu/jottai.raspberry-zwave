#pragma once
#include "dependencies.cpp"

struct SensorDatum
{
    const std::string name;
    const std::string value;
    const std::optional<std::string> formattedValue;
    const std::optional<int> scale;
};

struct SensorData
{
    const std::string deviceId;
    const std::vector<SensorDatum> data;
    const int timestamp;
    const std::optional<float> batteryVoltage;
    const std::optional<float> rssi;

    SensorData()
    : deviceId(), data(), timestamp(0), batteryVoltage(0), rssi(0)
    {        
    }

    SensorData(
        const std::string deviceId,
        const std::vector<SensorDatum> data,
        const int timestamp,
        const std::optional<float> batteryVoltage,
        const std::optional<float> rssi)
    : deviceId(deviceId), data(data), timestamp(SinceEpoch()), batteryVoltage(batteryVoltage), rssi(rssi)
    {        
    }

    static int SinceEpoch()
    {
        auto timeSinceEpoch = std::chrono::system_clock::now().time_since_epoch();
        auto millisecondsSinceEpoch = std::chrono::duration_cast<std::chrono::milliseconds>(timeSinceEpoch);

        return millisecondsSinceEpoch.count();
    }

    static SensorData Empty()
    {
        return SensorData();
    }
};

struct Agent
{
    Http http;
    const std::string path = "sensor-data";

    void SendGatewayUpEvent(std::string gatewayId)
    {       
        std::stringstream json;

        json
        <<"{ "
        <<"  \"event\": \"gateway up\","
        <<"  \"gatewayId\": \""<<gatewayId<<"\""
        <<"}";

        http.EnqueueHttpMessageToAgent(HttpRequest(path, json));
    }

    void SendGatewayDownEvent(std::string gatewayId)
    {       
        std::stringstream json;

        json
        <<"{ "
        <<"  \"event\": \"gateway down\","
        <<"  \"gatewayId\": \""<<gatewayId<<"\""
        <<"}";

        http.EnqueueHttpMessageToAgent(HttpRequest(path, json));
    }

    void SendGatewayActiveEvent(std::string gatewayId)
    {       
        std::stringstream json;

        json
        <<"{ "
        <<"  \"event\": \"gateway active\","
        <<"  \"gatewayId\": \""<<gatewayId<<"\""        
        <<"}";

        http.EnqueueHttpMessageToAgent(HttpRequest(path, json));
    }

    void SendSensorUpEvent(std::string gatewayId, std::string sensorId, std::string sensorName)
    {       
        std::stringstream json;

        json
        <<"{ "
        <<"  \"event\": \"sensor up\","
        <<"  \"sensorId\": \""<<sensorId<<"\","
        <<"  \"gatewayId\": \""<<gatewayId<<"\","
        <<"  \"sensorName\": \""<<sensorName<<"\""
        <<"}";

        http.EnqueueHttpMessageToAgent(HttpRequest(path, json));
    }

    template<typename T>
    std::string ToOptionalJsonKeyValuePairFollowedByComma(std::string key, T value)
    {
        if(value)
        {
            return "\"" + key + "\": \"" + std::to_string(*value) + "\",";
        }
        else
        {
            return std::string();
        }
    }

    template<typename T>
    std::string ToOptionalJsonKeyValuePair(std::string key, T value)
    {
        if(value)
        {
            return "\"" + key + "\": \"" + std::to_string(*value) + "\"";
        }
        else
        {
            return std::string();
        }
    }

    template<typename T>
    std::string ToOptionalStringJsonKeyValuePair(std::string key, T value)
    {
        if(value)
        {
            return "\"" + key + "\": \"" + *value + "\"";
        }
        else
        {
            return std::string();
        }
    }

    void SendSensorDataEvent(std::string gatewayId, SensorData sensorData)
    {       
        std::stringstream json;

        json
        <<"{ "
        <<"  \"event\": \"sensor data\","
        <<"  \"sensorId\": \""<<sensorData.deviceId<<"\","
        <<"  \"gatewayId\": \""<<gatewayId<<"\","
        <<"  \"data\": [";

        for(auto& datum : sensorData.data)
        {
            json
            <<"  {"
            <<"    \"name\": \""<<datum.name<<"\","
            <<"    \"value\": \""<<datum.value<<"\","
            <<ToOptionalJsonKeyValuePairFollowedByComma("scale", datum.scale)
            <<ToOptionalStringJsonKeyValuePair("formattedValue", datum.formattedValue)
            <<"  }";

            if(&datum != &sensorData.data.back()) {
                json<<",";
            }
        }

        json
        <<"  ],"
        <<ToOptionalJsonKeyValuePairFollowedByComma("batteryVoltage", sensorData.batteryVoltage)
        <<ToOptionalJsonKeyValuePair("rssi", sensorData.rssi);

        json<<"}";

        http.EnqueueHttpMessageToAgent(HttpRequest(path, json));
    }
};
