#pragma once

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