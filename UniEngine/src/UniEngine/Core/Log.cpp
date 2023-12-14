#include "uepch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace UE {

	Referance<spdlog::logger> Log::l_CoreLogger;
	Referance<spdlog::logger> Log::l_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		l_CoreLogger = spdlog::stdout_color_mt("HAZEL");
		l_CoreLogger->set_level(spdlog::level::trace);

		l_ClientLogger = spdlog::stdout_color_mt("APP");
		l_ClientLogger->set_level(spdlog::level::trace);
	}

}