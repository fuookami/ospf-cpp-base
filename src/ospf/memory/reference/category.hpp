#pragma once

#include <ospf/basic_definition.hpp>

namespace ospf
{
    inline namespace memory
    {
        namespace reference
        {
            enum class ReferenceCategory : u8
            {
                Reference,      // not null pointer
                Borrow,
                UniqueBorrow
            };

            template<typename T, ReferenceCategory cat = ReferenceCategory::Reference>
            class Ref;
        };
    };
};

namespace std
{
    template<typename T, ospf::reference::ReferenceCategory cat>
        requires requires(ospf::reference::Ref<T, cat>& lhs, ospf::reference::Ref<T, cat>& rhs) { lhs.swap(rhs); }
    inline void swap(ospf::reference::Ref<T, cat>& lhs, ospf::reference::Ref<T, cat>& rhs) noexcept
    {
        lhs.swap(rhs);
    }
};

