#pragma once

#include <ospf/basic_definition.hpp>
#include <ospf/ospf_base_api.hpp>
#include <ospf/functional/result.hpp>
#include <ospf/meta_programming/meta_info.hpp>
#include <ospf/serialization/json/concepts.hpp>
#include <rapidjson/document.h>

namespace ospf
{
    inline namespace serialization
    {
        namespace json
        {
            OSPF_BASE_API std::optional<bool> to_bool(const rapidjson::Value& json) noexcept;
            OSPF_BASE_API std::optional<u8> to_u8(const rapidjson::Value& json) noexcept;
            OSPF_BASE_API std::optional<i8> to_i8(const rapidjson::Value& json) noexcept;
            OSPF_BASE_API std::optional<u16> to_u16(const rapidjson::Value& json) noexcept;
            OSPF_BASE_API std::optional<i16> to_i16(const rapidjson::Value& json) noexcept;
            OSPF_BASE_API std::optional<u32> to_u32(const rapidjson::Value& json) noexcept;
            OSPF_BASE_API std::optional<i32> to_i32(const rapidjson::Value& json) noexcept;
            OSPF_BASE_API std::optional<u64> to_u64(const rapidjson::Value& json) noexcept;
            OSPF_BASE_API std::optional<i64> to_i64(const rapidjson::Value& json) noexcept;
            OSPF_BASE_API std::optional<f32> to_f32(const rapidjson::Value& json) noexcept;
            OSPF_BASE_API std::optional<f64> to_f64(const rapidjson::Value& json) noexcept;
            OSPF_BASE_API std::optional<std::string> to_string(const rapidjson::Value& json) noexcept;

            // todo: big int, decimal and chrono

            template<typename T, CharType CharT>
            struct FromJsonValue;

            template<typename T, typename CharT>
            concept DeserializableFromJson = CharType<CharT> && (requires (const FromJsonValue<T, CharT>& deserializer)
                {
                    { deserializer(std::declval<rapidjson::Value>(), std::declval<T>(), std::declval<std::optional<NameTransfer<CharT>>>()) } -> DecaySameAs<Try<>>;
                }) 
                && (!std::default_initializable<T> || requires (const FromJsonValue<T, CharT>& deserializer)
                {
                    { deserializer(std::declval<rapidjson::Value>(), std::declval<std::optional<NameTransfer<CharT>>>()) } -> DecaySameAs<Result<T>>;
                });

            template<EnumType T, CharType CharT>
            struct FromJsonValue<T, CharT>
            {
                inline Try<> operator()(const rapidjson::Value& json, T& value, const std::optional<NameTransfer<CharT>>& transfer) const noexcept
                {
                    OSPF_TRY_SET(value, this->operator()(json));
                    return succeed;
                }

                inline Result<T> operator()(const rapidjson::Value& json, const std::optional<NameTransfer<CharT>>& transfer) const noexcept
                {
                    if (json.IsString())
                    {
                        const auto enum_value = parse_enum<T, CharT>(json.GetString());
                        if (enum_value.has_value())
                        {
                            return *enum_value;
                        }
                    }
                    else if (json.IsUint64())
                    {
                        const auto enum_value = magic_enum::enum_cast<T>(json.GetUint64());
                        if (enum_value.has_value())
                        {
                            return *enum_value;
                        }
                    }
                    return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for enum \"{}\"", json, TypeInfo<T>::name()) };
                }
            };

            template<WithMetaInfo T, CharType CharT>
            struct FromJsonValue<T, CharT>
            {
                inline Try<> operator()(const rapidjson::Value& json, T& obj, const std::optional<NameTransfer<CharT>>& transfer) const noexcept
                {
                    static constexpr const meta_info::MetaInfo<T> info{};
                    std::optional<OSPFError> err;
                    info.for_each(obj, [&err, &json, &transfer](auto& obj, const auto& field)
                        {
                            if constexpr (!field.writable())
                            {
                                return;
                            }
                            else
                            {
                                using FieldValueType = OriginType<decltype(field.value(obj))>;
                                static_assert(DeserializableFromJson<FieldValueType, CharT>);

                                if (err.has_value())
                                {
                                    return;
                                }

                                const auto key = transfer.has_value() ? (*transfer)(field.key()) : field.key();
                                if (!json.HasMember(key.data()))
                                {
                                    if constexpr (serialization_nullable<FieldValueType>)
                                    {
                                        return;
                                    }
                                    else
                                    {
                                        err = OSPFError{ OSPFErrCode::DeserializationFail, std::format("lost non-nullable field \"{}\" for type {}", field.key(), TypeInfo<T>::name()) };
                                    }
                                }
                                else
                                {
                                    const auto deserializer = FromJsonValue<FieldValueType, CharT>{};
                                    auto value = deserializer(json, transfer);
                                    if constexpr (!serialization_nullable<FieldValueType>)
                                    {
                                        if (value.is_failed())
                                        {
                                            err = OSPFError{ OSPFErrCode::DeserializationFail, std::format("failed deserializing field \"{}\" for type {}, {}", field.key(), TypeInfo<T>::name(), value.err().message()) };
                                            return;
                                        }
                                    }
                                    if (value.is_successful())
                                    {
                                        field.value(obj) = std::move(value).unwrap();
                                    }
                                }
                            }
                        });
                    return succeed;
                }

