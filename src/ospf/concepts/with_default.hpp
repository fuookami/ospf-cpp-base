#pragma once

#include <ospf/concepts.hpp>
#include <concepts>

namespace ospf
{
    inline namespace concepts
    {
        template<std::copy_constructible T>
        struct DefaultValue {};

        template<std::copy_constructible T>
            requires std::default_initializable<T>
        struct DefaultValue<T>
        {
            static constexpr const T value = T{};
        };

        template<typename T>
        concept WithDefault = requires
        {
            { DefaultValue<T>::value } -> DecaySameAs<T>;
        };
    };
};
