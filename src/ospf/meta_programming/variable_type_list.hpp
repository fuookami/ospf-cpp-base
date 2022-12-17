#pragma once

#include <ospf/basic_definition.hpp>
#include <ospf/literal_constant.hpp>

namespace ospf
{
    inline namespace meta_programming
    {
        namespace variable_type_list
        {
            template<typename T>
            inline static constexpr const usize type_index(void) noexcept
            {
                return 0_uz;
            }

            template<typename T>
            inline static constexpr const usize strict_type_index(void) noexcept
            {
                return 0_uz;
            }

            template<typename T, typename U, typename... Types>
            inline static constexpr const usize type_index(void) noexcept
            {
                using T1 = std::decay_t<T>;
                using T2 = std::decay_t<U>;
                return std::is_same_v<T1, T2> || std::is_base_of_v<T2, T1> || std::is_convertible_v<T2, T1>
                    ? 0_uz
                    : type_index<T, Types...>() + 1_uz;
            }

            template<typename T, typename U, typename... Types>
            inline static constexpr const usize strict_type_index(void) noexcept
            {
                using T1 = std::decay_t<T>;
                using T2 = std::decay_t<U>;
                return std::is_same_v<T1, T2> || std::is_base_of_v<T2, T1>
                    ? 0_uz
                    : strict_type_index<T, Types...>() + 1_uz;
            }

            template<usize i, typename... Types>
            struct TypeAt;

            template<usize i, typename T, typename... Types>
                requires (i > 0_uz)
            struct TypeAt<i, T, Types...>
            {
                using Type = typename TypeAt<i - 1_uz, Types...>::Type;
            };

            template<typename T, typename... Types>
            struct TypeAt<0_uz, T, Types...>
            {
                using Type = T;
            };

            template<typename T>
            struct TypeAt<0_uz, T>
            {
                using Type = T;
            };

            static constexpr const usize npos = (std::numeric_limits<usize>::max)();

            template<typename T, typename... Types>
            inline static constexpr const usize index(const usize length) noexcept
            {
                constexpr auto i = variable_type_list::type_index<T, Types...>();
                return i < length ? i : npos;
            }

            template<typename T, typename... Types>
            inline static constexpr const usize strict_index(const usize length) noexcept
            {
                constexpr auto i = variable_type_list::strict_type_index<T, Types_...>();
                return i < length ? i : npos;
            }
        };

        template<typename... Types>
        struct VariableTypeList
        {
            static constexpr const usize npos = variable_type_list::npos;
            static constexpr const usize length = sizeof...(Types);

            template<usize index>
            using At = std::enable_if_t<(index < length),
                typename variable_type_list::TypeAt<index, Types...>::Type
            >;

            template<typename T>
            static constexpr const usize index = variable_type_list::index(length);

            template<typename T>
            static constexpr const usize strict_index = variable_type_list::strict_index(length);
        };

        template<usize index, typename... Types>
        using TypeAt = typename VariableTypeList<Types...>::template At<index>;

        template<typename T, typename... Types>
        static constexpr const usize type_index = VariableTypeList<Types...>::template index<T>;

        template<typename T, typename... Types>
        static constexpr const usize strict_type_index = VariableTypeList<Types...>::template strict_index<T>;
    };
};
