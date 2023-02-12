#pragma once

#include <ospf/basic_definition.hpp>
#include <ospf/type_family.hpp>

namespace ospf
{
    inline namespace functional
    {
        namespace array_detail
        {
            template<typename T, usize i, usize len, typename... Args>
            inline constexpr std::array<T, len> make_array_impl(const std::function<T(const usize)>& constructor, Args&&... args) noexcept
            {
                if constexpr (i == len)
                {
                    return std::array<T, len>{ std::forward<Args>(args)... };
                }
                else
                {
                    return make_array_impl<T, i + 1_uz, len>(constructor, std::forward<Args>(args)..., constructor(i));
                }
            }
        };

        template<typename T, usize len>
        inline constexpr std::array<T, len> make_array(const std::function<T(const usize)>& constructor) noexcept
        {
            return array_detail::make_array_impl<T, 0_uz, len>(constructor);
        }

        template<typename T, usize len>
            requires std::copy_constructible<T>
        inline constexpr std::array<T, len> make_array(ArgCLRefType<T> value) noexcept
        {
            if constexpr (CopyFaster<T>)
            {
                return array_detail::make_array_impl<T, 0_uz, len>(
                    [value](const usize _)
                    {
                        return value;
                    });
            }
            else
            {
                return array_detail::make_array_impl<T, 0_uz, len>(
                    [&value](const usize _)
                    {
                        return value;
                    });
            }
        }
    };
};
