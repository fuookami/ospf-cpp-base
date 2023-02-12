﻿#pragma once

#include <ospf/serialization/json/io.hpp>
#include <ospf/serialization/json/to_value.hpp>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace ospf
{
    inline namespace serialization
    {
        namespace json
        {
            template<typename T, typename CharT = char>
                requires SerializableToJson<T, CharT>
            class Serializer
            {
            public:
                using ValueType = OriginType<T>;

            public:
                Serializer(void) = default;
                Serializer(NameTransfer<CharT> transfer)
                    : _transfer(std::move(transfer)) {}
                Serializer(const Serializer& ano) = default;
                Serializer(Serializer&& ano) noexcept = default;
                Serializer& operator=(const Serializer& rhs) = default;
                Serializer& operator=(Serializer&& rhs) noexcept = default;
                ~Serializer(void) noexcept = default;

            public:
                template<typename = void>
                    requires WithMetaInfo<ValueType>
                inline Result<rapidjson::Document> operator()(const ValueType& obj) const noexcept
                {
                    rapidjson::Document doc;
                    doc.SetObject();
                    OSPF_TRY_EXEC(serialize(doc, obj, doc));
                    return std::move(doc);
                }

                template<usize len>
                inline Result<rapidjson::Document> operator()(const std::span<const ValueType, len> objs) const noexcept
                {
                    rapidjson::Document doc;
                    doc.SetArray();
                    for (const auto& obj : objs)
                    {
                        OSPF_TRY_GET(json, this->operator()(obj, doc));
                        doc.PushBack(json.Move());
                    }
                    return std::move(doc);
                }

                inline Result<rapidjson::Value> operator()(const ValueType& obj, rapidjson::Document& doc) const noexcept
                {
                    const ToJsonValue<ValueType, CharT> serializer{};
                    return serializer(obj, doc, _transfer);
                }

                template<usize len>
                inline Result<rapidjson::Value> operator()(const std::span<const ValueType, len> objs, rapidjson::Document& doc) const noexcept
                {
                    rapidjson::Value json{ rapidjson::kArrayType };
                    const ToJsonValue<ValueType, CharT> serializer{};
                    for (const auto& obj : objs)
                    {
                        OSPF_TRY_GET(sub_json, serializer(obj, doc, _transfer));
                        json.PushBack(sub_json.Move());
                    }
                    return std::move(json);
                }

            private:
                template<typename = void>
                    requires WithMetaInfo<ValueType>
                inline Try<> serialize(rapidjson::Value& json, const ValueType& obj, rapidjson::Document& doc) const noexcept
                {
                    static constexpr const meta_info::MetaInfo<ValueType> info{};
                    json.SetObject();
                    std::optional<OSPFError> err;
                    info.for_each(obj, [this, &err, &value, &doc](const auto& obj, const auto& field)
                        {
                            using FieldValueType = OriginType<decltype(field.value(obj))>;
                            static_assert(SerializableToJson<FieldValueType, CharT>);

                            if (err.has_value())
                            {
                                return;
                            }

                            const auto key = this->_transfer.has_value() ? (*this->_transfer)(field.key()) : field.key();
                            const ToJsonValue<FieldValueType, CharT> serializer{};
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
                        return succeed;
                    }
                }

            private:
                std::optional<NameTransfer<CharT>> _transfer;
            };

            template<typename T, typename CharT = char>
            inline Try<> to_file
            (
                const std::filesystem::path& path,
                const T& obj,
                std::optional<NameTransfer<CharT>> transfer = meta_programming::NameTransfer<NamingSystem::Underscore, NamingSystem::Camelcase, CharT>{}
            ) noexcept
            {
                if (!std::filesystem::exists(path))
                {
                    return OSPFError{ OSPFErrCode::FileNotFound, std::format("\"{}\" not exist", path) };
                }
                if (std::filesystem::is_directory(path))
                {
                    return OSPFError{ OSPFErrCode::NotAFile, std::format("\"{}\" is not a file", path) };
                }

                auto serializer = transfer.has_value() ? Serializer<T, CharT>{ std::move(transfer).value() } : Serializer<T, CharT>{};
                OSPF_TRY_GET(doc, serializer(obj));

                std::basic_ofstream<CharT> fout{ path };
                OSPF_TRY_EXEC(write(fout, doc));
                return succeed;
            }

            template<typename T, usize len, typename CharT = char>
            inline Try<> to_file
            (
                const std::filesystem::path& path,
                const std::span<const T, len> objs,
                std::optional<NameTransfer<CharT>> transfer = meta_programming::NameTransfer<NamingSystem::Underscore, NamingSystem::Camelcase, CharT>{}
            ) noexcept
            {
                if (!std::filesystem::exists(path))
                {
                    return OSPFError{ OSPFErrCode::FileNotFound, std::format("\"{}\" not exist", path) };
                }
                if (std::filesystem::is_directory(path))
                {
                    return OSPFError{ OSPFErrCode::NotAFile, std::format("\"{}\" is not a file", path) };
                }

                auto serializer = transfer.has_value() ? Serializer<T, CharT>{ std::move(transfer).value() } : Serializer<T, CharT>{};
                OSPF_TRY_GET(doc, serializer(objs));

                std::basic_ofstream<CharT> fout{ path };
                OSPF_TRY_EXEC(write(fout, doc));
                return succeed;
            }

            template<typename T, typename CharT = char>
            inline Result<std::basic_string<CharT>> to_string
            (
                const T& obj,
                std::optional<NameTransfer<CharT>> transfer = meta_programming::NameTransfer<NamingSystem::Underscore, NamingSystem::Camelcase, CharT>{}
            ) noexcept
            {
                auto serializer = transfer.has_value() ? Serializer<T, CharT>{ std::move(transfer).value() } : Serializer<T, CharT>{};
                OSPF_TRY_GET(doc, serializer(obj));

                std::basic_ostringstream<CharT> sout;
                OSPF_TRY_EXEC(write(sout, doc));
                return succeed;
            }

            template<typename T, usize len, typename CharT = char>
            inline Result<std::basic_string<CharT>> to_string
            (
                const std::span<const T, len> objs,
                std::optional<NameTransfer<CharT>> transfer = meta_programming::NameTransfer<NamingSystem::Underscore, NamingSystem::Camelcase, CharT>{}
            ) noexcept
            {
                auto serializer = transfer.has_value() ? Serializer<T, CharT>{ std::move(transfer).value() } : Serializer<T, CharT>{};
                OSPF_TRY_GET(doc, serializer(objs));

                std::basic_ostringstream<CharT> sout;
                OSPF_TRY_EXEC(write(fout, doc));
                return succeed;
            }

            template<typename T, typename CharT = char>
            inline Result<rapidjson::Value> to_value
            (
                const T& obj,
                rapidjson::Document& doc,
                std::optional<NameTransfer<CharT>> transfer = meta_programming::NameTransfer<NamingSystem::Underscore, NamingSystem::Camelcase, CharT>{}
            )
            {
                auto serializer = transfer.has_value() ? Serializer<T, CharT>{ std::move(transfer).value() } : Serializer<T, CharT>{};
                return serializer(obj, doc);
            }

            template<typename T, usize len, typename CharT = char>
            inline Result<rapidjson::Value> to_value
            (
                const std::span<const T, len> objs,
                rapidjson::Document& doc,
                std::optional<NameTransfer<CharT>> transfer = meta_programming::NameTransfer<NamingSystem::Underscore, NamingSystem::Camelcase, CharT>{}
            )
            {
                auto serializer = transfer.has_value() ? Serializer<T, CharT>{ std::move(transfer).value() } : Serializer<T, CharT>{};
                return serializer(objs, doc);
            }

            // todo: to bytes
        };
    };
};
