#pragma once

#include <ospf/basic_definition.hpp>
#include <ospf/ospf_base_api.hpp>
#include <ospf/functional/result.hpp>
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
            concept DeserializableFromJson = requires (const FromJsonValue<T> deserializer)
            {
                { deserializer(std::declval<rapidjson::Value>()) } -> DecaySameAs<Result<T>>;
            };

            template<EnumType T>
            struct FromJsonValue<T>
            {
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
                    return OSPFError{ OSPFErrCode::DeserializationFail, std::format("invalid value {} for enum {}", value, TypeInfo<T>::name()) };
                }
            };

            // todo: optional, ptr, variant, either, val/ref
        };
    };
};
