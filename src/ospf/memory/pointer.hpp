#pragma once

#include <ospf/memory/pointer/raw.hpp>
#include <ospf/memory/pointer/unique.hpp>
#include <ospf/memory/pointer/shared.hpp>
#include <ospf/memory/pointer/weak.hpp>

namespace ospf
{
    inline namespace memory
    {
        template<typename T>
        using Ptr = std::conditional_t<
            std::is_array_v<T>,
            pointer::Ptr<ArrayType<T>, pointer::PointerCategory::Raw>,
            pointer::Ptr<OriginType<T>, pointer::PointerCategory::Raw>
        >;

        template<typename T>
        using Unique = std::conditional_t<
            std::is_array_v<T>,
            pointer::Ptr<ArrayType<T>, pointer::PointerCategory::Unique>,
            pointer::Ptr<OriginType<T>, pointer::PointerCategory::Unique>
        >;

        template<typename T>
        using Shared = std::conditional_t<
            std::is_array_v<T>,
            pointer::Ptr<ArrayType<T>, pointer::PointerCategory::Shared>,
            pointer::Ptr<OriginType<T>, pointer::PointerCategory::Shared>
        >;

        template<typename T>
        using Weak = std::conditional_t<
            std::is_array_v<T>,
            pointer::Ptr<ArrayType<T>, pointer::PointerCategory::Weak>,
            pointer::Ptr<OriginType<T>, pointer::PointerCategory::Weak>
        >;
    };
};
