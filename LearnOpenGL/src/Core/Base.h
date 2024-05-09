#pragma once

#include <memory>

#ifdef LGL_DEBUG
    #define LGL_ENABLE_ASSERTS
#endif

#ifdef LGL_ENABLE_ASSERTS
    #define LGL_ASSERT(x, ...) { if(!(x)) { LGL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define LGL_CORE_ASSERT(x, ...) { if(!(x)) { LGL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define LGL_ASSERT(x, ...)
    #define LGL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define LGL_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace LGL {

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}