workspace "gameEngineTest"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Include directories relative to root folser (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "gameEngineTest/vendor/GLFW/include"

--Add another project by premake5.lua
include "gameEngineTest/vendor/GLFW"

project "gameEngineTest"
	location "gameEngineTest"
	kind "SharedLib"
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	--Set precompile header
	pchheader "egpch.h"
	pchsource "gameEngineTest/src/egpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}
	
	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.17763.0"

		defines
		{
			"EG_PLATFORM_WINDOWS",
			"EG_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "EG_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "EG_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "EG_DIST"
		optimize "On"
	
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs 
	{
		"gameEngineTest/vendor/spdlog/include",
		"gameEngineTest/src"
	}

	links
	{
		"gameEngineTest"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "10.0.17763.0"

		defines
		{
			"EG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "EG_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "EG_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "EG_DIST"
		optimize "On"