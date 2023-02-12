#pragma once

#include <ospf/ospf_base_api.hpp>
#include <ospf/basic_definition.hpp>
#include <ospf/meta_programming/naming_system.hpp>
#include <vector>
#include <span>
#include <string_view>

namespace ospf
{
    inline namespace meta_programming
    {
        namespace name_transfer
        {
            OSPF_BASE_API std::string underscore_name_join(const std::span<const std::string_view> words) noexcept;
            OSPF_BASE_API std::string calmelcase_name_join(const std::span<const std::string_view> words) noexcept;
            OSPF_BASE_API std::string pascalcase_name_join(const std::span<const std::string_view> words) noexcept;
            OSPF_BASE_API std::string upper_underscore_name_join(const std::span<const std::string_view> words) noexcept;

            template<NamingSystem system, typename CharT>
            struct Backend
            {
                template<usize len>
                inline std::basic_string<CharT> operator()(const std::span<const std::basic_string_view<CharT>, len> words) const noexcept
                {
                    return {};
                }
            };

            template<>
            struct Backend<NamingSystem::Underscore, char>
            {
                template<usize len>
                inline std::string operator()(const std::span<const std::string_view, len> words) const noexcept
                {
                    return underscore_name_join(words);
                }
            };

            template<>
            struct Backend<NamingSystem::Camelcase, char>
            {
                template<usize len>
                inline std::string operator()(const std::span<const std::string_view, len> words) const noexcept
                {
                    return calmelcase_name_join(words);
                }
            };

            template<>
            struct Backend<NamingSystem::Pascalcase, char>
            {
                template<usize len>
                inline std::string operator()(const std::span<const std::string_view, len> words) const noexcept
                {
                    return pascalcase_name_join(words);
                }
            };

            template<>
            struct Backend<NamingSystem::UpperUnderscore, char>
            {
                template<usize len>
                inline std::string operator()(const std::span<const std::string_view, len> words) const noexcept
                {
                    return upper_underscore_name_join(words);
                }
            };

            // todo: impl for different character
        };
    };
};

