#pragma once

#include <ospf/basic_definition.hpp>
#include <ospf/functional/result.hpp>
#include <ospf/ospf_base_api.hpp>

namespace ospf
{
    inline namespace serialization
    {
        namespace csv
        {
            OSPF_BASE_API std::string from_bool(const bool value) noexcept;
            OSPF_BASE_API std::string from_u8(const u8 value) noexcept;
            OSPF_BASE_API std::string from_i8(const i8 value) noexcept;
            OSPF_BASE_API std::string from_u16(const u16 value) noexcept;
            OSPF_BASE_API std::string from_i16(const i16 value) noexcept;
            OSPF_BASE_API std::string from_u32(const u32 value) noexcept;
            OSPF_BASE_API std::string from_i32(const i32 value) noexcept;
            OSPF_BASE_API std::string from_u64(const u64 value) noexcept;
            OSPF_BASE_API std::string from_i64(const i64 value) noexcept;
            OSPF_BASE_API std::string from_f32(const f32 value) noexcept;
            OSPF_BASE_API std::string from_f64(const f64 value) noexcept;

            // todo: big int, decimal and chrono

            template<typename T>
            struct ToCSVValue;

            template<typename T>
            concept SerializableToCSV = requires
            {
                { ToCSVValue<T>{}(std::declval<T>()) } -> DecaySameAs<Result<std::string>>;
            };

            template<EnumType T>
            struct ToCSVValue<T>
            {
                inline Result<std::string> operator()(const T value) const noexcept
                {
                    return magic_enum::enum_name<T>(value);
                }
            };

            template<typename T>
                requires (std::convertible_to<T, std::string> || std::convertible_to<T, std::string_view>)
            struct ToCSVValue<T>
            {
                inline Result<std::string> operator()(ArgCLRefType<T> value) const noexcept
                {
                    if constexpr (std::convertible_to<T, std::string_view>)
                    {
                        return std::string{ static_cast<std::string_view>(value) };
                    }
                    else
                    {
                        return static_cast<std::string>(value);
                    }
                }
            };

            // todo: optional, ptr, variant, either, val/ref

            template<>
            struct ToCSVValue<bool>
            {
                inline Result<std::string> operator()(const bool value) const noexcept
                {
                    return from_bool(value);
                }
            };

            template<>
            struct ToCSVValue<u8>
            {
                inline Result<std::string> operator()(const u8 value) const noexcept
                {
                    return from_u8(value);
                }
            };

            template<>
            struct ToCSVValue<i8>
            {
                inline Result<std::string> operator()(const i8 value) const noexcept
                {
                    return from_i8(value);
                }
            };

            template<>
            struct ToCSVValue<u16>
            {
                inline Result<std::string> operator()(const u16 value) const noexcept
                {
                    return from_u16(value);
                }
            };

            template<>
            struct ToCSVValue<i16>
            {
                inline Result<std::string> operator()(const i16 value) const noexcept
                {
                    return from_i16(value);
                }
            };

            template<>
            struct ToCSVValue<u32>
            {
                inline Result<std::string> operator()(const u32 value) const noexcept
                {
                    return from_u32(value);
                }
            };

            template<>
            struct ToCSVValue<i32>
            {
                inline Result<std::string> operator()(const i32 value) const noexcept
                {
                    return from_i32(value);
                }
            };

            template<>
            struct ToCSVValue<u64>
            {
                inline Result<std::string> operator()(const u64 value) const noexcept
                {
                    return from_u64(value);
                }
            };

            template<>
            struct ToCSVValue<i64>
            {
                inline Result<std::string> operator()(const i64 value) const noexcept
                {
                    return from_i64(value);
                }
            };

            template<>
            struct ToCSVValue<std::string>
            {
                inline Result<std::string> operator()(const std::string& value) const noexcept
                {
                    return value;
                }
            };

            template<>
            struct ToCSVValue<std::string_view>
            {
                inline Result<std::string> operator()(const std::string_view value) const noexcept
                {
                    return std::string{ value };
                }
            };
        };
    };
};
