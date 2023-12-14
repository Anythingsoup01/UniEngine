#pragma once

#include <memory>

#ifdef _WIN32

	#ifdef _WIN64
	
		#define UE_PLATFORM_WINDOWS
	
	#else
	
		#error "x86 Builds are not supported!"
	
	#endif
	
#elif defined(__APPLE__) || defined(__MACH__)
	
	#inclide <TargetConditionals.h>
	
	#if TARGET_IPHONE_SIMULATOR == 1
	
		#error "IOS Simulator is not supported!"
	
	#elif TARGET_OS_IPHONE == 1
	
		#define UE_PLATFORM_IOS
		#error "IOS is not supported!"
	
	#elif TARGET_OS_MAC == 1
	
		#define UE_PLATFORM_MACOS
		#error "MacOS is not supported!"
	
	#else
	
		#error "Unknown Apple platform!"
	
	#endif 
	
#elif defined(__ANDROID__)
	
		#define UE_PLATFORM_ANDROID
		#error "Android is not supported!"
	
#elif defined(__LINUX__)
	
		#define UE_PLATFORM_LINUX
		#error "Linux is not supported!"

#endif

#ifdef UE_PLATFORM_WINDOWS
	#if UE_DYNAMIC_LINK
		#ifdef UE_BUILD_DLL
			#define UE_API __declspec(dllexport)
		#else
			#define UE_API __declspec(dllimport)
		#endif
	#else
	    #define UE_API
	#endif
#else
	#error UniEngine only supports Windows!
#endif

#ifdef UE_DEBUG
	#define UE_ENABLE_ASSERTS
#endif

#ifdef UE_ENABLE_ASSERTS
	#define UE_ASSERT(x, ...) { if(!(x)) { UE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define UE_CORE_ASSERT(x, ...) { if(!(x)) { UE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define UE_ASSERT(x, ...)
	#define UE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define UE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace UE {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Reference = std::shared_ptr<T>;
}