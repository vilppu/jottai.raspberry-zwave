#pragma once
#include "dependencies.cpp"

SensorData ToSensorData(OpenZWave::Notification const& notification)
{
	std::cout<<"GetValueID().GetAsString(): "<<notification.GetValueID().GetAsString()<<std::endl;
	std::cout<<"GetValueID().GetTypeAsString(): "<<notification.GetValueID().GetTypeAsString()<<std::endl;
	std::cout<<"GetValueID().GetGenreAsString(): "<<notification.GetValueID().GetGenreAsString()<<std::endl;

	auto value = notification.GetValueID();
	std::cout<<"GetValueLabel(): "<<OpenZWave::Manager::Get()->GetValueLabel(value)<<std::endl;
	std::cout<<"GetValueUnits(): "<<OpenZWave::Manager::Get()->GetValueUnits(value)<<std::endl;
	std::cout<<"GetValueMin(): "<<OpenZWave::Manager::Get()->GetValueMin(value)<<std::endl;
	std::cout<<"GetValueMax(): "<<OpenZWave::Manager::Get()->GetValueMax(value)<<std::endl;
	
	std::string stringValue;
	OpenZWave::Manager::Get()->GetValueAsString(value, &stringValue);
	std::cout<<"GetValueAsString(): "<<stringValue<<std::endl;	
	
	return SensorData::Empty();
}
