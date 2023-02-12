#pragma once

#include <ospf/basic_definition.hpp>
#include <ospf/ospf_base_api.hpp>
#include <ospf/functional/result.hpp>
#include <ospf/meta_programming/meta_info.hpp>
#include <ospf/serialization/json/concept.hpp>
#include <rapidjson/document.h>

namespace ospf
{
    inline namespace serialization
    {
        namespace json
        {
            OSPF_BASE_API std::optional<bool> to_bool(const rapidjson::Value& value) noexcept;
            OSPF_BASE_API std::optional<u8> to_u8(const rapidjson::Value& value) noexcept;
            OSPF_BASE_API std::optional<i8> to_i8(const rapidjson::Value& value) noexcept;
            OSPF_BASE_API std::optional<u16> to_u16(const rapidjson::Value& value) noexcept;
            OSPF_BASE_API std::optional<i16> to_i16(const rapidjson::Value& value) noexcept;
            OSPF_BASE_API std::optional<u32> to_u32(const rapidjson::Value& value) noexcept;
            OSPF_BASE_API std::optional<i32> to_i32(const rapidjson::Value& value) noexcept;
            OSPF_BASE_API std::optional<u64> to_u64(const rapidjson::Value& value) noexcept;
            OSPF_BASE_API std::optional<i64> to_i64(const rapidjson::Value& value) noexcept;
            OSPF_BASE_API std::optional<f32> to_f32(const rapidjson::Value& value) noexcept;
            OSPF_BASE_API std::optional<f64> to_f64(const rapidjson::Value& value) noexcept;
            OSPF_BASE_API std::optional<std::string> to_string(const rapidjson::Value& value) noexcept;

            // todo: big int, decimal and chrono

            template<typename T>
            struct FromJsonValue;

            template<typename T>
            concept DeserializableFromJson = (requires (const FromJsonValue<T> deserializer)
                {
                    { deserializer(std::declval<rapidjson::Value>(), std::declval<T>()) } -> DecaySameAs<Try<>>;
                }) 
                && (!std::default_initializable<T> || requires (const FromJsonValue<T> deserializer)
                {
                    { deserializer(std::declval<rapidjson::Value>()) } -> DecaySameAs<Result<T>>;
                });

            template<EnumType T>
            struct FromJsonValue<T>
            {
                inline Try<> operator()(const rapidjson::Value& value, T& obj) const noexcept
                {
                    OSPF_TRY_SET(obj, this->operator()(value));
                    return succeed;
                }

                inline Result<T> operator()(const rapidjson::Value& value) const noexcept
                {
                    if (value.IsString())
                    {
                        const auto enum_value = magic_enum::enum_cast<T>(value.GetString());
                        if (enum_value.has_value())
                        {
                            return *enum_value;
                        }
                    }
                    else if (value.IsUint64())
                    {
                        const auto enum_value = magic_enum::enum_cast<T>(value.GetUint64());
                        if (enum_value.has_value())
                        {
                            return *enum_value;
                        }
                    }
                    return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for enum \"{}\"", value, TypeInfo<T>::name()) };
                }
            };

            template<WithMetaInfo T>
            struct FromJsonValue<T>
            {
                inline Try<> operator()(const rapidjson::Value& value, T& obj) const noexcept
                {
                    // todo
                    return succeed;
                }

                template<typename = void>
                    requires std::default_initializable<T>
                inline Result<T> operator()(const rapidjson::Value& value) const noexcept
                {
                    T obj{};
                    OSPF_TRY_EXEC(this->operator()(value, obj));
                    return std::move(obj);
                }
            };

            // todo: optional, ptr, variant, either, val/ref

            template<>
            struct FromJsonValue<u8>
            {
                inline Try<> operator()(const rapidjson::Value& value, u8& obj) const noexcept
                {
                    const auto obj_value = to_u8(value);
                    if (obj_value.has_value())
                    {
                        obj = obj_value.value();
                        return succeed;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for u8", value) };
                    }
                }

                inline Result<u8> operator()(const rapidjson::Value& value) const noexcept
                {
                    u8 obj{ 0_u8 };
                    OSPF_TRY_EXEC(this->operator()(value, obj));
                    return obj;
                }
            };

            template<>
            struct FromJsonValue<i8>
            {
                inline Try<> operator()(const rapidjson::Value& value, i8& obj) const noexcept
                {
                    const auto obj_value = to_i8(value);
                    if (obj_value.has_value())
                    {
                        obj = obj_value.value();
                        return succeed;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for i8", value) };
                    }
                }

