workspace "LearnOpenGL"
    architecture "x64"
	startproject "LearnOpenGL"
    configurations { "Debug", "Release"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "LearnOpenGL/vendor/GLFW/include"
IncludeDir["Glad"] = "LearnOpenGL/vendor/Glad/include"
IncludeDir["glm"] = "LearnOpenGL/vendor/glm"
IncludeDir["ImGui"] = "LearnOpenGL/vendor/imgui"
IncludeDir["stb_image"] = "LearnOpenGL/vendor/stb_image"
IncludeDir["assimp"] = "LearnOpenGL/vendor/assimp"

group "Dependency"
    include "LearnOpenGL/vendor/GLFW"
    include "LearnOpenGL/vendor/Glad"
    include "LearnOpenGL/vendor/imgui"

group ""

project "LearnOpenGL"
    location "LearnOpenGL"
    kind "ConsoleApp"
    language "C++"
	cppdialect "C++17"
	staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "pch.h"
	pchsource "LearnOpenGL/src/pch.cpp"
	
    files { 
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
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
		"%{IncludeDir.glm}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.assimp}",
    }
	
	libdirs
    {
        "%{prj.name}/vendor/assimp",
    }

    links 
    {
        "GLFW",
        "Glad",
        "ImGui",
        "assimp-vc143-mtd.lib",
        "opengl32.lib",
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "LGL_DEBUG"
		runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "LGL_RELEASE"
		runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "LGL_DIST"
		runtime "Release"
        optimize "on"
