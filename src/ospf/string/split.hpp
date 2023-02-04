#pragma once

#include <ospf/type_family.hpp>
#include <regex>
#include <set>
#include <format>

namespace ospf
{
    inline namespace string
    {
        template<typename C>
        inline static constexpr std::vector<std::basic_string_view<C>> regex_split(const std::basic_string_view<C> src, const std::basic_string_view<C> regex) noexcept
        {
            std::basic_regex<C> reg{ regex.data() };
            std::vector<std::basic_string_view<C>> ret;
            std::regex_iterator<typename std::basic_string_view<C>::const_iterator> curr{ src.cbegin(), src.cend(), reg };
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

        template<typename C>
        inline static constexpr std::vector<std::basic_string_view<C>> regex_split(const std::basic_string_view<C> src, const C* regex) noexcept
        {
            return regex_split(src, std::basic_string_view<C>{ regex });
        }

        template<typename C>
        inline static constexpr std::vector<std::basic_string_view<C>> regex_split(const C* src, const C* regex) noexcept
        {
            return regex_split(std::basic_string_view<C>{ src }, std::basic_string_view<C>{ regex });
        }

        template<typename C>
        inline static constexpr decltype(auto) split(const std::basic_string_view<C> src, const std::basic_string_view<C> splitors = std::basic_string_view<C>{}) noexcept
        {
            // todo: impl for different character

            static const std::set<C> regex_special_charaters = { '^', '$', '.', '[', ']', '*', '\\', '?', '+', '{', '}', '|', '(', ')' };
            static const auto is_regex_special_charaters = [](const C ch) -> bool
            {
                return regex_special_charaters.contains(ch);
            };
            static const auto to_regex_charater = [](const C ch) -> std::basic_string<C>
            {
                return is_regex_special_charaters(ch) ? std::basic_string<C>{ "\\" } : std::format("{}", ch);
            };

            if (splitors.empty())
            {
                return regex_split(src, std::basic_string_view<C>{ "\\s" });
            }
            else
            {
                auto curr(splitors.cbegin());
                std::basic_ostringstream<C> regex_sout;
                regex_sout << "[" << to_regex_charater(*curr);
                ++curr;

                for (auto end(splitors.cend()); curr != end; ++curr)
                {
                    regex_sout << "|" << to_regex_charater(*curr);
                }
                regex_sout << "]";
                return regex_split(src, std::basic_string_view<C>{ regex_sout.str() });
            }
        }

        template<typename C>
        std::vector<std::basic_string_view<C>> split(const std::basic_string_view<C> src, const C* splitors) noexcept
        {
            return split(src, std::basic_string_view<C>{ splitors });
        }

        template<typename C>
        std::vector<std::basic_string_view<C>> split(const C* src, const C* splitors) noexcept
        {
            return split(std::basic_string_view<C>{ src }, std::basic_string_view<C>{ splitors });
        }

        template<typename C>
        std::vector<std::basic_string_view<C>> regex_catch(const std::basic_string_view<C> src, const std::basic_string_view<C> regex) noexcept
        {
            std::basic_regex<C> reg(regex);
            std::vector<std::basic_string_view<C>> ret;
            std::regex_iterator<typename std::basic_string_view<C>::const_iterator> curr(src.cbegin(), src.cend(), reg);
            decltype(curr) end;
            for (; curr != end; ++curr)
            {
                ret.push_back(curr->str());
            }

            return ret;
        }

        template<typename C>
        std::vector<std::basic_string_view<C>> regex_catch(const std::basic_string_view<C> src, const C* regex) noexcept
        {
            return regex_catch(src, std::basic_string_view<C>{ regex });
        }

        template<typename C>
        std::vector<std::basic_string_view<C>> regex_catch(const C* src, const C* regex) noexcept
        {
            return regex_catch(std::basic_string_view<C>{ src }, std::basic_string_view<C>{ regex });
        }
    };
};
