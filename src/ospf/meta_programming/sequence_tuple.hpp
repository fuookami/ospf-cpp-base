#pragma once

#include <ospf/meta_programming/variable_type_list.hpp>
#include <ospf/type_family.hpp>

namespace ospf
{
	inline namespace meta_programming
	{
        template<typename... Elems>
        class SequenceTuple
        {
        public:
            using Types = VariableTypeList<Elems...>;

        public:
            constexpr SequenceTuple(Elems&&... elems)
                : m_tuple{ std::forward<Elems>(elems)...} {}
            constexpr SequenceTuple(const SequenceTuple& ano) = default;
            constexpr SequenceTuple(SequenceTuple&& ano) = default noexcept;
            constexpr SequenceTuple& operator=(const SequenceTuple& rhs) = default;
            constexpr SequenceTuple& operator=(SequenceTuple&& rhs) = default noexcept;
            constexpr ~SequenceTuple(void) = default;

        public:
            inline constexpr const bool empty(void) const noexcept
            {
                return Types::length == 0_uz;
            }

            template<usize i>
                requires (i < Types::length)
            inline constexpr decltype(auto) get(void) noexcept
            {
                return std::get<i>(m_tuple);
            }

            template<usize i>
                requires (i < Types::length)
            inline constexpr decltype(auto) get(void) const noexcept
            {
                return std::get<i>(m_tuple);
            }

            template<typename T, typename Pred>
            inline constexpr auto accumulate(RRefType<T> lhs, const Pred& pred) const noexcept
            {
                return accumulate<0_uz>(move<T>(lhs), pred);
            }

            template<typename Pred>
            inline constexpr void for_each(const Pred& pred) const noexcept
            {
                for_each<0_uz>(pred);
            }

            template<typename T>
            inline constexpr auto push(RRefType<T> e) const noexcept
            {
                return std::apply([e](const auto&... elems)
                    {
                        return SequenceTuple<Elems..., T>{ elems..., move<T>(e) };
                    }, m_tuple);
            }

            template<typename T>
            inline constexpr auto insert(RRefType<T> e) const noexcept
            {
                if constexpr (Types::template index<T>() == Types::npos)
                {
                    return push(move<T>(e));
                }
                else
                {
                    return *this;
                }
            }

        private:
            template<usize i, typename Pred>
            inline constexpr void for_each(const Pred& pred) const noexcept
            {
                if constexpr (i != Types::length)
                {
                    pred(std::get<i>(m_tuple));
                    for_each<i + 1_uz>(pred);
                }
            }

            template<usize i, typename T, typename Pred>
            inline constexpr auto accumulate(RRefType<T> lhs, const Pred& pred) const noexcept
            {
                if constexpr (i != Types::length)
                {
                    return accumulate<i + 1_uz>(pred(move<T>(lhs), std::get<i>(m_tuple)), pred);
                }
                else
                {
                    return lhs;
                }
            }

        private:
            std::tuple<Elems...> m_tuple;
        };
	};
};
