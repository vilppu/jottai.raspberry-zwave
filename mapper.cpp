#pragma once
#include "dependencies.cpp"

SensorData ToSensorData(OpenZWave::Notification const& notification)
{
	return SensorData::Empty();
}
