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

template<typename T, typename U, ospf::reference::ReferenceCategory category1, ospf::reference::ReferenceCategory category2>
inline constexpr ospf::RetType<std::compare_three_way_result_t<T, U>> operator<=>(const std::optional<ospf::reference::Ref<T, category1>>& lhs, const std::optional<ospf::reference::Ref<U, category2>>& rhs) noexcept
{
    if (static_cast<bool>(lhs) && static_cast<bool>(rhs))
    {
        return **lhs <=> **rhs;
    }
    else
    {
        return static_cast<bool>(lhs) <=> static_cast<bool>(rhs);
    }
}

template<typename T, typename U, ospf::reference::ReferenceCategory category1, ospf::reference::ReferenceCategory category2>
inline constexpr ospf::RetType<std::compare_three_way_result_t<T, U>> operator<=>(const std::optional<const ospf::reference::Ref<T, category1>>& lhs, const std::optional<const ospf::reference::Ref<U, category2>>& rhs) noexcept
{
    if (static_cast<bool>(lhs) && static_cast<bool>(rhs))
    {
        return **lhs <=> **rhs;
    }
    else
    {
        return static_cast<bool>(lhs) <=> static_cast<bool>(rhs);
    }
}
