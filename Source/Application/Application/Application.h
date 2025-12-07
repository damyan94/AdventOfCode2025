#pragma once

struct CommandLineArgs
{
	int32_t ArgC;
	char**  ArgV;
};

class Application
{
public:
	Application() = default;
	~Application() = default;

	bool Init(CommandLineArgs args);
	void Run();

private:
	void ParseCommandLineArgs() const;

	//TODO Move these to a separate class
	void PrintWelcomeMessage() const;
	void PrintCommandLineArgsHelp() const;
	void PrintCommandsHelp() const;

	void PrintVersion() const;
	void PrintInvalidArg() const;
	void PrintInvalidCommand() const;

private:
	CommandLineArgs m_Args;
	bool m_IsRunning;
};