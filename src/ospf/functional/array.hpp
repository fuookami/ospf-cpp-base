#pragma once

#include <ospf/basic_definition.hpp>
#include <ospf/functional/result.hpp>
#include <ospf/type_family.hpp>

namespace ospf
{
    inline namespace functional
    {
        namespace array_detail
        {
            template<typename T, usize i, usize len, typename Func, typename... Args>
                requires requires (const Func& func) { { func(std::declval<usize>()) } -> DecaySameAs<T>; }
            inline constexpr std::array<T, len> make_array_impl(const Func& constructor, Args&&... args) noexcept
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

            template<typename T, usize i, usize len, typename Func, typename... Args>
                requires requires (const Func&& func) { { func(std::declval<usize>()) } -> DecaySameAs<Result<T>>; }
            inline constexpr Result<std::array<T, len>> try_make_array_impl(const Func& constructor, Args&&... args) noexcept
            {
                if constexpr (i == len)
                {
                    return std::array<T, len>{ std::forward<Args>(args)... };
                }
                else
                {
                    OSPF_TRY_GET(this_arg, constructor(i));
                    return try_make_array_impl<T, i + 1_uz, len>(constructor, std::forward<Args>(args)..., std::move(this_arg));
                }
            }
        };

        template<typename T, usize len, std::input_iterator It>
            requires requires (const It& it) { { *it } -> DecaySameAs<T>; }
        inline constexpr std::array<T, len> make_array(It&& it) noexcept
        {
            return array_detail::make_array_impl<T, 0_uz, len>([&it](const usize _)
                {
                    return *it;
                });
        }

        template<typename T, usize len, std::input_iterator It>
            requires requires (const It& it) { { *it } -> DecaySameAs<Result<T>>; }
        inline constexpr Result<std::array<T, len>> make_array(It&& it) noexcept
        {
            return array_detail::try_make_array_impl<T, 0_uz, len>([&it](const usize _)
                {
                    return *it;
                });
        }

        template<typename T, usize len, typename Func>
            requires requires (const Func& func) { { func(std::declval<usize>()) } -> DecaySameAs<T>; }
        inline constexpr std::array<T, len> make_array(const Func& constructor) noexcept
        {
            return array_detail::make_array_impl<T, 0_uz, len>(constructor);
        }

        template<typename T, usize len, typename Func>
            requires requires (const Func&& func) { { func(std::declval<usize>()) } -> DecaySameAs<Result<T>>; }
        inline constexpr Result<std::array<T, len>> make_array(const Func& constructor) noexcept
        {
            return array_detail::try_make_array_impl<T, 0_uz, len>(constructor);
        }

        template<typename T, usize len>
            requires std::copyable<T>
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
