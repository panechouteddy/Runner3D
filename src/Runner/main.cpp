#include "pch.h"
#include "App.h"

int main()
{
	App::Get()->Run();
	App::Get()->Shutdown();

	return 0;
}