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
        template<typename CharT>
        struct StringHasher;

        template<>
        struct StringHasher<char>
        {
            using is_transparent = void;

            OSPF_BASE_API const usize operator()(const char* str) const noexcept;
            OSPF_BASE_API const usize operator()(const std::string_view str) const noexcept;
            OSPF_BASE_API const usize operator()(const std::string& str) const noexcept;
        };

        // todo: impl for different character

#ifdef BOOST_MSVC
        template<typename K, typename V, typename CharT = typename K::value_type>
            requires (std::is_same_v<K, std::basic_string<CharT>> || std::is_same_v<K, std::basic_string_view<CharT>>)
        using StringHashMap = std::unordered_map<K, V, StringHasher, std::equal_to<>>;

        template<typename K, typename V, typename CharT = typename K::value_type>
            requires (std::is_same_v<K, std::basic_string<CharT>> || std::is_same_v<K, std::basic_string_view<CharT>>)
        using StringHashMultiMap = std::unordered_multimap<K, V, StringHasher, std::equal_to<>>;

        template<typename K, typename CharT = typename K::value_type>
            requires (std::is_same_v<K, std::basic_string<CharT>> || std::is_same_v<K, std::basic_string_view<CharT>>)
        using StringHashSet = std::unordered_set<K, StringHasher, std::equal_to<>>;
#else
        template<typename K, typename V, typename CharT = typename K::value_type>
            requires (std::is_same_v<K, std::basic_string<CharT>> || std::is_same_v<K, std::basic_string_view<CharT>>)
        using StringHashMap = std::unordered_map<K, V>;

        template<typename K, typename V, typename CharT = typename K::value_type>
            requires (std::is_same_v<K, std::basic_string<CharT>> || std::is_same_v<K, std::basic_string_view<CharT>>)
        using StringHashMultiMap = std::unordered_multimap<K, V>;

        template<typename K, typename CharT = typename K::value_type>
            requires (std::is_same_v<K, std::basic_string<CharT>> || std::is_same_v<K, std::basic_string_view<CharT>>)
        using StringHashSet = std::unordered_set<K>;
#endif
    };
};
