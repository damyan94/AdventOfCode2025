#include "stdafx.h"

#include "Application/Application/Application.h"
#include "Application.h"

bool Application::Init(CommandLineArgs args)
{
	m_Args = args;
	m_IsRunning = m_Args.ArgC <= 1;
	if(!m_IsRunning)
	{
		ParseCommandLineArgs();
		return true;
	}

	srand((uint32_t)time(nullptr));

	Log::Init();

#ifdef DEBUG
	Log::SetLogLevel(ELogLevel::LogDebug);

#else
	Log::SetLogLevel(ELogLevel::LogInfo);

#endif

	return true;
}

void Application::Run()
{
	if(m_IsRunning)
	{
		PrintWelcomeMessage();
	}

	while (m_IsRunning)
	{
		Log::Text("\nAOC > ", false);

		std::string currCommand;
		std::cin >> currCommand;

		if(currCommand == "h" || currCommand == "help")
		{
			PrintCommandsHelp();
		}
		else if(currCommand == "v" || currCommand == "version")
		{
			PrintVersion();
		}
		else if(currCommand == "q" || currCommand == "quit")
		{
			m_IsRunning = false;
		}
		else
		{
			PrintInvalidCommand();
		}
	}
}

void Application::ParseCommandLineArgs() const
{
	for (int32_t i = 1; i < m_Args.ArgC; i++)
	{
		const std::string currArg = m_Args.ArgV[i];
		if(currArg == "-h" || currArg == "--help")
		{
			PrintCommandLineArgsHelp();
		}
		else if(currArg == "-v" || currArg == "--version")
		{
			PrintVersion();
		}
		else
		{
			PrintInvalidArg();
		}
	}
}

void Application::PrintWelcomeMessage() const
{
	Log::Text("Welcome to Advent of Code 2025 (AOC2025)!");
	Log::Text("For help type h or help.");
}

void Application::PrintCommandLineArgsHelp() const
{
	Log::Text("Advent of Code 2025 command line arguments:");
	Log::Text("Short command\t| Long command\t| Description");
	Log::Text("--------------------------------------------------------------------------------");
	Log::Text("-h\t\t| --help\t| Print help message.");
	Log::Text("-v\t\t| --version\t| Print version message.");
}

void Application::PrintCommandsHelp() const
{
	Log::Text("Advent of Code 2025 commands:");
	Log::Text("Short command\t| Long command\t| Description");
	Log::Text("--------------------------------------------------------------------------------");
	Log::Text("h\t\t| help\t\t| Print help message.");
	Log::Text("v\t\t| version\t| Print version message.");
	Log::Text("q\t\t| quit\t\t| Quit the program.");
}

void Application::PrintVersion() const
{
	Log::Text("Advent of Code 2025. Build date: " __DATE__ " " __TIME__);
	Log::Text("By Damyan Damyanov - https://github.com/damyan94");
}

void Application::PrintInvalidArg() const
{
	Log::Text("Error! Invalid command line argument provided.");
	Log::Text("Run program with -h or --help to print valid command line arguments and commands.");
}

void Application::PrintInvalidCommand() const
{
	Log::Text("Error! Invalid command provided.");
	Log::Text("Run program with -h or --help to print valid command line arguments and commands.");
}