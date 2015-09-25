#include <Log.h>
#include <cstdio>
#include <stdint.h>
#include <stdarg.h>


// TODO: log4cplus backend?
namespace OpenCarma
{
	// For buffer output:
	//static const uint32_t MAX_LINE = 1024;
	//char buffer[MAX_LINE];
	//vsprintf(buffer, fmt, args);

	Log::Log()
	{
	}


	Log::~Log()
	{
	}

	static char* TranslateLogLevel(Log::LOG_LEVEL level)
	{
		switch (level)
		{
		case Log::LOG_DEBUG:
			return "D:";
		case Log::LOG_INFO:
			return "I:";
		case Log::LOG_WARNINIG:
			return "W:";
		case Log::LOG_ERROR:
			return "E:";
		case Log::LOG_FATAL:
			return "F:";
		default:
			return "";
		}
	}

	void Log::log(LOG_LEVEL level, const char* fmt, ...)
	{		
		// Simple stdout backend:
		va_list args;
		va_start(args, fmt);
		printf(TranslateLogLevel(level));
		vprintf(fmt, args);
		printf("\n");
		va_end(args);
	}
}