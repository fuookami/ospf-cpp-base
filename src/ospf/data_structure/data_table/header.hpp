#pragma once

#include <ospf/functional/either.hpp>
#include <ospf/meta_programming/type_info.hpp>
#include <set>

namespace ospf
{
    inline namespace data_structure
    {
        namespace data_table
        {
            class DataTableHeader
            {
                using Either = functional::Either<std::type_index, std::set<std::type_index>>;

            public:
                DataTableHeader(std::string name, const std::type_index type)
                    : _name(std::move(name)), _type(Either::left(type)) {}

                DataTableHeader(std::string name, std::set<std::type_index> type)
                    : _name(std::move(name)), _type(Either::right(std::move(type))) {}
                
                template<std::forward_iterator It>
                    requires requires (const It& it) { { *it } -> DecaySameAs<std::type_index>; }
                DataTableHeader(std::string name, It&& first, It&& last)
                    : DataTableHeader(std::move(name), std::set<std::type_index>{ std::forward<It>(first), std::forward<It>(last) }) {}

                template<std::ranges::range R>
                DataTableHeader(std::string name, const R& r)
                    : DataTableHeader(std::move(name), std::set<std::type_index>{ std::ranges::begin(r), std::ranges::end(r) }) {}

            public:
                DataTableHeader(const DataTableHeader& ano) = default;
                DataTableHeader(DataTableHeader&& ano) noexcept = default;
                DataTableHeader& operator=(const DataTableHeader& rhs) = default;
                DataTableHeader& operator=(DataTableHeader&& rhs) noexcept = default;
                ~DataTableHeader(void) = default;

            public:
                inline const std::string_view name(void) const noexcept
                {
                    return _name;
                }

                inline const bool signle_type(void) const noexcept
                {
                    return _type.is_left();
                }

                inline const bool multi_type(void) const noexcept
                {
                    return _type.is_right();
                }

                template<typename T>
                inline const bool is(void) const noexcept
                {
                    return std::visit([](const auto& type)
                        {
                            if constexpr (DecaySameAs<decltype(type), std::type_index>)
                            {
                                return TypeInfo<T>::index() == type;
                            }
                            else
                            {
                                return false;
                            }
                        }, _type);
                }

                template<typename T>
                inline const bool contains(void) const noexcept
                {
                    return std::visit([](const auto& types)
                        {
                            if constexpr (DecaySameAs<decltype(types), std::set<std::type_index>>)
                            {
                                return types.contains(TypeInfo<T>::index());
                            }
                            else
                            {
                                return false;
                            }
                        }, _type);
                }

            private:
                std::string _name;
                Either _type;
            };
        };
    };
};
