workspace "gameEngineTest"
	architecture "x64"
	startproject "Sandbox"

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
IncludeDir["Glad"] = "gameEngineTest/vendor/Glad/include"
IncludeDir["ImGui"] = "gameEngineTest/vendor/imgui"

--Add another project by premake5.lua
include "gameEngineTest/vendor/GLFW"
include "gameEngineTest/vendor/Glad"
include "gameEngineTest/vendor/imgui"


project "gameEngineTest"
	location "gameEngineTest"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}
	
	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "10.0.17763.0"

		defines
		{
			"EG_PLATFORM_WINDOWS",
			"EG_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "EG_DEBUG"
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Release"
		defines "EG_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "EG_DIST"
		runtime "Release"
		optimize "On"
	
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		systemversion "10.0.17763.0"

		defines
		{
			"EG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "EG_DEBUG"
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Release"
		defines "EG_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "EG_DIST"
		runtime "Release"
		optimize "On"