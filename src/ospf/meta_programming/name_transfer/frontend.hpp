#pragma once

#include <ospf/ospf_base_api.hpp>
#include <ospf/basic_definition.hpp>
#include <ospf/meta_programming/naming_system.hpp>
#include <vector>
#include <string_view>

namespace ospf
{
    inline namespace meta_programming
    {
        namespace name_transfer
        {
            OSPF_BASE_API std::vector<std::string_view> underscore_name_split(const std::string_view name) noexcept;
            OSPF_BASE_API std::vector<std::string_view> calmelcase_name_split(const std::string_view name) noexcept;
            OSPF_BASE_API std::vector<std::string_view> pascalcase_name_split(const std::string_view name) noexcept;
            OSPF_BASE_API std::vector<std::string_view> upper_underscore_name_split(const std::string_view name) noexcept;

            template<NamingSystem system, typename CharT>
            struct Frontend 
            {
                inline std::vector<std::basic_string_view<CharT>> operator()(const std::std::basic_string_view<CharT> name) const noexcept
                {
                    return {};
                }
            };

            template<>
            struct Frontend<NamingSystem::Underscore, char>
            {
                inline decltype(auto) operator()(const std::string_view name) const noexcept
                {
                    return underscore_name_split(name);
                }
            };

            template<>
            struct Frontend<NamingSystem::Camelcase, char>
            {
                inline decltype(auto) operator()(const std::string_view name) const noexcept
                {
                    return calmelcase_name_split(name);
                }
            };

            template<>
            struct Frontend<NamingSystem::Pascalcase, char>
            {
                inline decltype(auto) operator()(const std::string_view name) const noexcept
                {
                    return pascalcase_name_split(name);
                }
            };

            template<>
            struct Frontend<NamingSystem::UpperUnderscore, char>
            {
                inline decltype(auto) operator()(const std::string_view name) const noexcept
                {
                    return upper_underscore_name_split(name);
                };
            };

            // todo: impl for different character
        };
    };
};
