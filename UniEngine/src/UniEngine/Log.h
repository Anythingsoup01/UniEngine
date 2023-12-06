#pragma once
#include "uepch.h"

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"
namespace UE {

	class UE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core Log Error Codes
#define UE_CORE_FATAL(...)      ::UE::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define UE_CORE_ERROR(...)      ::UE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define UE_CORE_WARN(...)       ::UE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define UE_CORE_INFO(...)       ::UE::Log::GetCoreLogger()->info(__VA_ARGS__)

/*#define UE_CORE_TRACE(...)      ::UE::Log::GetCoreLogger()->trace(__VA_ARGS__)*/
// Broken ^

// Client Log Error Codes
#define UE_FATAL(...)           ::UE::Log::GetClientLogger()->critical(__VA_ARGS__)
#define UE_ERROR(...)           ::UE::Log::GetClientLogger()->error(__VA_ARGS__)
#define UE_WARN(...)            ::UE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define UE_INFO(...)            ::UE::Log::GetClientLogger()->info(__VA_ARGS__)

#define UE_TRACE(...)            ::UE::Log::GetClientLogger()->trace(__VA_ARGS__)
// Broken ^


