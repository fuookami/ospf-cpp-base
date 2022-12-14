#pragma once

#include <magic_enum.hpp>
#include <type_traits>
#include <format>

namespace ospf
{
    inline namespace concepts
    {
        template<typename T>
        concept EnumType = std::is_enum_v<T>;

        template<EnumType T>
        inline constexpr const std::string_view to_string(const T value) noexcept
        {
            return magic_enum::enum_name<T>(value);
        }

        template<typename T, typename U>
        concept NotSameAs = !std::is_same_v<T, U>;

        template<typename T, typename U>
        struct IsDecaySameAs
        {
            static constexpr const bool value = std::is_same_v<std::decay_t<T>, std::decay_t<U>>;
        };

        template<typename T, typename U>
        static constexpr const bool is_decay_same_as = IsDecaySameAs<T, U>::value;

        template<typename T, typename U>
        concept DecaySameAs = is_decay_same_as<T, U>;
    };
};

namespace std
{
    template<ospf::EnumType T, typename CharT>
    struct formatter<T, CharT> : formatter<string_view, CharT>
    {
        template<typename FormatContext>
        inline static decltype(auto) format(const T value, FormatContext& fc)
        {
            return formatter<string_view, CharT>::format(ospf::to_string(value), fc);
        }
    };
};
