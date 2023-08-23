﻿#pragma once

#include <ospf/ospf_base_api.hpp>
#include <ospf/basic_definition.hpp>
#include <ospf/concepts/base.hpp>
#include <ospf/literal_constant.hpp>
#include <ospf/meta_programming/naming_system.hpp>
#include <locale>
#include <numeric>
#include <span>
#include <string>
#include <string_view>

namespace ospf
{
    inline namespace meta_programming
    {
        namespace name_transfer
        {
            template<NamingSystem system, CharType CharT>
            struct Backend;

            template<CharType CharT>
            struct Backend<NamingSystem::Underscore, CharT>
            {
                using StringType = std::basic_string<CharT>;
                using StringViewType = std::basic_string_view<CharT>;

                template<usize len>
                inline StringType operator()(const std::span<const StringViewType, len> words) const noexcept
                {
                    if (words.empty())
                    {
                        return StringType{};
                    }

                    StringType ret{};
                    const usize size = std::accumulate(words.begin(), words.end(), 0_uz,
                        [](const usize lhs, const StringViewType str)
                        {
                            return lhs + str.size();
                        }) + words.size() - 1_uz;
                    ret.resize(size, CharT{ '_' });

                    for (usize i{ 0_uz }, k{ 0_uz }; i != words.size(); ++i)
                    {
                        const StringViewType word = words[i];
                        assert(!word.empty());
                        for (usize j{ 0_uz }; j != word.size(); ++j, ++k)
                        {
                            ret[k] = std::tolower(word[j], std::locale{});
                        }
                        ++k;
                    }

                    return ret;
                }
            };

            template<CharType CharT>
            struct Backend<NamingSystem::Kebab, CharT>
            {
                using StringType = std::basic_string<CharT>;
                using StringViewType = std::basic_string_view<CharT>;

                template<usize len>
                inline StringType operator()(const std::span<const StringViewType, len> words) const noexcept
                {
                    if (words.empty())
                    {
                        return StringType{};
                    }

                    StringType ret{};
                    const usize size = std::accumulate(words.begin(), words.end(), 0_uz,
                        [](const usize lhs, const StringViewType str)
                        {
                            return lhs + str.size();
                        }) + words.size() - 1_uz;
                        ret.resize(size, CharT{ '-' });

                        for (usize i{ 0_uz }, k{ 0_uz }; i != words.size(); ++i)
                        {
                            const StringViewType word = words[i];
                            assert(!word.empty());
                            for (usize j{ 0_uz }; j != word.size(); ++j, ++k)
                            {
                                ret[k] = std::tolower(word[j], std::locale{});
                            }
                            ++k;
                        }

                        return ret;
                }
            };

            template<CharType CharT>
            struct Backend<NamingSystem::Camelcase, CharT>
            {
                using StringType = std::basic_string<CharT>;
                using StringViewType = std::basic_string_view<CharT>;

                template<usize len>
                inline StringType operator()(const std::span<const StringViewType, len> words) const noexcept
                {
                    if (words.empty())
                    {
                        return StringType{};
                    }

                    StringType ret{};
                    const usize size = std::accumulate(words.begin(), words.end(), 0_uz,
                        [](const usize lhs, const StringViewType str) 
                        { 
                            return lhs + str.size(); 
                        });
                    ret.resize(size, CharT{ ' ' });
                    usize k{ 0_uz };
                    for (usize j{ 0_uz }; j != words.front().size(); ++j, ++k)
                    {
                        ret[k] = std::tolower(words.front()[j], std::locale{});
                    }
                    for (usize i{ 1_uz }; i != words.size(); ++i)
                    {
                        const StringViewType word = words[i];
                        assert(!word.empty());
                        ret[k] = std::toupper(word.front(), std::locale{});
                        ++k;
                        for (usize j{ 1_uz }; j != word.size(); ++j, ++k)
                        {
                            ret[k] = std::tolower(word[j], std::locale{});
                        }
                    }
                    return ret;
                }
            };

            template<CharType CharT>
            struct Backend<NamingSystem::Pascalcase, CharT>
            {
                using StringType = std::basic_string<CharT>;
                using StringViewType = std::basic_string_view<CharT>;

                template<usize len>
                inline StringType operator()(const std::span<const StringViewType, len> words) const noexcept
                {
                    if (words.empty())
                    {
                        return StringType{};
                    }

                    StringType ret{};
                    const usize size = std::accumulate(words.begin(), words.end(), 0_uz,
                        [](const usize lhs, const StringViewType str) 
                        { 
                            return lhs + str.size(); 
                        });
                    ret.resize(size, CharT{ ' ' });
                    for (usize i{ 0_uz }, k{ 0_uz }; i != words.size(); ++i)
                    {
                        const StringViewType word = words[i];
                        assert(!word.empty());
                        ret[k] = std::toupper(word.front(), std::locale{});
                        ++k;
                        for (usize j{ 1_uz }; j != word.size(); ++j, ++k)
                        {
                            ret[k] = std::tolower(word[j], std::locale{});
                        }
                    }
                    return ret;
                }
            };

            template<CharType CharT>
            struct Backend<NamingSystem::UpperUnderscore, CharT>
            {
                using StringType = std::basic_string<CharT>;
                using StringViewType = std::basic_string_view<CharT>;

                template<usize len>
                inline StringType operator()(const std::span<const StringViewType, len> words) const noexcept
                {
                    if (words.empty())
                    {
                        return StringType{};
                    }

                    StringType ret{};
                    const usize size = std::accumulate(words.begin(), words.end(), 0_uz,
                        [](const usize lhs, const StringViewType str) 
                        { 
                            return lhs + str.size(); 
                        }) + words.size() - 1_uz;
                    ret.resize(size, CharT{ '_' });
                    for (usize i{ 0_uz }, k{ 0_uz }; i != words.size(); ++i)
                    {
                        const StringViewType word = words[i];
                        assert(!word.empty());
                        for (usize j{ 0_uz }; j != word.size(); ++j, ++k)
                        {
                            ret[k] = std::toupper(word[j], std::locale{});
                        }
                        ++k;
                    }
                    return ret;
                }
            };

            extern template struct Backend<NamingSystem::Underscore, char>;
            extern template struct Backend<NamingSystem::Underscore, wchar>;

            extern template struct Backend<NamingSystem::Kebab, char>;
            extern template struct Backend<NamingSystem::Kebab, wchar>;

            extern template struct Backend<NamingSystem::Camelcase, char>;
            extern template struct Backend<NamingSystem::Camelcase, wchar>;

            extern template struct Backend<NamingSystem::Pascalcase, char>;
            extern template struct Backend<NamingSystem::Pascalcase, wchar>;

            extern template struct Backend<NamingSystem::UpperUnderscore, char>;
            extern template struct Backend<NamingSystem::UpperUnderscore, wchar>;
        };
    };
};
