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

            template<NamingSystem system>
            struct Backend
            {
                inline std::string operator()(const std::span<const std::string_view> words) const noexcept
                {
                    return {};
                }
            };

            template<>
            struct Backend<NamingSystem::Underscore>
            {
                inline std::string operator()(const std::span<const std::string_view> words) const noexcept
                {
                    return underscore_name_join(words);
                }
            };

            template<>
            struct Backend<NamingSystem::Camelcase>
            {
                inline std::string operator()(const std::span<const std::string_view> words) const noexcept
                {
                    return calmelcase_name_join(words);
                }
            };

            template<>
            struct Backend<NamingSystem::Pascalcase>
            {
                inline std::string operator()(const std::span<const std::string_view> words) const noexcept
                {
                    return pascalcase_name_join(words);
                }
            };

            template<>
            struct Backend<NamingSystem::UpperUnderscore>
            {
                inline std::string operator()(const std::span<const std::string_view> words) const noexcept
                {
                    return upper_underscore_name_join(words);
                }
            };
        };
    };
};

