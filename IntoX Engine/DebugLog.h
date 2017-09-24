#pragma once

#include <string>


class DebugLog
{
public:
	enum Type { DEFAULT_LOG, WARNING_LOG, ERROR_LOG };
	DebugLog();
	~DebugLog();
	static void Print(std::string log, Type logType);

private:
	static void SetLogTypeColor(Type logType);
};

