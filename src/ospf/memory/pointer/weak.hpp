#pragma once

#include <ospf/memory/pointer/impl.hpp>
#include <ospf/memory/pointer/category.hpp>

namespace ospf
{
    inline namespace memory
    {
        namespace pointer
        {
            template<typename T>
            class Ptr<T, pointer::PointerCategory::Weak>
                : public pointer::PtrImpl<T, Ptr<T, pointer::PointerCategory::Weak>>
            {};
        };
    };
};
