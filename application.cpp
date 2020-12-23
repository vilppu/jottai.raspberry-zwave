#pragma once
#include "dependencies.cpp"

void Start()
{
	auto port = "/dev/ttyACM0";

	signal(SIGINT, SIGINTHandler);

	Handler handler;
	
	std::cout<<"Starting ..."<<std::endl;

	OpenZWave::Options::Create( "./open-zwave/config/", "", "");
	OpenZWave::Options::Get()->AddOptionInt("SaveLogLevel", OpenZWave::LogLevel_Error);
	OpenZWave::Options::Get()->AddOptionInt("QueueLogLevel", OpenZWave::LogLevel_Error);
	OpenZWave::Options::Get()->AddOptionInt("DumpTrigger", OpenZWave::LogLevel_Error);
	OpenZWave::Options::Get()->AddOptionInt("PollInterval", 500);
	OpenZWave::Options::Get()->AddOptionBool("IntervalBetweenPolls", true);
	OpenZWave::Options::Get()->AddOptionBool("ValidateValueChanges", true);
	OpenZWave::Options::Get()->Lock();
	OpenZWave::Manager::Create();
	OpenZWave::Manager::Get()->AddWatcher(Handler::Handle, &handler);
	OpenZWave::Manager::Get()->AddDriver(port);

	std::cout<<"Initializing..."<<std::endl;
	handler.WaitUntilInitializationHandled();
	std::cout<<"Initializing completed."<<std::endl;

	while (!exiting)
	{
		std::cout<<"Waiting ..."<<std::endl;
		sleep(5);
	}

	OpenZWave::Manager::Get()->RemoveDriver(port);
	OpenZWave::Manager::Get()->RemoveWatcher(Handler::Handle, &handler);
	OpenZWave::Manager::Destroy();
	OpenZWave::Options::Destroy();

	
	std::cout<<"Quitting ..."<<std::endl;
}

void Test()
{	
	std::cout<<"Running self-test ..."<<std::endl;

	Handler stateHolder;

	// EnqueueHttpMessageToAgent(HttpRequest(""));
	// EnqueueHttpMessageToAgent(HttpRequest(""));
	// EnqueueHttpMessageToAgent(HttpRequest(""));

	std::this_thread::sleep_for (std::chrono::seconds(1));
}
