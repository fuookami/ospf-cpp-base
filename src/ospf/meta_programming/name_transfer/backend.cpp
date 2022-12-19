#include "backend.hpp"
#include <ospf/literal_constant.hpp>
#include <numeric>

namespace ospf::meta_programming::name_transfer
{
    std::string underscore_name_join(const std::span<const std::string_view> words) noexcept
    {
        if (words.empty())
        {
            return "";
        }

        std::string ret{};
        const auto size = std::accumulate(words.begin(), words.end(), 0_uz, [](const usize lhs, const std::string_view str) { return lhs + str.size(); }) + words.size() - 1_uz;
        ret.resize(size, '_');
        for (auto i{ 0_uz }, k{ 0_uz }; i != words.size(); ++i)
        {
            const auto word = words[i];
            assert(!word.empty());
            for (auto j{ 0_uz }; j != word.size(); ++j, ++k)
            {
                ret[k] = static_cast<char>(std::tolower(word[j]));
            }
            ++k;
        }
        return ret;
    }

    std::string calmelcase_name_join(const std::span<const std::string_view> words) noexcept
    {
        if (words.empty())
        {
            return "";
        }

        std::string ret{};
        const auto size = std::accumulate(words.begin(), words.end(), 0_uz, [](const usize lhs, const std::string_view str) { return lhs + str.size(); });
        ret.resize(size, ' ');
        auto k{ 0_uz };
        for (auto j{ 0_uz }; j != words.front().size(); ++j, ++k)
        {
            ret[k] = static_cast<char>(std::tolower(words.front()[j]));
        }
        for (auto i{ 1_uz }; i != words.size(); ++i)
        {
            const auto word = words[i];
            assert(!word.empty());
            ret[k] = static_cast<char>(std::toupper(word.front()));
            ++k;
            for (auto j{ 1_uz }; j != word.size(); ++j, ++k)
            {
                ret[k] = static_cast<char>(std::tolower(word[j]));
            }
        }
        return ret;
    }

    std::string pascalcase_name_join(const std::span<const std::string_view> words) noexcept
    {
        if (words.empty())
        {
            return "";
        }

        std::string ret{};
        const auto size = std::accumulate(words.begin(), words.end(), 0_uz, [](const usize lhs, const std::string_view str) { return lhs + str.size(); });
        ret.resize(size, ' ');
        for (auto i{ 0_uz }, k{ 0_uz }; i != words.size(); ++i)
        {
            const auto word = words[i];
            assert(!word.empty());
            ret[k] = static_cast<char>(std::toupper(word.front()));
            ++k;
            for (auto j{ 1_uz }; j != word.size(); ++j, ++k)
            {
                ret[k] = static_cast<char>(std::tolower(word[j]));
            }
        }
        return ret;
    }

    std::string upper_underscore_name_join(const std::span<const std::string_view> words) noexcept
    {
        if (words.empty())
        {
            return "";
        }

        std::string ret{};
        const auto size = std::accumulate(words.begin(), words.end(), 0_uz, [](const usize lhs, const std::string_view str) { return lhs + str.size(); }) + words.size() - 1_uz;
        ret.resize(size, '_');
        for (auto i{ 0_uz }, k{ 0_uz }; i != words.size(); ++i)
        {
            const auto word = words[i];
            assert(!word.empty());
            for (auto j{ 0_uz }; j != word.size(); ++j, ++k)
            {
                ret[k] = static_cast<char>(std::toupper(word[j]));
            }
            ++k;
        }
        return ret;
    }
};
