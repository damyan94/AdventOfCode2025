#include "stdafx.h"

#include "Application/Application/Application.h"

////////////////////////////////////////////////////////////////////////////////
bool Application::Init()
{
	srand((uint32_t)time(nullptr));

	Log::Init();

#ifdef DEBUG
	Log::SetLogLevel(ELogLevel::LogDebug);

#else
	Log::SetLogLevel(ELogLevel::LogInfo);

#endif

	return true;
}

////////////////////////////////////////////////////////////////////////////////
void Application::Run()
{
	bool running = false;
	while (running)
	{
		//TODO implement
	}
}