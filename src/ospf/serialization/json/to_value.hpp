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
            OSPF_BASE_API rapidjson::Value from_bool(const bool value, rapidjson::Document& doc) noexcept;
            OSPF_BASE_API rapidjson::Value from_u8(const u8 value, rapidjson::Document& doc) noexcept;
            OSPF_BASE_API rapidjson::Value from_i8(const i8 value, rapidjson::Document& doc) noexcept;
            OSPF_BASE_API rapidjson::Value from_u16(const u16 value, rapidjson::Document& doc) noexcept;
            OSPF_BASE_API rapidjson::Value from_i16(const i16 value, rapidjson::Document& doc) noexcept;
            OSPF_BASE_API rapidjson::Value from_u32(const u32 value, rapidjson::Document& doc) noexcept;
            OSPF_BASE_API rapidjson::Value from_i32(const i32 value, rapidjson::Document& doc) noexcept;
            OSPF_BASE_API rapidjson::Value from_u64(const u64 value, rapidjson::Document& doc) noexcept;
            OSPF_BASE_API rapidjson::Value from_i64(const i64 value, rapidjson::Document& doc) noexcept;
            OSPF_BASE_API rapidjson::Value from_f32(const f32 value, rapidjson::Document& doc) noexcept;
            OSPF_BASE_API rapidjson::Value from_f64(const f64 value, rapidjson::Document& doc) noexcept;
            OSPF_BASE_API rapidjson::Value from_string(const std::string& value, rapidjson::Document& doc) noexcept;
            OSPF_BASE_API rapidjson::Value from_string_view(const std::string_view value, rapidjson::Document& doc) noexcept;

            // todo: big int, decimal and chrono

            template<typename T, typename CharT>
            struct ToJsonValue;

            template<typename T, typename CharT>
            concept SerializableToJson = requires (const ToJsonValue<T, CharT> serializer)
            {
                { serializer(std::declval<T>(), std::declval<rapidjson::Document>(), std::declval<std::optional<NameTransfer<CharT>>>()) } -> DecaySameAs<Result<rapidjson::Value>>;
            };

            template<EnumType T>
            struct ToJsonValue<T, char>
            {
                inline Result<rapidjson::Value> operator()(const T value, rapidjson::Document& doc, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    return rapidjson::Value{ to_string(value).data(), doc.GetAllocator() };
                }
            };

            template<WithMetaInfo T>
            struct ToJsonValue<T, char>
            {
                inline Result<rapidjson::Value> operator()(const T& obj, rapidjson::Document& doc, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    static constexpr const meta_info::MetaInfo<T> info{};
                    rapidjson::Value json{ rapidjson::kObjectType };
                    std::optional<OSPFError> err;
                    info.for_each(obj, [&ret, &err, &doc, &transfer](const auto& obj, const auto& field)
                        {
                            using FieldValueType = OriginType<decltype(field.value(obj))>;
                            static_assert(SerializableToJson<FieldValueType>);

                            if (err.has_value())
                            {
                                return;
                            }

                            const auto key = transfer.has_value() ? (*transfer)(field.key()) : field.key();
                            const ToJsonValue<FieldValueType, char> serializer{};
                            auto sub_json = serializer(field.value(obj));
                            if (sub_json.is_failed())
                            {
                                err = OSPFError{ OSPFErrCode::SerializationFail, std::format("failed serializing field \"{}\" for type\"{}\", {}", field.key(), TypeInfo<T>::name(), sub_json.err().message()) };
                                return;
                            }
                            else
                            {
                                json.AddMember(rapidjson::StringRef(key.data()), sub_json.unwrap().Move(), doc.GetAllocator());
                            }
                        });
                    if (err.has_value())
                    {
                        return std::move(err).value();
                    }
                    else
                    {
                        return std::move(json);
                    }
                }
            };

            // todo: optional, ptr, variant, either, val/ref

            template<>
            struct ToJsonValue<bool, char>
            {
                inline Result<rapidjson::Value> operator()(const bool value, rapidjson::Document& doc, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    return from_bool(value, doc);
                }
            };

            template<>
            struct ToJsonValue<u8, char>
            {
                inline Result<rapidjson::Value> operator()(const u8 value, rapidjson::Document& doc, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    return from_u8(value, doc);
                }
            };

            template<>
            struct ToJsonValue<i8, char>
            {
                inline Result<rapidjson::Value> operator()(const i8 value, rapidjson::Document& doc, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    return from_i8(value, doc);
                }
            };

            template<>
            struct ToJsonValue<u16, char>
            {
                inline Result<rapidjson::Value> operator()(const u16 value, rapidjson::Document& doc, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    return from_u16(value, doc);
                }
            };

            template<>
            struct ToJsonValue<i16, char>
            {
                inline Result<rapidjson::Value> operator()(const i16 value, rapidjson::Document& doc, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    return from_i16(value, doc);
                }
            };

            template<>
            struct ToJsonValue<u32, char>
            {
                inline Result<rapidjson::Value> operator()(const u32 value, rapidjson::Document& doc, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    return from_u32(value, doc);
                }
            };

            template<>
            struct ToJsonValue<i32, char>
            {
                inline Result<rapidjson::Value> operator()(const i32 value, rapidjson::Document& doc, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    return from_i32(value, doc);
                }
            };

            template<>
            struct ToJsonValue<u64, char>
            {
                inline Result<rapidjson::Value> operator()(const u64 value, rapidjson::Document& doc, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    return from_u64(value, doc);
                }
            };

            template<>
            struct ToJsonValue<i64, char>
            {
                inline Result<rapidjson::Value> operator()(const i64 value, rapidjson::Document& doc, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    return from_i64(value, doc);
                }
            };

            template<>
            struct ToJsonValue<f32, char>
            {
                inline Result<rapidjson::Value> operator()(const f32 value, rapidjson::Document& doc, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    return from_f32(value, doc);
                }
            };

            template<>
            struct ToJsonValue<f64, char>
            {
                inline Result<rapidjson::Value> operator()(const f64 value, rapidjson::Document& doc, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    return from_f64(value, doc);
                }
            };

            template<>
            struct ToJsonValue<std::string, char>
            {
                inline Result<rapidjson::Value> operator()(const std::string& value, rapidjson::Document& doc, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    return from_string(value, doc);
                }
            };

            template<>
            struct ToJsonValue<std::string_view, char>
            {
                inline Result<rapidjson::Value> operator()(const std::string& value, rapidjson::Document& doc, const std::optional<NameTransfer<char>>& transfer) const noexcept
                {
                    return from_string_view(value, doc);
                }
            };
        };
    };
};
