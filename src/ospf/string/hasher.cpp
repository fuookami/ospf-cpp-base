#include <ospf/string/hasher.hpp>

namespace ospf::string
{
    usize StringHasher::operator()(const char* str) const noexcept
    {
        static constexpr const auto hasher = std::hash<std::string_view>{};
        return hasher(str);
    }

    usize StringHasher::operator()(const std::string_view str) const noexcept
    {
        static constexpr const auto hasher = std::hash<std::string_view>{};
        return hasher(str);
    }

    usize StringHasher::operator()(const std::string& str) const noexcept
    {
        static constexpr const auto hasher = std::hash<std::string_view>{};
        return hasher(str);
    }
};


