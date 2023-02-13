#pragma once

#include <ospf/concepts/base.hpp>
#include <ospf/string/hasher.hpp>

namespace ospf
{
    inline namespace concepts
    {
        template<typename T>
        concept EnumType = std::is_enum_v<T>;

        template<EnumType T, CharType CharT = char>
        inline constexpr const std::basic_string_view<CharT> to_string(const T value) noexcept
        {
            if constexpr (SameAs<CharT, char>)
            {
                return magic_enum::enum_name<T>(value);
            }
            else
            {
                static StringHashMap<std::string_view, std::basic_string<CharT>> cache;
                const auto str = magic_enum::enum_name<T>(value);
                const auto it = cache.find(str);
                if (it == cache.end())
                {
                    const auto [new_it, _] = cache.insert({ str, boost::locale::conv::to_utf<CharT>(std::string{ str }, std::locale{}) });
                    return new_it->second;
                }
                else
                {
                    return it->second;
                }
            }
        }
    };
};

namespace std
{
    template<ospf::EnumType T, ospf::CharType CharT = char>
    inline const basic_string_view<CharT> to_string(const T value) noexcept
    {
        return ospf::to_string<T, CharT>(value);
    }

    template<ospf::EnumType T, ospf::CharType CharT>
    struct formatter<T, CharT>
        : public formatter<basic_string_view<CharT>, CharT>
    {
        template<typename FormatContext>
        inline decltype(auto) format(const T value, FormatContext& fc)
        {
            static const auto _formatter = formatter<basic_string_view<CharT>, CharT>{};
            return _formatter.format(ospf::to_string<T, CharT>(value), fc);
        }
    };
};
