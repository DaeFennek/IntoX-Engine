#include "DebugLog.h"
#include <iostream>

#ifdef _WIN32 || _WIN64
#include <Windows.h>
#endif

#define LOG_COLOR 15
#define WARNING_COLOR 14
#define ERROR_COLOR 12

DebugLog::DebugLog() {}

DebugLog::~DebugLog() {}

void DebugLog::Print(std::string log, Type logType)
{
	SetLogTypeColor(logType);
	std::cout << "IntoX Engine: " << log << std::endl;
}

void DebugLog::SetLogTypeColor(Type logType)
{
#ifdef _WIN32

	WORD wColor;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;	

	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		int color;
		switch (logType)
		{
			case Type::DEFAULT_LOG:
				color = LOG_COLOR;
				break;
			case Type::WARNING_LOG:
				color = WARNING_COLOR;
				break;
			case Type::ERROR_LOG:
				color = ERROR_COLOR;
				break;		
		}
		
		wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}	
#endif

}
