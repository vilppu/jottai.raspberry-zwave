#pragma once
#include "dependencies.cpp"

struct SensorDatum
{
    const std::string name;
    const std::string value;
    const std::string scale;
    const std::string formattedValue;
};

struct SensorData
{
    const std::string sensorId;
    const std::vector<SensorDatum> data;
    const int batteryVoltage;
    const int rssi;
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

    void SendSensorDataEvent(std::string gatewayId, SensorData sensorData)
    {       
        std::stringstream json;

        json
        <<"{ "
        <<"  \"event\": \"sensor data\","
        <<"  \"sensorId\": \""<<sensorData.sensorId<<"\","
        <<"  \"gatewayId\": \""<<gatewayId<<"\","
        <<"  \"data\": [";

        for(auto& datum : sensorData.data)
        {
            json
            <<"  {"
            <<"    \"name\": \""<<datum.name<<"\","
            <<"    \"value\": \""<<datum.value<<"\","
            <<"    \"formattedValue\": \""<<datum.formattedValue<<"\""
            <<"  }";

            if(&datum != &sensorData.data.back()) {
                json<<",";
            }
        }

        json
        <<"  ],"
        <<"  \"batteryVoltage\": \""<<sensorData.batteryVoltage/100<<"."<<sensorData.batteryVoltage%100<<" VDC\","
        <<"  \"rssi\": \""<<(int)sensorData.rssi<<" dBm\"";

        json<<"}";

        http.EnqueueHttpMessageToAgent(HttpRequest(path, json));
    }
};
