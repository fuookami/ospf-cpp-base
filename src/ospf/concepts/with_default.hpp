#pragma once

#include <ospf/concepts.hpp>
#include <concepts>

namespace ospf
{
    inline namespace concepts
    {
        template<typename T>
        struct DefaultValue {};

        template<typename T>
        concept WithDefault = requires
        {
            { DefaultValue<T>::value } -> DecaySameAs<T>;
        };
    };
};
