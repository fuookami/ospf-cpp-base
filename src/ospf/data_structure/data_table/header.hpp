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
                DataTableHeader(void)
                    : _name(""), _type(std::nullopt) {}

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

                inline const bool empty(void) const noexcept
                {
                    return !_type.has_value();
                }

                inline const bool signle_type(void) const
                {
                    return (*_type).is_left();
                }

                inline const bool multi_type(void) const
                {
                    return (*_type).is_right();
                }

                template<typename T>
                inline const bool is(void) const
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
                        }, *_type);
                }

                inline const bool is(const std::type_index target_type) const
                {
                    return std::visit([target_type](const auto& type)
                        {
                            if constexpr (DecaySameAs<decltype(type), std::type_index>)
                            {
                                return target_type == type;
                            }
                            else
                            {
                                return false;
                            }
                        }, *_type);
                }

                template<typename T>
                inline const bool contains(void) const
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
                        }, *_type);
                }

                inline const bool contains(const std::type_index target_type) const
                {
                    return std::visit([target_type](const auto& types)
                        {
                            if constexpr (DecaySameAs<decltype(types), std::set<std::type_index>>)
                            {
                                return types.contains(target_type);
                            }
                            else
                            {
                                return false;
                            }
                        }, *_type);
                }

                template<typename T>
                inline const bool matched(void) const
                {
                    return std::visit([](const auto& type)
                        {
                            if constexpr (DecaySameAs<decltype(type), std::type_index>)
                            {
                                return TypeInfo<T>::index() == type;
                            }
                            else if constexpr (DecaySameAs<decltype(type), std::set<std::type_index>>)
                            {
                                return type.contains(TypeInfo<T>::index());
                            }
                            else
                            {
                                return false;
                            }
                        }, *_type);
                }

                inline const bool matched(const std::type_index target_type) const
                {
                    return std::visit([target_type](const auto& type)
                        {
                            if constexpr (DecaySameAs<decltype(type), std::type_index>)
                            {
                                return target_type == type;
                            }
                            else if constexpr (DecaySameAs<decltype(type), std::set<std::type_index>>)
                            {
                                return type.contains(target_type);
                            }
                            else
                            {
                                return false;
                            }
                        }, *_type);
                }

            public:
                inline std::string to_string(void) const noexcept
                {
                    if (_type.has_value())
                    {
                        return std::visit([this](const auto& type) -> std::string
                            {
                                if constexpr (DecaySameAs<decltype(type), std::type_index>)
                                {
                                    return std::format("{}({})", this->name(), type_name(type));
                                }
                                else if constexpr (DecaySameAs<decltype(type), std::set<std::type_index>>)
                                {
                                    if (type.empty())
                                    {
                                        return this->_name;
                                    }
                                    else if (type.size() == 1_uz)
                                    {
                                        return std::format("{}({})", this->name(), type_name(*type.begin()));
                                    }
                                    else
                                    {
                                        return std::format("{}({}...)", this->name(), type_name(*type.begin()));
                                    }
                                }
                                else
                                {
                                    return "";
                                }
                            }, *_type);
                    }
                    else
                    {
                        return "";
                    }
                }

            public:
                inline void clear(void) noexcept
                {
                    _name.assign("");
                    _type = std::nullopt;
                }

            private:
                std::string _name;
                std::optional<Either> _type;
            };
        };
    };
};

namespace std
{
    inline std::string to_string(const ospf::data_table::DataTableHeader& header) noexcept
    {
        return header.to_string();
    }

    template<typename CharT>
    struct formatter<ospf::data_table::DataTableHeader, CharT>
        : public formatter<string_view, CharT>
    {
        template<typename FormatContext>
        inline decltype(auto) format(const ospf::data_table::DataTableHeader& value, FormatContext& fc)
        {
            static const auto _formatter = formatter<string_view, CharT>{};
            return _formatter.format(value.to_string(), fc);
        }
    };
};
