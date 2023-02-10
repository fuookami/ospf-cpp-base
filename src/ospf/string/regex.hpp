#pragma once

#include <set>

namespace ospf
{
    inline namespace string
    {
        namespace regex
        {
            template<typename CharT>
            struct RegexTrait;

            template<>
            struct RegexTrait<char>
            {
                OSPF_BASE_API static const std::set<char> special_charaters;
                static constexpr const std::string_view empty_charaters = "\\s";

                OSPF_BASE_API static std::string to_regex_expr(const char ch) noexcept;
                OSPF_BASE_API static std::string to_regex_expr(const std::string_view str) noexcept;
                OSPF_BASE_API static std::string generate_regex_expr(const std::string_view splitors) noexcept;
            };

            // todo: impl for different character
        };
    };
};
