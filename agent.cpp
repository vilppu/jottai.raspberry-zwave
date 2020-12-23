#pragma once
#include "dependencies.cpp"

struct DeviceDatum
{    
    DeviceDatum(
        const std::string propertyId,
        const std::string propertyTypeId,
        const std::string propertyName,
        const std::string propertyDescription,
        const std::string protocol,
        const std::string unitOfMeasurement,
        const std::string valueType,
        const std::string value,
        const std::string formattedValue,
        const std::string minimumValue,
        const std::string maximumValue)
    : propertyId(propertyId),
      propertyTypeId(propertyTypeId),
      propertyName(propertyId),
      propertyDescription(propertyDescription),
      protocol(protocol),
      unitOfMeasurement(unitOfMeasurement),
      valueType(valueType),
      value(value),
      formattedValue(formattedValue),
      minimumValue(minimumValue),
      maximumValue(maximumValue)
    {        
    }

    const std::string propertyId;
    const std::string propertyTypeId;
    const std::string propertyName;
    const std::string propertyDescription;
    const std::string protocol;
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
        const std::string channel,
        const std::string deviceId,
        const std::string manufacturerName,
        const std::string deviceName,
        const std::vector<DeviceDatum> data,
        const std::string batteryVoltage,
        const std::string rssi,
        const std::string timestamp)
    : gatewayId(gatewayId),
      channel(channel),
      deviceId(deviceId),
      manufacturerName(manufacturerName),
      deviceName(deviceName),
      data(data),
      batteryVoltage(batteryVoltage),
      rssi(rssi),
      timestamp(timestamp)
    {        
    }

    const std::string gatewayId;
    const std::string channel;
    const std::string deviceId;
    const std::string manufacturerName;
    const std::string deviceName;
    const std::vector<DeviceDatum> data;
    const std::string batteryVoltage;
    const std::string rssi;
    const std::string timestamp;
};

struct Agent
{
    Http http;
    const std::string path = "sensor-data";

    void SendSensorDataEvent(std::string gatewayId, DeviceData sensorData)
    {       
        std::stringstream json;

        json
        <<"{ "
        <<"  \"gatewayId\": \""<<sensorData.gatewayId<<"\","
        <<"  \"channel\": \""<<sensorData.channel<<"\","
        <<"  \"deviceId\": \""<<sensorData.deviceId<<"\","
        <<"  \"sensorId\": \""<<sensorData.deviceId<<"\","
        <<"  \"manufacturerName\": \""<<sensorData.manufacturerName<<"\","
        <<"  \"batteryVoltage\": \""<<sensorData.batteryVoltage<<"\","
        <<"  \"rssi\": \""<<sensorData.rssi<<"\","
        <<"  \"timestamp\": \""<<sensorData.timestamp<<"\","
        <<"  \"data\": [";

        for(auto& datum : sensorData.data)
        {
            json
            <<"  {"
            <<"    \"propertyId\": \""<<datum.propertyId<<"\","
            <<"    \"propertyTypeId\": \""<<datum.propertyTypeId<<"\","
            <<"    \"propertyName\": \""<<datum.propertyName<<"\","
            <<"    \"propertyDescription\": \""<<datum.propertyDescription<<"\","
            <<"    \"protocol\": \""<<datum.protocol<<"\","
            <<"    \"unitOfMeasurement\": \""<<datum.unitOfMeasurement<<"\","
            <<"    \"valueType\": \""<<datum.valueType<<"\","
            <<"    \"value\": \""<<datum.value<<"\","
            <<"    \"formattedValue\": \""<<datum.formattedValue<<"\","
            <<"    \"minimumValue\": \""<<datum.minimumValue<<"\","
            <<"    \"maximumValue\": \""<<datum.maximumValue<<"\""
            <<"  }";

            if(&datum != &sensorData.data.back()) {
                json<<",";
            }
        }

        json
        <<"  ],"
        <<"}";

        http.EnqueueHttpMessageToAgent(HttpRequest(path, json));
    }
};
