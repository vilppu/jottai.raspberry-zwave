#pragma once
#include "dependencies.cpp"

bool exiting = false;

void SIGINTHandler(int)
{
	exiting = true;
}
