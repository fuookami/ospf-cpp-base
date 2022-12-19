#pragma once

#include <ospf/basic_definition.hpp>

namespace ospf
{
    inline namespace memory
    {
        namespace pointer
        {
            enum class PointerCategory : u8
            {
                Unique,
                Shared,
                Weak,
                Raw
            };

            template<typename T, PointerCategory category = PointerCategory::Raw>
            class Ptr;
        };
    };
};

namespace std
{
    template<typename T, ospf::memory::pointer::PointerCategory category>
        requires requires(ospf::memory::pointer::Ptr<T, category>& lhs, ospf::memory::pointer::Ptr<T, category>& rhs) { lhs.swap(rhs); }
    inline void swap(ospf::memory::pointer::Ptr<T, category>& lhs, ospf::memory::pointer::Ptr<T, category>& rhs) noexcept
    {
        lhs.swap(rhs);
    }
};
