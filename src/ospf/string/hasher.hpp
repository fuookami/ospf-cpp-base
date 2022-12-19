#pragma once

#include <ospf/ospf_base_api.hpp>
#include <ospf/basic_definition.hpp>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <functional>

namespace ospf
{
    inline namespace string
    {
        struct StringHasher
        {
            using is_transparent = void;

            OSPF_BASE_API usize operator()(const char* str) const noexcept;
            OSPF_BASE_API usize operator()(const std::string_view str) const noexcept;
            OSPF_BASE_API usize operator()(const std::string& str) const noexcept;
        };

#ifdef BOOST_MSVC
        template<typename K_, typename V_>
            requires (std::is_same_v<K_, std::string> || std::is_same_v<K_, std::string_view>)
        using StringHashMap = std::unordered_map<K_, V_, StringHasher, std::equal_to<>>;

        template<typename K_, typename V_>
            requires (std::is_same_v<K_, std::string> || std::is_same_v<K_, std::string_view>)
        using StringHashMultiMap = std::unordered_multimap<K_, V_, StringHasher, std::equal_to<>>;

        template<typename K_>
            requires (std::is_same_v<K_, std::string> || std::is_same_v<K_, std::string_view>)
        using StringHashSet = std::unordered_set<K_, StringHasher, std::equal_to<>>;
#else
        template<typename K_, typename V_>
            requires (std::is_same_v<K_, std::string> || std::is_same_v<K_, std::string_view>)
        using StringHashMap = std::unordered_map<K_, V_>;

        template<typename K_, typename V_>
            requires (std::is_same_v<K_, std::string> || std::is_same_v<K_, std::string_view>)
        using StringHashMultiMap = std::unordered_multimap<K_, V_>;

        template<typename K_>
            requires (std::is_same_v<K_, std::string> || std::is_same_v<K_, std::string_view>)
        using StringHashSet = std::unordered_set<K_>;
#endif
    };
};
