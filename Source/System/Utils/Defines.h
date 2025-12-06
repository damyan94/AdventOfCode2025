#pragma once

template <typename EnumType>
bool IsEnumValueValid(EnumType value)
{
	return value > EnumType::Invalid
		&& value < EnumType::Count;
}

class INonCopyable
{
public:
	INonCopyable() = default;
	~INonCopyable() = default;

private:
	INonCopyable(const INonCopyable&) = delete;
	INonCopyable& operator=(const INonCopyable&) = delete;
};

class INonMoveable
{
public:
	INonMoveable() = default;
	~INonMoveable() = default;

private:
	INonMoveable(INonMoveable&&) = delete;
	INonMoveable& operator=(INonMoveable&&) = delete;
};

class INonCopyMoveable
	: public INonCopyable
	, public INonMoveable
{
public:
	INonCopyMoveable() = default;
	~INonCopyMoveable() = default;
};

////////////////////////////////////////////////////////////////////////////////
// ================================= DEFINES ===================================
////////////////////////////////////////////////////////////////////////////////


#define _Stringify_(X) #X
#define _Stringify(X) _Stringify_(X)

#ifdef _MSC_VER
#define _DebugBreak __debugbreak()
#else
#define _DebugBreak
#endif

#define _DebugBreakInfo(_Reason)\
"Reason: " _Stringify(_Reason) \
", File: " __FILE__ \
", Line: " _Stringify(__LINE__)

#define _DebugBreakInfoMsgBox(_Reason)\
"Reason: " _Stringify(_Reason) \
"\nFile: " __FILE__ \
"\nLine: " _Stringify(__LINE__)

#define _MessageBoxError(_Text)\
UI::ShowMessageBoxOK("Error!", _Text, UI::EMessageBoxIcon::Error)

#define Assert(...)\
Log::Error(_DebugBreakInfo(__VA_ARGS__));\
_MessageBoxError(_DebugBreakInfoMsgBox(__VA_ARGS__));\
_DebugBreak

#define AssertReturnIf(_Condition, ...)		do { if (_Condition) { Assert(_Condition); return __VA_ARGS__; }} while(false)

#define Format(_Text, ...)			std::format(_Text, __VA_ARGS__)

#define ReturnIf(_Condition, ...)	if (_Condition) return __VA_ARGS__
#define BreakIf(_Condition)			if (_Condition) break
#define ContinueIf(_Condition)		if (_Condition) continue

#define AssertReturnIf(_Condition, ...)		do { if (_Condition) { Assert(_Condition); return __VA_ARGS__; }} while(false)
#define AssertBreakIf(_Condition)			do { if (_Condition) { Assert(_Condition); break; }} while(false)
#define AssertContinueIf(_Condition)		do { if (_Condition) { Assert(_Condition); continue; }} while(false)

#define SafeDelete(_Pointer)				do { if (_Pointer) { delete _Pointer; _Pointer = nullptr; }} while(false)
#define SafeDeleteArray(_Pointer)			do { if (_Pointer) { delete[] _Pointer; _Pointer = nullptr; }} while(false)

////////////////////////////////////////////////////////////////////////////////
// ================================= TYPEDEFS ==================================
////////////////////////////////////////////////////////////////////////////////

//TODO think of strong type for these values
typedef uint64_t		TimePoint;
typedef uint32_t		TimerId;

#define CREATE_STRONG_TYPE(_Name, _Type, _DefaultValue, _InvalidValue)\
class _Name\
{\
public:\
	_Name() = default;\
	~_Name() = default;\
	_Name(_Type initialValue) : value(initialValue) {};\
\
	bool operator==(const _Name& other) const { return value == other.value; }\
	bool operator!=(const _Name& other) const { return value != other.value; }\
\
	bool IsValid() const { return value != _Name::Invalid; }\
\
	static _Type Default;\
	static _Type Invalid;\
\
public:\
	_Type value = _DefaultValue;\
};\
_Type _Name::Default = _DefaultValue;\
_Type _Name::Invalid = _InvalidValue;

typedef std::vector<std::string> StringVector;

////////////////////////////////////////////////////////////////////////////////
// =============================== ENUMERATIONS ================================
////////////////////////////////////////////////////////////////////////////////

enum class EUnitOfTime
	: int8_t
{
	Invalid = -1
	, Nanosecond
	, Microsecond
	, Millisecond
	, Second
	, Minute
	, Hour
	, Day
	, Week
	, Month
	, Year
	, Count
};

enum class ETimeStringFormat
	: int8_t
{
	Invalid = -1
	, Default
	, Timestamp
	, TimePoint
	, Count
};

////////////////////////////////////////////////////////////////////////////////
// ================================= CONSTANTS =================================
////////////////////////////////////////////////////////////////////////////////

namespace Constants
{
inline constexpr int64_t TimeSecondsInMinute	= 60;
inline constexpr int64_t TimeMinutesInHour		= 60;
inline constexpr int64_t TimeHoursInDay			= 24;
inline constexpr int64_t TimeDaysInYear			= 365;

inline constexpr int64_t TimeSecondsInHour		= TimeSecondsInMinute * TimeMinutesInHour;
inline constexpr int64_t TimeSecondsInDay		= TimeSecondsInHour * TimeHoursInDay;
inline constexpr int64_t TimeSecondsInYear		= TimeSecondsInDay * TimeDaysInYear;

inline constexpr int64_t TimeMinutesInDay		= TimeMinutesInHour * TimeHoursInDay;
inline constexpr int64_t TimeMinutesInYear		= TimeMinutesInDay * TimeDaysInYear;

inline constexpr int64_t TimeHoursInYear		= TimeHoursInDay * TimeDaysInYear;

inline constexpr int64_t TimerMinInterval		= 20; // Milliseconds
} // !namespace Constants