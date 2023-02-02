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

        template<typename T, typename... Args>
        struct IsDecaySameAs;

        template<typename T, typename U>
        struct IsDecaySameAs<T, U>
        {
            static constexpr const bool value = std::is_same_v<std::decay_t<T>, std::decay_t<U>>;
        };

        template<typename T, typename U, typename... Args>
        struct IsDecaySameAs<T, U, Args...>
        {
            static constexpr const bool value = IsDecaySameAs<T, U>::value || IsDecaySameAs<T, Args...>::value;
        };

        template<typename T, typename... Args>
        static constexpr const bool is_decay_same_as = IsDecaySameAs<T, Args...>::value;

        template<typename T, typename... Args>
        concept DecaySameAs = is_decay_same_as<T, Args...>;

        template<typename T, typename... Args>
        concept DecayNotSameAs = !is_decay_same_as<T, Args...>;
    };
};

namespace std
{
    template<ospf::EnumType T>
    inline const std::string_view to_string(const T value) noexcept
    {
        return ospf::to_string(value);
    }

    template<ospf::EnumType T, typename CharT>
    struct formatter<T, CharT> 
        : public formatter<string_view, CharT>
    {
        template<typename FormatContext>
        inline static decltype(auto) format(const T value, FormatContext& fc)
        {
            return formatter<string_view, CharT>::format(ospf::to_string(value), fc);
        }
    };
};
