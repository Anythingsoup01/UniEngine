#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace UE {

	class UE_API Log
	{
	public:
		static void Init();

		inline static Reference<spdlog::logger>& GetCoreLogger() { return l_CoreLogger; }
		inline static Reference<spdlog::logger>& GetClientLogger() { return l_ClientLogger; }
	private:
		static Reference<spdlog::logger> l_CoreLogger;
		static Reference<spdlog::logger> l_ClientLogger;
	};

}

// Core log macros
#define UE_CORE_TRACE(...)    ::UE::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define UE_CORE_INFO(...)     ::UE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define UE_CORE_WARN(...)     ::UE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define UE_CORE_ERROR(...)    ::UE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define UE_CORE_FATAL(...)    ::UE::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define UE_TRACE(...)	      ::UE::Log::GetClientLogger()->trace(__VA_ARGS__)
#define UE_INFO(...)	      ::UE::Log::GetClientLogger()->info(__VA_ARGS__)
#define UE_WARN(...)	      ::UE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define UE_ERROR(...)	      ::UE::Log::GetClientLogger()->error(__VA_ARGS__)
#define UE_FATAL(...)	      ::UE::Log::GetClientLogger()->fatal(__VA_ARGS__)