                inline Result<i8> operator()(const rapidjson::Value& value) const noexcept
                {
                    i8 obj{ 0_i8 };
                    OSPF_TRY_EXEC(this->operator()(value, obj));
                    return obj;
                }
            };

            template<>
            struct FromJsonValue<u16>
            {
                inline Try<> operator()(const rapidjson::Value& value, u16& obj) const noexcept
                {
                    const auto obj_value = to_u16(value);
                    if (obj_value.has_value())
                    {
                        obj = obj_value.value();
                        return succeed;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for u16", value) };
                    }
                }

                inline Result<u16> operator()(const rapidjson::Value& value) const noexcept
                {
                    u16 obj{ 0_u16 };
                    OSPF_TRY_EXEC(this->operator()(value, obj));
                    return obj;
                }
            };

            template<>
            struct FromJsonValue<i16>
            {
                inline Try<> operator()(const rapidjson::Value& value, i16& obj) const noexcept
                {
                    const auto obj_value = to_i16(value);
                    if (obj_value.has_value())
                    {
                        obj = obj_value.value();
                        return succeed;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for i16", value) };
                    }
                }

                inline Result<i16> operator()(const rapidjson::Value& value) const noexcept
                {
                    i16 obj{ 0_i16 };
                    OSPF_TRY_EXEC(this->operator()(value, obj));
                    return obj;
                }
            };

            template<>
            struct FromJsonValue<u32>
            {
                inline Try<> operator()(const rapidjson::Value& value, u32& obj) const noexcept
                {
                    const auto obj_value = to_u32(value);
                    if (obj_value.has_value())
                    {
                        obj = obj_value.value();
                        return succeed;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for u32", value) };
                    }
                }

                inline Result<u32> operator()(const rapidjson::Value& value) const noexcept
                {
                    u32 obj{ 0_u32 };
                    OSPF_TRY_EXEC(this->operator()(value, obj));
                    return obj;
                }
            };

            template<>
            struct FromJsonValue<i32>
            {
                inline Try<> operator()(const rapidjson::Value& value, i32& obj) const noexcept
                {
                    const auto obj_value = to_i32(value);
                    if (obj_value.has_value())
                    {
                        obj = obj_value.value();
                        return succeed;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for i32", value) };
                    }
                }

                inline Result<i32> operator()(const rapidjson::Value& value) const noexcept
                {
                    i32 obj{ 0_i32 };
                    OSPF_TRY_EXEC(this->operator()(value, obj));
                    return obj;
                }
            };

            template<>
            struct FromJsonValue<u64>
            {
                inline Try<> operator()(const rapidjson::Value& value, u64& obj) const noexcept
                {
                    const auto obj_value = to_u64(value);
                    if (obj_value.has_value())
                    {
                        obj = obj_value.value();
                        return succeed;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for u64", value) };
                    }
                }

                inline Result<u64> operator()(const rapidjson::Value& value) const noexcept
                {
                    u64 obj{ 0_u64 };
                    OSPF_TRY_EXEC(this->operator()(value, obj));
                    return obj;
                }
            };

            template<>
            struct FromJsonValue<i64>
            {
                inline Try<> operator()(const rapidjson::Value& value, i64& obj) const noexcept
                {
                    const auto obj_value = to_i64(value);
                    if (obj_value.has_value())
                    {
                        obj = obj_value.value();
                        return succeed;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for i64", value) };
                    }
                }

                inline Result<i64> operator()(const rapidjson::Value& value) const noexcept
                {
                    i64 obj{ 0_i64 };
                    OSPF_TRY_EXEC(this->operator()(value, obj));
                    return obj;
                }
            };

            template<>
            struct FromJsonValue<std::string>
            {
                inline Try<> operator()(const rapidjson::Value& value, std::string& obj) const noexcept
                {
                    const auto obj_value = to_string(value);
                    if (obj_value.has_value())
                    {
                        obj = std::move(obj_value).value();
                        return succeed;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value \"{}\" for std::string", value) };
                    }
                }

                inline Result<std::string> operator()(const rapidjson::Value& value) const noexcept
                {
                    std::string obj{};
                    OSPF_TRY_EXEC(this->operator()(value, obj));
                    return obj;
                }
            };
        };
    };
};
