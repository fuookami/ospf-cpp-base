#pragma once

#include <ospf/ospf_base_api.hpp>
#include <ospf/basic_definition.hpp>
#include <ospf/literal_constant.hpp>
#include <ospf/meta_programming/naming_system.hpp>
#include <locale>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

namespace ospf
{
    inline namespace meta_programming
    {
        namespace name_transfer
        {
            // todo: impl abbreviations list for splitting

            template<NamingSystem system, CharType CharT>
            struct Frontend;

            template<CharType CharT>
            struct Frontend<NamingSystem::Underscore, CharT>
            {
                using StringType = std::basic_string<CharT>;
                using StringViewType = std::basic_string_view<CharT>;

                inline std::vector<StringViewType> operator()(const StringViewType name) const noexcept
                {
                    if (name.empty())
                    {
                        return {};
                    }
                    assert(std::ranges::all_of(name, [](const CharT ch)
                        {
                            return std::isalnum(ch, std::locale{}) || ch == CharT{ '_' };
                        }));

                    usize p{ 0_uz }, q{ 1_uz };
                    bool flag{ name.front() == CharT{ '_' } };
                    std::vector<StringViewType> ret;
                    for (usize i{ 0_uz }; i != name.size(); ++i)
                    {
                        if (name[i] == '_')
                        {
                            if (p != q && !flag)
                            {
                                ret.push_back(name.substr(p, q - p));
                            }
                            p = q = i + 1_uz;
                            flag = true;
                        }
                        else if (flag)
                        {
                            p = i;
                            q = i + 1_uz;
                            flag = false;
                        }
                        else
                        {
                            q = i + 1_uz;
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
            struct Frontend<NamingSystem::Camelcase, CharT>
            {
                using StringType = std::basic_string<CharT>;
                using StringViewType = std::basic_string_view<CharT>;

                inline std::vector<StringViewType> operator()(const StringViewType name) const noexcept
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
                        else if (std::islower(name[i], std::locale{}))
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
            struct Frontend<NamingSystem::Pascalcase, CharT>
                : public Frontend<NamingSystem::Camelcase, CharT> {};

            template<CharType CharT>
            struct Frontend<NamingSystem::UpperUnderscore, CharT>
                : public Frontend<NamingSystem::Underscore, CharT> {};

            extern template struct Frontend<NamingSystem::Underscore, char>;
            extern template struct Frontend<NamingSystem::Underscore, wchar>;

            extern template struct Frontend<NamingSystem::Camelcase, char>;
            extern template struct Frontend<NamingSystem::Camelcase, wchar>;

            extern template struct Frontend<NamingSystem::Pascalcase, char>;
            extern template struct Frontend<NamingSystem::Pascalcase, wchar>;

            extern template struct Frontend<NamingSystem::UpperUnderscore, char>;
            extern template struct Frontend<NamingSystem::UpperUnderscore, wchar>;
        };
    };
};
