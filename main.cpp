#include <stdint.h>
#include "http.cpp"
#include "state.cpp"
#include "notifications.cpp"
#include "application.cpp"

int main(int argc, char* argv[])
{
	if(argc > 1 && std::string(argv[1])=="test")
	{
		Test();
	}
	else
	{
		Start();
	}
	
	return 0;
}
