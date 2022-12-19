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
                SharedBorrow,
                UniqueBorrow
            };

            template<typename T, ReferenceCategory category = ReferenceCategory::Reference>
            class Ref;
        };
    };
};
