#pragma once

enum class ELogLevel
	: int8_t
{
	Invalid = -1
	, LogNone		// Log nothing
	, LogText		// Log text
	, LogError		// Log text and errors
	, LogWarning	// Log text, errors and warnings
	, LogInfo		// Log text, errors, warnings and info
	, LogDebug		// Log everything
	, Count
};

enum class ETextColor
	: int8_t
{
	Invalid = -1
	, Black
	, Red
	, Green
	, Yellow
	, Blue
	, Magenta
	, Cyan
	, White
	, Count
};

enum class ETextStyle
	: int8_t
{
	Invalid = -1
	, Regular
	, Dim
	, Italic
	, Underlined
	, CrossedOut
	, DoublyUnderlined
	, Count
};

enum class EMessageType
	: int8_t
{
	Invalid = -1
	, Text
	, Error
	, Count
};

namespace Log
{
	void Init();

	void Text(const std::string& text, bool newLine = true, bool timestamp = false);
	void Text(const std::string& text, ETextColor textColor, bool newLine = true, bool timestamp = false);
	void Text(const std::string& text, ETextColor textColor, ETextStyle textStyle, bool newLine = true, bool timestamp = false);

	void Error(const std::string& text);
	void Warning(const std::string& text);
	void Info(const std::string& text);
	void Debug(const std::string& text);

	void SetLogLevel(ELogLevel logLevel);
	ELogLevel GetLogLevel();

	void _TestLogging();
} // !namespace Log