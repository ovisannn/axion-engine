#pragma once

#include <memory>

// ---------------------------------------------------------------------------
// Platform check
// ---------------------------------------------------------------------------
#ifndef AX_PLATFORM_WINDOWS
#if !defined(AX_PLATFORM_LINUX) && !defined(AX_PLATFORM_MACOS)
#error "Axion only supports Windows, Linux, and macOS!"
#endif
#endif

// ---------------------------------------------------------------------------
// Debug break
// ---------------------------------------------------------------------------
#ifdef AX_DEBUG
#if defined(AX_PLATFORM_WINDOWS)
#define AX_DEBUGBREAK() __debugbreak()
#elif defined(AX_PLATFORM_LINUX)
#include <signal.h>
#define AX_DEBUGBREAK() raise(SIGTRAP)
#else
#define AX_DEBUGBREAK()
#endif
#define AX_ENABLE_ASSERTS
#else
#define AX_DEBUGBREAK()
#endif

// ---------------------------------------------------------------------------
// Utility macros
// ---------------------------------------------------------------------------
#define AX_EXPAND_MACRO(x) x
#define AX_STRINGIFY_MACRO(x) #x
#define BIT(x) (1 << x)

#define AX_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) \
    { return this->fn(std::forward<decltype(args)>(args)...); }

// ---------------------------------------------------------------------------
// Smart pointer aliases
// ---------------------------------------------------------------------------
namespace Axion {

    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

}