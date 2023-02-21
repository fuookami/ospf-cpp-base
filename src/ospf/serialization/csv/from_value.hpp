#pragma once

#include <ospf/basic_definition.hpp>
#include <ospf/functional/result.hpp>
#include <ospf/meta_programming/type_info.hpp>
#include <ospf/ospf_base_api.hpp>
#include <ospf/serialization/nullable.hpp>
#include <ospf/serialization/writable.hpp>
#include <format>

namespace ospf
{
    inline namespace serialization
    {
        namespace csv
        {
            OSPF_BASE_API std::optional<bool> to_bool(const std::string_view value) noexcept;
            OSPF_BASE_API std::optional<u8> to_u8(const std::string_view value) noexcept;
            OSPF_BASE_API std::optional<i8> to_i8(const std::string_view value) noexcept;
            OSPF_BASE_API std::optional<u16> to_u16(const std::string_view value) noexcept;
            OSPF_BASE_API std::optional<i16> to_i16(const std::string_view value) noexcept;
            OSPF_BASE_API std::optional<i32> to_i32(const std::string_view value) noexcept;
            OSPF_BASE_API std::optional<u32> to_u32(const std::string_view value) noexcept;
            OSPF_BASE_API std::optional<i64> to_i64(const std::string_view value) noexcept;
            OSPF_BASE_API std::optional<u64> to_u64(const std::string_view value) noexcept;
            OSPF_BASE_API std::optional<f32> to_f32(const std::string_view value) noexcept;
            OSPF_BASE_API std::optional<f64> to_f64(const std::string_view value) noexcept;

            // todo: big int, decimal and chrono
            // todo: impl for different character

            template<typename T, CharType CharT>
            struct FromCSVValue;

            template<typename T, typename CharT>
            concept DeserializableFromCSV = CharType<CharT> && requires (const FromCSVValue<T, CharT>& deserializer)
            {
                { deserializer(std::declval<std::basic_string_view<CharT>>()) } -> DecaySameAs<Result<T>>;
            };

            template<EnumType T, CharType CharT>
            struct FromCSVValue<T, CharT>
            {
                inline Result<T> operator()(const std::basic_string_view<CharT> value) const noexcept
                {
                    const auto enum_value = parse_enum<T, CharT>(value);
                    if (enum_value.has_value())
                    {
                        return *enum_value;
                    }
                    const auto int_value = to_u64(value);
                    if (int_value.has_value())
                    {
                        const auto enum_value = magic_enum::enum_cast<T>(int_value);
                        if (enum_value.has_value())
                        {
                            return *enum_value;
                        }
                    }
                    return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for enum \"{}\"", value, TypeInfo<T>::name()) };
                }
            };

            template<typename T, CharType CharT>
                requires (std::convertible_to<std::basic_string<CharT>, T> || std::convertible_to<std::basic_string_view<CharT>, T>)
            struct FromCSVValue<T, CharT>
            {
                inline Result<T> operator()(const std::basic_string_view<CharT> value) const noexcept
                {
                    if constexpr (std::convertible_to<std::basic_string_view<CharT>, T>)
                    {
                        return static_cast<T>(value);
                    }
                    else
                    {
                        return static_cast<T>(std::basic_string<CharT>{ value });
                    }
                }
            };

            // todo: optional, ptr, variant, either, val/ref

            template<>
            struct FromCSVValue<bool, char>
            {
                inline Result<bool> operator()(const std::string_view value) const noexcept
                {
                    const auto ret = to_bool(value);
                    if (ret.has_value())
                    {
                        return *ret;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for bool", value) };
                    }
                }
            };

            template<>
            struct FromCSVValue<u8, char>
            {
                inline Result<u8> operator()(const std::string_view value) const noexcept
                {
                    const auto ret = to_u8(value);
                    if (ret.has_value())
                    {
                        return *ret;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for u8", value) };
                    }
                }
            };

            template<>
            struct FromCSVValue<i8, char>
            {
                inline Result<i8> operator()(const std::string_view value) const noexcept
                {
                    const auto ret = to_i8(value);
                    if (ret.has_value())
                    {
                        return *ret;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for i8", value) };
                    }
                }
            };

            template<>
            struct FromCSVValue<u16, char>
            {
                inline Result<u16> operator()(const std::string_view value) const noexcept
                {
                    const auto ret = to_u16(value);
                    if (ret.has_value())
                    {
                        return *ret;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for u16", value) };
                    }
                }
            };

            template<>
            struct FromCSVValue<i16, char>
            {
                inline Result<i16> operator()(const std::string_view value) const noexcept
                {
                    const auto ret = to_i16(value);
                    if (ret.has_value())
                    {
                        return *ret;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for i16", value) };
                    }
                }
            };

            template<>
            struct FromCSVValue<u32, char>
            {
                inline Result<u32> operator()(const std::string_view value) const noexcept
                {
                    const auto ret = to_u32(value);
                    if (ret.has_value())
                    {
                        return *ret;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for u32", value) };
                    }
                }
            };

            template<>
            struct FromCSVValue<i32, char>
            {
                inline Result<i32> operator()(const std::string_view value) const noexcept
                {
                    const auto ret = to_i32(value);
                    if (ret.has_value())
                    {
                        return *ret;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for i32", value) };
                    }
                }
            };

            template<>
            struct FromCSVValue<u64, char>
            {
                inline Result<u64> operator()(const std::string_view value) const noexcept
                {
                    const auto ret = to_u64(value);
                    if (ret.has_value())
                    {
                        return *ret;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for u64", value) };
                    }
                }
            };

            template<>
            struct FromCSVValue<i64, char>
            {
                inline Result<i64> operator()(const std::string_view value) const noexcept
                {
                    const auto ret = to_i64(value);
                    if (ret.has_value())
                    {
                        return *ret;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for i64", value) };
                    }
                }
            };

            template<>
            struct FromCSVValue<f32, char>
            {
                inline Result<f32> operator()(const std::string_view value) const noexcept
                {
                    const auto ret = to_f32(value);
                    if (ret.has_value())
                    {
                        return *ret;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for f32", value) };
                    }
                }
            };

            template<>
            struct FromCSVValue<f64, char>
            {
                inline Result<f64> operator()(const std::string_view value) const noexcept
                {
                    const auto ret = to_f64(value);
                    if (ret.has_value())
                    {
                        return *ret;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for f64", value) };
                    }
                }
            };

            template<>
            struct FromCSVValue<std::string, char>
            {
                inline Result<std::string> operator()(const std::string_view value) const noexcept
                {
                    return std::string{ value };
                }
            };

            template<>
            struct FromCSVValue<std::string_view, char>
            {
                inline Result<std::string_view> operator()(const std::string_view value) const noexcept
                {
                    return value;
                }
            };
        };
    };
};
