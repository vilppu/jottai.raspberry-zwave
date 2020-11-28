void Start()
{
	auto port = "/dev/ttyACM01";
	StateHolder stateHolder;
	HttpMessageQueue httpMessageQueue;
	
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
	OpenZWave::Manager::Get()->AddWatcher(OnNotification, &stateHolder);
	// OpenZWave::Manager::Get()->AddDriver(port);		
	// OpenZWave::Manager::Get()->RemoveDriver(port);
	OpenZWave::Manager::Get()->RemoveWatcher(OnNotification, &stateHolder);
	OpenZWave::Manager::Destroy();
	OpenZWave::Options::Destroy();

	std::cout<<"Quitting ..."<<std::endl;
}

void Test()
{	
	std::cout<<"Running self-test ..."<<std::endl;

	StateHolder stateHolder;
	HttpMessageQueue httpMessageQueue;

	EnqueueHttpMessage(httpMessageQueue, HttpMessage());
	EnqueueHttpMessage(httpMessageQueue, HttpMessage());
	EnqueueHttpMessage(httpMessageQueue, HttpMessage());

	std::this_thread::sleep_for (std::chrono::seconds(1));
}
