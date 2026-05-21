#pragma once

#include "Axion/Core/Base.h"

// Silence spdlog warnings on MSVC
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Axion {

    class Log {
    public:
        static void Init();

        static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

    private:
        static Ref<spdlog::logger> s_CoreLogger;
        static Ref<spdlog::logger> s_ClientLogger;
    };

}

// ---------------------------------------------------------------------------
// Engine-side logging macros (use in Axion engine code)
// ---------------------------------------------------------------------------
#define AX_CORE_TRACE(...)    ::Axion::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define AX_CORE_INFO(...)     ::Axion::Log::GetCoreLogger()->info(__VA_ARGS__)
#define AX_CORE_WARN(...)     ::Axion::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AX_CORE_ERROR(...)    ::Axion::Log::GetCoreLogger()->error(__VA_ARGS__)
#define AX_CORE_CRITICAL(...) ::Axion::Log::GetCoreLogger()->critical(__VA_ARGS__)

// ---------------------------------------------------------------------------
// Client-side logging macros (use in Sandbox / game code)
// ---------------------------------------------------------------------------
#define AX_TRACE(...)    ::Axion::Log::GetClientLogger()->trace(__VA_ARGS__)
#define AX_INFO(...)     ::Axion::Log::GetClientLogger()->info(__VA_ARGS__)
#define AX_WARN(...)     ::Axion::Log::GetClientLogger()->warn(__VA_ARGS__)
#define AX_ERROR(...)    ::Axion::Log::GetClientLogger()->error(__VA_ARGS__)
#define AX_CRITICAL(...) ::Axion::Log::GetClientLogger()->critical(__VA_ARGS__)