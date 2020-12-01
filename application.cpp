#pragma once
#include "dependencies.cpp"

void Start()
{
	auto port = "/dev/ttyACM0";
	Handler Handler;
	
	std::cout<<"Starting ..."<<std::endl;

	OpenZWave::Options::Create( "./open-zwave/config/", "", "");
	OpenZWave::Options::Get()->AddOptionInt("SaveLogLevel", OpenZWave::LogLevel_Detail);
	OpenZWave::Options::Get()->AddOptionInt("QueueLogLevel", OpenZWave::LogLevel_Debug);
	OpenZWave::Options::Get()->AddOptionInt("DumpTrigger", OpenZWave::LogLevel_Error);
	OpenZWave::Options::Get()->AddOptionInt("PollInterval", 500);
	OpenZWave::Options::Get()->AddOptionBool("IntervalBetweenPolls", true);
	OpenZWave::Options::Get()->AddOptionBool("ValidateValueChanges", true);
	OpenZWave::Options::Get()->Lock();
	OpenZWave::Manager::Create();
	OpenZWave::Manager::Get()->AddWatcher(Handler::Handle, &Handler);
	OpenZWave::Manager::Get()->AddDriver(port);
	OpenZWave::Manager::Get()->RemoveDriver(port);
	OpenZWave::Manager::Get()->RemoveWatcher(Handler::Handle, &Handler);
	OpenZWave::Manager::Destroy();
	OpenZWave::Options::Destroy();

	sleep(5);
	std::cout<<"Quitting ..."<<std::endl;
}

void Test()
{	
	std::cout<<"Running self-test ..."<<std::endl;

	Handler stateHolder;

	// EnqueueHttpMessageToAgent(JsonObject(""));
	// EnqueueHttpMessageToAgent(JsonObject(""));
	// EnqueueHttpMessageToAgent(JsonObject(""));

	std::this_thread::sleep_for (std::chrono::seconds(1));
}
