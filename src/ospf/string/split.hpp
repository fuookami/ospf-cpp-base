#pragma once

#include <ospf/type_family.hpp>
#include <ospf/ospf_base_api.hpp>
#include <ospf/string/regex.hpp>
#include <regex>

namespace ospf
{
    inline namespace string
    {
        template<typename CharT>
        inline static constexpr std::vector<std::basic_string_view<CharT>> regex_split(const std::basic_string_view<CharT> src, const std::basic_string_view<CharT> regex) noexcept
        {
            std::basic_regex<CharT> reg{ regex.data() };
            std::vector<std::basic_string_view<CharT>> ret;
            std::regex_iterator<typename std::basic_string_view<CharT>::const_iterator> curr{ src.cbegin(), src.cend(), reg };
            decltype(curr) prefix, end;
            bool flag{ false };
            for (; curr != end; ++curr)
            {
                if (curr->prefix().length() != 0_uz)
                {
                    ret.push_back(curr->prefix().str());
                    prefix = curr;
                    flag = true;
                }
            }

            if (flag && prefix != end)
            {
                auto temp = prefix->suffix();
                if (temp.length() != 0_uz)
                {
                    ret.push_back(std::move(temp.str()));
                }
            }
            else if (!flag)
            {
                ret.push_back(src);
            }

            return ret;
        }

        template<typename CharT>
        inline static constexpr std::vector<std::basic_string_view<CharT>> regex_split(const std::basic_string_view<CharT> src, const CharT* regex) noexcept
        {
            return regex_split(src, std::basic_string_view<CharT>{ regex });
        }

        template<typename CharT>
        inline static constexpr std::vector<std::basic_string_view<CharT>> regex_split(const CharT* src, const CharT* regex) noexcept
        {
            return regex_split(std::basic_string_view<CharT>{ src }, std::basic_string_view<CharT>{ regex });
        }

        template<typename CharT>
        inline static constexpr decltype(auto) split(const std::basic_string_view<CharT> src, const std::basic_string_view<CharT> splitors = std::basic_string_view<CharT>{}) noexcept
        {
            if (splitors.empty())
            {
                return regex_split(src, regex::RegexTrait<CharT>::empty_charaters);
            }
            else
            {
                return regex_split(src, regex::RegexTrait<CharT>::generate_regex_expr(splitors));
            }
        }

        template<typename CharT>
        std::vector<std::basic_string_view<CharT>> split(const std::basic_string_view<CharT> src, const CharT* splitors) noexcept
        {
            return split(src, std::basic_string_view<CharT>{ splitors });
        }

        template<typename CharT>
        std::vector<std::basic_string_view<CharT>> split(const CharT* src, const CharT* splitors) noexcept
        {
            return split(std::basic_string_view<CharT>{ src }, std::basic_string_view<CharT>{ splitors });
        }

        template<typename CharT>
        std::vector<std::basic_string_view<CharT>> regex_catch(const std::basic_string_view<CharT> src, const std::basic_string_view<CharT> regex) noexcept
        {
            std::basic_regex<CharT> reg(regex);
            std::vector<std::basic_string_view<CharT>> ret;
            std::regex_iterator<typename std::basic_string_view<CharT>::const_iterator> curr(src.cbegin(), src.cend(), reg);
            decltype(curr) end;
            for (; curr != end; ++curr)
            {
                ret.push_back(curr->str());
            }

            return ret;
        }

        template<typename CharT>
        std::vector<std::basic_string_view<CharT>> regex_catch(const std::basic_string_view<CharT> src, const CharT* regex) noexcept
        {
            return regex_catch(src, std::basic_string_view<CharT>{ regex });
        }

        template<typename CharT>
        std::vector<std::basic_string_view<CharT>> regex_catch(const CharT* src, const CharT* regex) noexcept
        {
            return regex_catch(std::basic_string_view<CharT>{ src }, std::basic_string_view<CharT>{ regex });
        }
    };
};
