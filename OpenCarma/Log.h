#pragma once
#include "Common/Singleton.h"

namespace OpenCarma
{
	class Log : public Commons::Singleton<Log>
	{
	public:
		enum LOG_LEVEL		
		{
			LOG_DEBUG,
			LOG_INFO,
			LOG_WARNINIG,
			LOG_ERROR,
			LOG_FATAL,
		};

	public:
		Log();
		~Log();

		void log(LOG_LEVEL level, const char* fmt, ...);
	};
}

#define LOG_STRING(level, fmt, ...) Log::getInstance().log(level, fmt, ##__VA_ARGS__)

#ifdef _DEBUG // TODO: check with other compilers
#	define LOG_DEBUG(fmt, ...) LOG_STRING(Log::LOG_DEBUG, fmt, ##__VA_ARGS__)
#else
#	define LOG_DEBUG(fmt, ...)
#endif
#define LOG_INFO(fmt, ...) LOG_STRING(Log::LOG_INFO, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) LOG_STRING(Log::LOG_WARNINIG, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) LOG_STRING(Log::LOG_ERROR, fmt, ##__VA_ARGS__)
#define LOG_FATAL(fmt, ...) LOG_STRING(Log::LOG_FATAL, fmt, ##__VA_ARGS__)