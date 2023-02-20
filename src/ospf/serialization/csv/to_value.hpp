#pragma once

#include <ospf/basic_definition.hpp>
#include <ospf/functional/result.hpp>
#include <ospf/functional/value_or_reference.hpp>
#include <ospf/memory/pointer/category.hpp>
#include <ospf/ospf_base_api.hpp>
#include <deque>
#include <span>

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
            // todo: impl for different character

            template<typename T, CharType CharT>
            struct ToCSVValue;

            template<typename T, typename CharT>
            concept SerializableToCSV = CharType<CharT> && requires (const ToCSVValue<OriginType<T>, CharT>& serializer)
            {
                { serializer(std::declval<T>()) } -> DecaySameAs<Result<std::basic_string<CharT>>>;
            };

            template<EnumType T, CharType CharT>
            struct ToCSVValue<T, CharT>
            {
                inline Result<std::basic_string<CharT>> operator()(const T value) const noexcept
                {
                    return to_string<T, CharT>(value);
                }
            };

            template<typename T, CharType CharT>
                requires (std::convertible_to<T, std::basic_string<CharT>> || std::convertible_to<T, std::basic_string_view<CharT>>)
            struct ToCSVValue<T, CharT>
            {
                inline Result<std::basic_string<CharT>> operator()(ArgCLRefType<T> value) const noexcept
                {
                    if constexpr (std::convertible_to<T, std::basic_string_view<CharT>>)
                    {
                        return std::basic_string<CharT>{ static_cast<std::basic_string_view<CharT>>(value) };
                    }
                    else
                    {
                        return static_cast<std::basic_string<CharT>>(value);
                    }
                }
            };

            template<typename T, CharType CharT>
                requires SerializableToCSV<T, CharT>
            struct ToCSVValue<std::optional<T>, CharT>
            {
                inline Result<std::basic_string<CharT>> operator()(const std::optional<T>& value) const noexcept
                {
                    static const ToCSVValue<OriginType<T>, CharT> serializer{};
                    if (value.has_value())
                    {
                        return serializer(*value);
                    }
                    else
                    {
                        return std::basic_string<CharT>{};
                    }
                }
            };

            template<typename T, pointer::PointerCategory cat, CharType CharT>
                requires SerializableToCSV<T, CharT>
            struct ToCSVValue<pointer::Ptr<T, cat>, CharT>
            {
                inline Result<std::basic_string<CharT>> operator()(const pointer::Ptr<T, cat>& value) const noexcept
                {
                    static const ToCSVValue<OriginType<T>, CharT> serializer{};
                    if (value != nullptr)
                    {
                        return serializer(*value);
                    }
                    else
                    {
                        return std::basic_string<CharT>{};
                    }
                }
            };

            template<typename T, reference::ReferenceCategory cat, CharType CharT>
                requires SerializableToCSV<T, CharT>
            struct ToCSVValue<reference::Ref<T, cat>, CharT>
            {
                inline Result<std::basic_string<CharT>> operator()(const reference::Ref<T, cat>& value) const noexcept
                {
                    static const ToCSVValue<OriginType<T>, CharT> serializer{};
                    return serializer(*value);
                }
            };

            template<typename T, typename U, CharType CharT>
                requires SerializableToCSV<T, CharT> && SerializableToCSV<U, CharT>
            struct ToCSVValue<std::pair<T, U>, CharT>
            {
                inline Result<std::basic_string<CharT>> operator()(const std::pair<T, U>& value) const noexcept
                {
                    std::basic_ostringstream<CharT> sout;
                    static const ToCSVValue<OriginType<T>, CharT> serializer1{};
                    OSPF_TRY_GET(value1, serializer1(value.first));
                    sout << std::move(value1);
                    sout << CharT{ ';' };
                    static const ToCSVValue<OriginType<U>, CharT> serializer2{};
                    OSPF_TRY_GET(value2, serializer2(value.second));
                    sout << std::move(value2);
                    return sout.str();
                }
            };

            template<typename... Ts, CharType CharT>
            struct ToCSVValue<std::tuple<Ts...>, CharT>
            {
                inline Result<std::basic_string<CharT>> operator()(const std::tuple<Ts...>& value) const noexcept
                {
                    std::basic_ostringstream<CharT> sout;
                    OSPF_TRY_EXEC(serialize<0_uz>(sout, value));
                    return sout.str();
                }

                template<usize i>
                inline static Try<> serialize(std::basic_ostringstream<CharT>& os, const std::tuple<Ts...>& value) noexcept
                {
                    if constexpr (i == VariableTypeList<Ts...>::length)
                    {
                        return succeed;
                    }
                    else
                    {
                        using ValueType = OriginType<decltype(std::get<i>(value))>;
                        static_assert(SerializableToCSV<ValueType, CharT>);
                        static const ToCSVValue<ValueType, CharT> serializer{};
                        std::basic_ostringstream<CharT> sout;
                        OSPF_TRY_GET(this_value, serializer(sout, std::get<i>(value)));
                        sout << std::move(this_value);
                        if constexpr (i != (VariableTypeList<Ts...>::length - 1_uz))
                        {
                            sout << CharT{ ';' };
                        }
                        return serialize<i + 1_uz>(os, value);
                    }
                }
            };

            template<typename... Ts, CharType CharT>
            struct ToCSVValue<std::variant<Ts...>, CharT>
            {
                inline Result<std::basic_string<CharT>> operator()(const std::variant<Ts...>& value) const noexcept
                {
                    return std::visit([](const auto& this_value)
                        {
                            using ValueType = OriginType<decltype(this_value)>;
                            static_assert(SerializableToCSV<ValueType, CharT>);
                            static const ToCSVValue<ValueType, CharT> serializer{};
                            return serializer(this_value);
                        }, value);
                }
            };

            template<typename T, typename U, CharType CharT>
                requires SerializableToCSV<T, CharT> && SerializableToCSV<U, CharT>
            struct ToCSVValue<Either<T, U>, CharT>
            {
                inline Result<std::basic_string<CharT>> operator()(const Either<T, U>& value) const noexcept
                {
                    return std::visit([](const auto& this_value)
                        {
                            using ValueType = OriginType<decltype(this_value)>;
                            static const ToCSVValue<ValueType, CharT> serializer{};
                            return serializer(this_value);
                        }, value);
                }
            };

            template<typename T, reference::ReferenceCategory cat, CopyOnWrite cow, CharType CharT>
                requires SerializableToCSV<T, CharT>
            struct ToCSVValue<ValOrRef<T, cat, cow>, CharT>
            {
                inline Result<std::basic_string<CharT>> operator()(const ValOrRef<T, cat, cow>& value) const noexcept
                {
                    static const ToCSVValue<OriginType<T>, CharT> serializer{};
                    return serializer(*value);
                }
            };

            template<typename T, usize len, CharType CharT>
                requires SerializableToCSV<T, CharT>
            struct ToCSVValue<std::array<T, len>, CharT>
            {
                inline Result<std::basic_string<CharT>> operator()(const std::array<T, len> values) const noexcept
                {
                    std::basic_ostringstream<CharT> sout;
                    static const ToCSVValue<OriginType<T>, CharT> serializer{};
                    for (usize i{ 0_uz }; i != values.size(); ++i)
                    {
                        OSPF_TRY_GET(this_value, serializer(values[i]));
                        sout << std::move(this_value);
                        if (i != (values.size() - 1_uz); ++i)
                        {
                            sout << CharT{ ',' };
                        }
                    }
                    return sout.str();
                }
            };

            template<typename T, CharType CharT>
                requires SerializableToCSV<T, CharT>
            struct ToCSVValue<std::vector<T>, CharT>
            {
                inline Result<std::basic_string<CharT>> operator()(const std::vector<T>& values) const noexcept
                {
                    std::basic_ostringstream<CharT> sout;
                    static const ToCSVValue<OriginType<T>, CharT> serializer{};
                    for (usize i{ 0_uz }; i != values.size(); ++i)
                    {
                        OSPF_TRY_GET(this_value, serializer(values[i]));
                        sout << std::move(this_value);
                        if (i != (values.size() - 1_uz); ++i)
                        {
                            sout << CharT{ ',' };
                        }
                    }
                    return sout.str();
                }
            };

            template<typename T, CharType CharT>
                requires SerializableToCSV<T, CharT>
            struct ToCSVValue<std::deque<T>, CharT>
            {
                inline Result<std::basic_string<CharT>> operator()(const std::deque<T>& values) const noexcept
                {
                    std::basic_ostringstream<CharT> sout;
                    static const ToCSVValue<OriginType<T>, CharT> serializer{};
                    for (usize i{ 0_uz }; i != values.size(); ++i)
                    {
                        OSPF_TRY_GET(this_value, serializer(values[i]));
                        sout << std::move(this_value);
                        if (i != (values.size() - 1_uz); ++i)
                        {
                            sout << CharT{ ',' };
                        }
                    }
                    return sout.str();
                }
            };

            template<typename T, usize len, CharType CharT>
                requires SerializableToCSV<T, CharT>
            struct ToCSVValue<std::span<T, len>, CharT>
            {
                inline Result<std::basic_string<CharT>> operator()(const std::span<T, len> values) const noexcept
                {
                    std::basic_ostringstream<CharT> sout;
                    static const ToCSVValue<OriginType<T>, CharT> serializer{};
                    for (usize i{ 0_uz }; i != values.size(); ++i)
                    {
                        OSPF_TRY_GET(this_value, serializer(values[i]));
                        sout << std::move(this_value);
                        if (i != (values.size() - 1_uz); ++i)
                        {
                            sout << CharT{ ',' };
                        }
                    }
                    return sout.str();
                }
            };

            // todo: optional_array, pointer_array, reference_array, tagged_map, value_or_reference_array

            template<>
            struct ToCSVValue<bool, char>
            {
                inline Result<std::string> operator()(const bool value) const noexcept
                {
                    return from_bool(value);
                }
            };

            template<>
            struct ToCSVValue<u8, char>
            {
                inline Result<std::string> operator()(const u8 value) const noexcept
                {
                    return from_u8(value);
                }
            };

            template<>
            struct ToCSVValue<i8, char>
            {
                inline Result<std::string> operator()(const i8 value) const noexcept
                {
                    return from_i8(value);
                }
            };

            template<>
            struct ToCSVValue<u16, char>
            {
                inline Result<std::string> operator()(const u16 value) const noexcept
                {
                    return from_u16(value);
                }
            };

            template<>
            struct ToCSVValue<i16, char>
            {
                inline Result<std::string> operator()(const i16 value) const noexcept
                {
                    return from_i16(value);
                }
            };

            template<>
            struct ToCSVValue<u32, char>
            {
                inline Result<std::string> operator()(const u32 value) const noexcept
                {
                    return from_u32(value);
                }
            };

            template<>
            struct ToCSVValue<i32, char>
            {
                inline Result<std::string> operator()(const i32 value) const noexcept
                {
                    return from_i32(value);
                }
            };

            template<>
            struct ToCSVValue<u64, char>
            {
                inline Result<std::string> operator()(const u64 value) const noexcept
                {
                    return from_u64(value);
                }
            };

            template<>
            struct ToCSVValue<i64, char>
            {
                inline Result<std::string> operator()(const i64 value) const noexcept
                {
                    return from_i64(value);
                }
            };

            template<>
            struct ToCSVValue<f32, char>
            {
                inline Result<std::string> operator()(const f32 value) const noexcept
                {
                    return from_f32(value);
                }
            };

            template<>
            struct ToCSVValue<f64, char>
            {
                inline Result<std::string> operator()(const f64 value) const noexcept
                {
                    return from_f64(value);
                }
            };

            template<>
            struct ToCSVValue<std::string, char>
            {
                inline Result<std::string> operator()(const std::string& value) const noexcept
                {
                    return value;
                }
            };

            template<>
            struct ToCSVValue<std::string_view, char>
            {
                inline Result<std::string> operator()(const std::string_view value) const noexcept
                {
                    return std::string{ value };
                }
            };
        };
    };
};
