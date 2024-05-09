#pragma once

#include "Core/Base.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace LGL
{
    class Log
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

#define LGL_CORE_TRACE(...)      ::LGL::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LGL_CORE_INFO(...)       ::LGL::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LGL_CORE_WARN(...)       ::LGL::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LGL_CORE_ERROR(...)      ::LGL::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LGL_CORE_CRITICAL(...)   ::LGL::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define LGL_TRACE(...)       ::LGL::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LGL_INFO(...)        ::LGL::Log::GetClientLogger()->info(__VA_ARGS__)
#define LGL_WARN(...)        ::LGL::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LGL_ERROR(...)       ::LGL::Log::GetClientLogger()->error(__VA_ARGS__)
#define LGL_CRITICAL(...)    ::LGL::Log::GetClientLogger()->critical(__VA_ARGS__)
