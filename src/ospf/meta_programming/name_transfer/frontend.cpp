#include "frontend.hpp"
#include <ospf/literal_constant.hpp>
#include <ranges>

namespace ospf::meta_programming::name_transfer
{
    std::vector<std::string_view> underscore_name_split(const std::string_view name) noexcept
    {
        if (name.empty())
        {
            return {};
        }
        assert(std::ranges::all_of(name, [](const char ch)
            {
                return static_cast<bool>(std::isalnum(ch)) || ch == '_';
            }));

        auto p{ 0_uz }, q{ 1_uz };
        auto flag{ name.front() == '_' };
        std::vector<std::string_view> ret;
        for (auto i{ 0_uz }; i != name.size(); ++i)
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

    std::vector<std::string_view> calmelcase_name_split(const std::string_view name) noexcept
    {
        if (name.empty())
        {
            return {};
        }
        assert(std::ranges::all_of(name, [](const char ch)
            {
                return static_cast<bool>(std::isalnum(ch));
            }));

        auto p{ 0_uz }, q{ 1_uz };
        auto flag{ static_cast<bool>(std::isupper(name.front())) };
        std::vector<std::string_view> ret;
        for (usize i{ 0_uz }; i != name.size(); ++i)
        {
            if (static_cast<bool>(std::isupper(name[i])))
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
            else if (static_cast<bool>(std::islower(name[i])))
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

    std::vector<std::string_view> pascalcase_name_split(const std::string_view name) noexcept
    {
        return calmelcase_name_split(name);
    }

    std::vector<std::string_view> upper_underscore_name_split(const std::string_view name) noexcept
    {
        return underscore_name_split(name);
    }
};
