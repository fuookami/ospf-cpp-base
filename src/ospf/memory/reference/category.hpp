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

            template<typename T, ReferenceCategory category = ReferenceCategory::Reference>
            class Ref;
        };
    };
};
