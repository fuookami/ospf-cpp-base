#include <ospf/string/hasher.hpp>

namespace ospf::string
{
    const usize StringHasher<char>::operator()(const char* str) const noexcept
    {
        static constexpr const auto hasher = std::hash<std::string_view>{};
        return hasher(str);
    }

    const usize StringHasher<char>::operator()(const std::string_view str) const noexcept
    {
        static constexpr const auto hasher = std::hash<std::string_view>{};
        return hasher(str);
    }

    const usize StringHasher<char>::operator()(const std::string& str) const noexcept
    {
        static constexpr const auto hasher = std::hash<std::string_view>{};
        return hasher(str);
    }
};
