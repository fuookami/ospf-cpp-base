#pragma once

#include <ospf/type_family.hpp>
#include <ospf/concepts/base.hpp>

namespace ospf
{
    inline namespace concepts
    {
        template<typename T>
        struct TagValue {};

        template<typename T>
        concept WithTag = requires(const T& ele)
        {
            { TagValue<T>::value(ele) } -> DecaySameAs<typename TagValue<T>::Type>;
        };
    };
};
