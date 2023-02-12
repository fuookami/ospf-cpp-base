#pragma once

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
            template<SerializableToJson T, typename CharT = char>
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
                        OSPF_TRY_GET(value, this->operator()(obj, doc));
                        doc.PushBack(value.Move());
                    }
                    return std::move(doc);
                }

                inline Result<rapidjson::Value> operator()(const ValueType& obj, rapidjson::Document& doc) const noexcept
                {
                    const ToJsonValue<ValueType> serializer{};
                    return serializer(obj, doc, _transfer);
                }

                template<usize len>
                inline Result<rapidjson::Value> operator()(const std::span<const ValueType, len> objs, rapidjson::Document& doc) const noexcept
                {
                    rapidjson::Value value{ rapidjson::kArrayType };
                    const ToJsonValue<ValueType> serializer{};
                    for (const auto& obj : objs)
                    {
                        OSPF_TRY_GET(value, serializer(obj, doc, _transfer));
                        value.PushBack(value.Move());
                    }
                    return std::move(value);
                }

            private:
                template<typename = void>
                    requires WithMetaInfo<ValueType>
                inline Try<> serialize(rapidjson::Value& value, const ValueType& obj, rapidjson::Document& doc) const noexcept
                {
                    static constexpr const meta_info::MetaInfo<ValueType> info{};
                    value.SetObject();
                    std::optional<OSPFError> err;
                    info.for_each(obj, [this, &err, &value, &doc](const auto& obj, const auto& field)
                        {
                            static_assert(SerializableToJson<decltype(field.value(obj))>);

                            if (err.has_value())
                            {
                                return;
                            }

                            const auto key = this->_transfer.has_value() ? (*this->_transfer)(field.key()) : field.key();
                            const ToJsonValue<OriginType<decltype(field.value(obj))>> serializer{};
                            auto value = serializer(field.value(obj));
                            if (value.failed())
                            {
                                err = OSPFError{ OSPFErrCode::SerializationFail, std::format("failed serializing field \"{}\" for type\"{}\", {}", field.key(), TypeInfo<T>::name(), value.err().message()) };
                                return;
                            }
                            else
                            {
                                value.AddMember(rapidjson::StringRef(key.data()), value.unwrap().Move(), doc.GetAllocator());
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
