#pragma once
#include "dependencies.cpp"

bool exiting = false;

void SIGINTHandler(int)
{
	std::cout << "Received SIGINT" << std::endl;
	exiting = true;
}
