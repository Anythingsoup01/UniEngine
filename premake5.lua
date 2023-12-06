workspace "UniversalEngine"
	architecture "x64"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "UniEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "UniEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "UniEngine/vendor/ImGui"
IncludeDir["glm"] = "UniEngine/vendor/glm"

include "UniEngine/vendor/GLFW"
include "UniEngine/vendor/GLAD"
include "UniEngine/vendor/ImGui"

project "UniEngine"
	location "UniEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "uepch.h"
	pchsource "UniEngine/src/uepch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links {
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
		"dwmapi.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"UE_PLATFORM_WINDOWS",
			"UE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines 
		{ 
			"UE_DEBUG",
			"UE_ENABLE_ASSERTS"
		}
		symbols "On"

	filter "configurations:Release"
		defines "UE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "UE_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"UniEngine/vendor/spdlog/include",
		"UniEngine/src",
		"%{IncludeDir.glm}"
	}

	links {
		"UniEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"UE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "UE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "UE_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "UE_DIST"
		symbols "On"