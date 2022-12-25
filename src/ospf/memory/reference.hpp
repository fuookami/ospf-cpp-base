#pragma once

#include <ospf/memory/reference/raw.hpp>
#include <ospf/memory/reference/borrow.hpp>
#include <ospf/memory/reference/unique_borrow.hpp>

namespace ospf
{
    inline namespace memory
    {
        template<typename T>
        using Ref = reference::Ref<OriginType<T>, reference::ReferenceCategory::Reference>;

        template<typename T>
        using Borrow = reference::Ref<OriginType<T>, reference::ReferenceCategory::Borrow>;

        template<typename T>
        using UniqueBorrow = reference::Ref<OriginType<T>, reference::ReferenceCategory::UniqueBorrow>;
    };
};
