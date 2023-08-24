#pragma once

#include <ospf/ospf_base_api.hpp>
#include <ospf/basic_definition.hpp>
#include <ospf/concepts/base.hpp>
#include <ospf/literal_constant.hpp>
#include <ospf/meta_programming/naming_system.hpp>
#include <ospf/string/split.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <locale>
#include <ranges>
#include <string>
#include <string_view>

namespace ospf
{
    inline namespace meta_programming
    {
        namespace name_transfer
        {
            template<NamingSystem system, CharType CharT>
            struct Frontend;

            template<CharType CharT>
            struct Frontend<NamingSystem::SnakeCase, CharT>
            {
                using StringType = std::basic_string<CharT>;
                using StringViewType = std::basic_string_view<CharT>;

                inline std::vector<StringViewType> operator()(const StringViewType name, const std::set<StringViewType>& abbreviations = std::set<StringViewType>{}) const noexcept
                {
                    if (name.empty())
                    {
                        return {};
                    }
                    assert(std::ranges::all_of(name, [](const CharT ch)
                        {
                            return std::isalnum(ch, std::locale{}) || ch == CharT{ '_' };
                        }));
                    return split(name, StringType{ CharT{ '_' } });
                }
            };

            template<CharType CharT>
            struct Frontend<NamingSystem::UpperSnakeCase, CharT>
                : public Frontend<NamingSystem::SnakeCase, CharT> {};

            template<CharType CharT>
            struct Frontend<NamingSystem::KebabCase, CharT>
            {
                using StringType = std::basic_string<CharT>;
                using StringViewType = std::basic_string_view<CharT>;

                inline std::vector<StringViewType> operator()(const StringViewType name, const std::set<StringViewType>& abbreviations = std::set<StringViewType>{}) const noexcept
                {
                    if (name.empty())
                    {
                        return {};
                    }
                    assert(std::ranges::all_of(name, [](const CharT ch)
                        {
                            return std::isalnum(ch, std::locale{}) || ch == CharT{ '-' };
                        }));
                    return split(name, StringType{ CharT{ '-' } });
                }
            };

            template<CharType CharT>
            struct Frontend<NamingSystem::CamelCase, CharT>
            {
                using StringType = std::basic_string<CharT>;
                using StringViewType = std::basic_string_view<CharT>;

                inline std::vector<StringViewType> operator()(const StringViewType name, const std::set<StringViewType>& abbreviations = std::set<StringViewType>{}) const noexcept
                {
                    if (name.empty())
                    {
                        return {};
                    }
                    assert(std::ranges::all_of(name, [](const CharT ch)
                        {
                            return std::isalnum(ch, std::locale{});
                        }));

                    usize p{ 0_uz }, q{ 1_uz };
                    bool flag{ std::isupper(name.front(), std::locale{}) };
                    std::vector<StringViewType> ret;
                    for (usize i{ 0_uz }; i != name.size(); ++i)
                    {
                        if (std::isupper(name[i], std::locale{}))
                        {
                            if (flag)
                            {
                                StringViewType part = name.substr(p, q - p);
                                StringType lower{ part.data(), q - p };
                                std::transform(lower.cbegin(), lower.cend(), lower.begin(), [](const CharT ch) { return std::tolower(ch, std::locale{}); });
                                if (abbreviations.contains(StringViewType{ lower }))
                                {
                                    ret.push_back(part);
                                    p = i;
                                }
                                q = i + 1_uz;
                            }
                            else
                            {
                                if ((q - p) > 1_uz && !flag)
                                {
                                    ret.push_back(name.substr(p, q - p));
                                }
                                p = i;
                                q = i + 1_uz;
                                flag = true;
                            }
                        }
                        else
                        {
                            if ((q - p) > 1_uz && flag)
                            {
                                ret.push_back(name.substr(p, q - p - 1_uz));
                                p = q - 1_uz;
                            }
                            q = i + 1_uz;
                            flag = false;
                        }
                    }
                    if (p != q)
                    {
                        ret.push_back(name.substr(p, q - p));
                    }
                    return ret;
                }
            };

            template<CharType CharT>
            struct Frontend<NamingSystem::PascalCase, CharT>
                : public Frontend<NamingSystem::CamelCase, CharT> {};

            extern template struct Frontend<NamingSystem::SnakeCase, char>;
            extern template struct Frontend<NamingSystem::SnakeCase, wchar>;

            extern template struct Frontend<NamingSystem::KebabCase, char>;
            extern template struct Frontend<NamingSystem::KebabCase, wchar>;

            extern template struct Frontend<NamingSystem::UpperSnakeCase, char>;
            extern template struct Frontend<NamingSystem::UpperSnakeCase, wchar>;

            extern template struct Frontend<NamingSystem::CamelCase, char>;
            extern template struct Frontend<NamingSystem::CamelCase, wchar>;

            extern template struct Frontend<NamingSystem::PascalCase, char>;
            extern template struct Frontend<NamingSystem::PascalCase, wchar>;
        };
    };
};
