workspace "UniversalEngine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "UniEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "UniEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "UniEngine/vendor/imgui"
IncludeDir["glm"] = "UniEngine/vendor/glm"
IncludeDir["stb_image"] = "UniEngine/vendor/stb_image"

group "Dependencies"
	include "UniEngine/vendor/GLFW"
	include "UniEngine/vendor/Glad"
	include "UniEngine/vendor/imgui"

project "UniEngine"
	location "UniEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "uepch.h"
	pchsource "UniEngine/src/uepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"UE_PLATFORM_WINDOWS",
			"UE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "UE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "UE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "UE_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"UniEngine/vendor/spdlog/include",
		"UniEngine/src",
		"UniEngine/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"UniEngine"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"UE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "UE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "UE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "UE_DIST"
		runtime "Release"
		optimize "on"