                template<typename = void>
                    requires std::default_initializable<T>
                inline Result<T> operator()(const rapidjson::Value& json, const std::optional<NameTransfer<CharT>>& transfer) const noexcept
                {
                    T obj{};
                    OSPF_TRY_EXEC(this->operator()(json, obj));
                    return std::move(obj);
                }
            };

            // todo: optional, ptr, variant, either, val/ref, range 

            template<>
            struct FromJsonValue<u8, char>
            {
                inline Try<> operator()(const rapidjson::Value& json, u8& value, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    const auto u8_value = to_u8(json);
                    if (u8_value.has_value())
                    {
                        value = u8_value.value();
                        return succeed;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid json \"{}\" for u8", json) };
                    }
                }

                inline Result<u8> operator()(const rapidjson::Value& json, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    u8 value{ 0_u8 };
                    OSPF_TRY_EXEC(this->operator()(json, value, transfer));
                    return value;
                }
            };

            template<>
            struct FromJsonValue<i8, char>
            {
                inline Try<> operator()(const rapidjson::Value& json, i8& value, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    const auto i8_value = to_i8(json);
                    if (i8_value.has_value())
                    {
                        value = i8_value.value();
                        return succeed;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid json \"{}\" for i8", json) };
                    }
                }

                inline Result<i8> operator()(const rapidjson::Value& json, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    i8 value{ 0_i8 };
                    OSPF_TRY_EXEC(this->operator()(json, value, transfer));
                    return value;
                }
            };

            template<>
            struct FromJsonValue<u16, char>
            {
                inline Try<> operator()(const rapidjson::Value& json, u16& value, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    const auto u16_value = to_u16(json);
                    if (u16_value.has_value())
                    {
                        value = u16_value.value();
                        return succeed;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for u16", value) };
                    }
                }

                inline Result<u16> operator()(const rapidjson::Value& json, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    u16 value{ 0_u16 };
                    OSPF_TRY_EXEC(this->operator()(json, value, transfer));
                    return value;
                }
            };

            template<>
            struct FromJsonValue<i16, char>
            {
                inline Try<> operator()(const rapidjson::Value& json, i16& value, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    const auto i16_value = to_i16(json);
                    if (i16_value.has_value())
                    {
                        value = i16_value.value();
                        return succeed;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for i16", value) };
                    }
                }

                inline Result<i16> operator()(const rapidjson::Value& json, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    i16 value{ 0_i16 };
                    OSPF_TRY_EXEC(this->operator()(json, value, transfer));
                    return value;
                }
            };

            template<>
            struct FromJsonValue<u32, char>
            {
                inline Try<> operator()(const rapidjson::Value& json, u32& value, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    const auto u32_value = to_u32(json);
                    if (u32_value.has_value())
                    {
                        value = u32_value.value();
                        return succeed;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for u32", value) };
                    }
                }

                inline Result<u32> operator()(const rapidjson::Value& json, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    u32 value{ 0_u32 };
                    OSPF_TRY_EXEC(this->operator()(json, value, transfer));
                    return value;
                }
            };

            template<>
            struct FromJsonValue<i32, char>
            {
                inline Try<> operator()(const rapidjson::Value& json, i32& value, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    const auto i32_value = to_i32(json);
                    if (i32_value.has_value())
                    {
                        value = i32_value.value();
                        return succeed;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for i32", value) };
                    }
                }

                inline Result<i32> operator()(const rapidjson::Value& json, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    i32 value{ 0_i32 };
                    OSPF_TRY_EXEC(this->operator()(json, value, transfer));
                    return value;
                }
            };

            template<>
            struct FromJsonValue<u64, char>
            {
                inline Try<> operator()(const rapidjson::Value& json, u64& value, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    const auto u64_value = to_u64(json);
                    if (u64_value.has_value())
                    {
                        value = u64_value.value();
                        return succeed;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for u64", value) };
                    }
                }

                inline Result<u64> operator()(const rapidjson::Value& json, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    u64 value{ 0_u64 };
                    OSPF_TRY_EXEC(this->operator()(json, value, transfer));
                    return value;
                }
            };

            template<>
            struct FromJsonValue<i64, char>
            {
                inline Try<> operator()(const rapidjson::Value& json, i64& value, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    const auto i64_value = to_i64(json);
                    if (i64_value.has_value())
                    {
                        value = i64_value.value();
                        return succeed;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for i64", value) };
                    }
                }

                inline Result<i64> operator()(const rapidjson::Value& json, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    i64 value{ 0_i64 };
                    OSPF_TRY_EXEC(this->operator()(json, value, transfer));
                    return value;
                }
            };

            template<>
            struct FromJsonValue<std::string, char>
            {
                inline Try<> operator()(const rapidjson::Value& json, std::string& value, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    const auto u64_value = to_string(json);
                    if (u64_value.has_value())
                    {
                        value = std::move(u64_value).value();
                        return succeed;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for std::string", value) };
                    }
                }

                inline Result<std::string> operator()(const rapidjson::Value& json, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    std::string value{};
                    OSPF_TRY_EXEC(this->operator()(json, value, transfer));
                    return value;
                }
            };
        };
    };
};
