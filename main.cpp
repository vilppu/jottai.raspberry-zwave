#include "dependencies.cpp"

int main(int argc, char *argv[])
{
	if (argc > 1 && std::string(argv[1]) == "test")
	{
		Start(true);
	}
	else
	{
		Start(false);
	}

	return 0;
}
