#pragma once
namespace UE {
	class Core
	{
	};
}

#ifdef UE_PLATFORM_WINDOWS
	#ifdef UE_BUILD_DLL
		#define UE_API _declspec(dllexport)
	#else 
		#define UE_API _declspec(dllimport)
	#endif // UE_BUILD_DLL
#endif // UE_PLATFORM_WINDOWS

#ifdef UE_ENABLE_ASSERTS
#define UE_ASSERT(x, ...) { if(!(x)) { UE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define UE_CORE_ASSERT(x, ...) { if(!(x)) { UE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define UE_ASSERT(x, ...)
#define UE_CORE_ASSERT(x, ...)
#endif

#define UE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)


#define BIT(x) (1 << x)


