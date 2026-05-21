#include "axpch.h"
#include "Axion/Core/Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Axion {

    Ref<spdlog::logger> Log::s_CoreLogger;
    Ref<spdlog::logger> Log::s_ClientLogger;

    void Log::Init() {
        // Pattern: [HH:MM:SS.ms] LoggerName: message
        spdlog::set_pattern("%^[%T.%e] %n: %v%$");

        s_CoreLogger = spdlog::stdout_color_mt("AXION");
        s_CoreLogger->set_level(spdlog::level::trace);

        s_ClientLogger = spdlog::stdout_color_mt("APP");
        s_ClientLogger->set_level(spdlog::level::trace);
    }

}