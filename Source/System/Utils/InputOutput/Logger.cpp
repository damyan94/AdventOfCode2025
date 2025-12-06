#include "stdafx.h"

#include "System/Utils/InputOutput/Logger.h"

#include <filesystem>

namespace
{
ELogLevel	m_LogLevel			= ELogLevel::LogInfo;
ETextColor	m_DefaultTextColor	= ETextColor::White;
ETextStyle	m_DefaultTextStyle	= ETextStyle::Regular;

constexpr const char* LogsDir = "Logs/";

void LogErrorToFile(const std::string& text);

constexpr const char* GetTextColor(ETextColor textColor)
{
	switch (textColor)
	{
	case ETextColor::Black:		return "90m";
	case ETextColor::Red:		return "91m";
	case ETextColor::Green:		return "92m";
	case ETextColor::Yellow:	return "93m";
	case ETextColor::Blue:		return "94m";
	case ETextColor::Magenta:	return "95m";
	case ETextColor::Cyan:		return "96m";
	case ETextColor::White:		return "97m";
	default:					return "";
	}
}

constexpr const char* GetTextStyle(ETextStyle textStyle)
{
	switch (textStyle)
	{
	case ETextStyle::Regular:			return "\033[0;";
	case ETextStyle::Dim:				return "\033[2;";
	case ETextStyle::Italic:			return "\033[3;";
	case ETextStyle::Underlined:		return "\033[4;";
	case ETextStyle::CrossedOut:		return "\033[9;";
	case ETextStyle::DoublyUnderlined:	return "\033[21;";
	default:							return "";
	}
}

void PrintLineToConsole(const std::string& text,
	ETextColor textColor, ETextStyle textStyle, EMessageType messageType)
{
	const auto timestamp = Time::GetNow().GetString(ETimeStringFormat::Default);
	const auto timestampedText = Format("[{0}] {1}", timestamp, text);

	auto print = [&timestampedText, &textColor, &textStyle](std::ostream& outStream)
		{
			outStream << GetTextStyle(textStyle) << GetTextColor(textColor);
			outStream << timestampedText << '\n';
			outStream << GetTextStyle(m_DefaultTextStyle) << GetTextColor(m_DefaultTextColor);
		};

	switch (messageType)
	{
	case EMessageType::Text:
		print(std::cout);
		break;

	case EMessageType::Error:
		print(std::cerr);
		LogErrorToFile(timestampedText);
		break;

	default:
		Assert("Invalid message type.");
		break;
	}
}

void LogErrorToFile(const std::string& text)
{
	static File errorFile(LogsDir + Format("ErrorLog_{0}.txt",
		Time::GetNow().GetString(ETimeStringFormat::Timestamp)), true);

	errorFile.AddLine(text);
}
} //!namespace

namespace Log
{
void Init()
{
	if (!std::filesystem::exists(LogsDir))
	{
		std::filesystem::create_directories(LogsDir);
	}
}

void Text(const std::string& text)
{
	Text(text, m_DefaultTextColor, m_DefaultTextStyle);
}

void Text(const std::string& text, ETextColor textColor)
{
	Text(text, textColor, m_DefaultTextStyle);
}
void Text(const std::string& text, ETextColor textColor, ETextStyle textStyle)
{
	ReturnIf(m_LogLevel < ELogLevel::LogText);
	PrintLineToConsole(text, textColor, textStyle, EMessageType::Text);
}

void Error(const std::string& text)
{
	ReturnIf(m_LogLevel < ELogLevel::LogError);
	PrintLineToConsole("[ERROR] " + text, ETextColor::Red, ETextStyle::Regular, EMessageType::Error);
}

void Warning(const std::string& text)
{
	ReturnIf(m_LogLevel < ELogLevel::LogWarning);
	PrintLineToConsole("[WARNING] " + text, ETextColor::Yellow, ETextStyle::Regular, EMessageType::Text);
}

void Info(const std::string& text)
{
	ReturnIf(m_LogLevel < ELogLevel::LogInfo);
	PrintLineToConsole("[INFO] " + text, ETextColor::White, ETextStyle::Regular, EMessageType::Text);
}

void Debug(const std::string& text)
{
	ReturnIf(m_LogLevel < ELogLevel::LogDebug);
	PrintLineToConsole("[DEBUG] " + text, ETextColor::Cyan, ETextStyle::Regular, EMessageType::Text);
}

void SetLogLevel(ELogLevel logLevel)
{
	m_LogLevel = logLevel;
}

ELogLevel GetLogLevel()
{
	return m_LogLevel;
}

void TestLogging()
{
	const auto previousLogLevel = GetLogLevel();

	Text("Starting logging test...", ETextColor::Green, ETextStyle::Underlined);
	Text("----------------------------------------");
	SetLogLevel(ELogLevel::LogDebug);
	Text("Text, log level = " + std::to_string((int8_t)GetLogLevel()), ETextColor::Blue);
	Info("Info 1");
	Warning("Warning 1");
	Error("Error 1");

	Text("----------------------------------------");
	SetLogLevel(ELogLevel::LogInfo);
	Text("Text, log level = " + std::to_string((int8_t)GetLogLevel()), ETextColor::Cyan, ETextStyle::Italic);
	Info("Info 2");
	Warning("Warning 2");
	Error("Error 2");

	Text("----------------------------------------");
	SetLogLevel(ELogLevel::LogWarning);
	Text("Text, log level = " + std::to_string((int8_t)GetLogLevel()), ETextColor::Green, ETextStyle::CrossedOut);
	Info("Info 3");
	Warning("Warning 3");
	Error("Error 3");

	Text("----------------------------------------");
	SetLogLevel(ELogLevel::LogError);
	Text("Text, log level = " + std::to_string((int8_t)GetLogLevel()), ETextColor::Magenta, ETextStyle::DoublyUnderlined);
	Info("Info 4");
	Warning("Warning 4");
	Error("Error 4");

	Text("----------------------------------------");
	SetLogLevel(ELogLevel::LogText);
	Text("Text, log level = " + std::to_string((int8_t)GetLogLevel()));
	Info("Info 5");
	Warning("Warning 5");
	Error("Error 5");

	Text("----------------------------------------");
	SetLogLevel(ELogLevel::LogNone);
	Text("Text, log level = " + std::to_string((int8_t)GetLogLevel()));
	Info("Info 6");
	Warning("Warning 6");
	Error("Error 6");
	Text("----------------------------------------");

	SetLogLevel(ELogLevel::LogDebug);
	Text("Logging test finished.", ETextColor::Green, ETextStyle::Underlined);

	SetLogLevel(previousLogLevel);
}
} // !namespace Log