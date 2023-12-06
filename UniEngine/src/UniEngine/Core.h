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

#define BIT(x) (1 << x)


