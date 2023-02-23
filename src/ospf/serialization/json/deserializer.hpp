#pragma once

#include <ospf/serialization/json/io.hpp>
#include <ospf/serialization/json/from_value.hpp>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace ospf
{
    inline namespace serialization
    {
        namespace json
        {
            // todo: impl multi-thread optimization

            template<typename T, CharType CharT = char>
                requires DeserializableFromJson<T, CharT>
            class Deserializer
            {
            public:
                using ValueType = OriginType<T>;

            public:
                Deserializer(void) = default;
                Deserializer(NameTransfer<CharT> transfer)
                    : _transfer(std::move(transfer)) {}
                Deserializer(const Deserializer& ano) = default;
                Deserializer(Deserializer&& ano) noexcept = default;
                Deserializer& operator=(const Deserializer& rhs) = default;
                Deserializer& operator=(Deserializer&& rhs) noexcept = default;
                ~Deserializer(void) noexcept = default;

            public:
                template<typename = void>
                    requires WithMetaInfo<ValueType> && WithDefault<ValueType>
                inline Result<ValueType> operator()(const Json<CharT>& json) const noexcept
                {
                    assert(value.IsObject());
                    static const FromJsonValue<ValueType, CharT> deserializer{};
                    return deserializer(json, _transfer);
                }

                template<typename = void>
                    requires WithMetaInfo<ValueType>
                inline Try<> operator()(const Json<CharT>& json, ValueType& obj) const noexcept
                {
                    assert(value.IsObject());
                    static const FromJsonValue<ValueType, CharT> deserializer{};
                    return deserializer(json, obj, _transfer);
                }

                template<typename = void>
                    requires WithDefault<ValueType>
                inline Result<std::vector<ValueType>> parse_array(const Json<CharT>& json) const noexcept
                {
                    assert(value.IsArray());
                    std::vector<ValueType> ret;
                    static const FromJsonValue<ValueType, CharT> deserializer{};
                    for (const auto& sub_json : json.GetArray())
                    {
                        OSPF_TRY_GET(obj, deserializer(sub_json, _transfer));
                        ret.push_back(std::move(obj));
                    }
                    return std::move(ret);
                }

                template<typename = void>
                    requires std::copy_constructible<ValueType>
                inline Result<std::vector<ValueType>> parse_array(const Json<CharT>& json, ValueType& origin_obj) const noexcept
                {
                    assert(value.IsArray());
                    std::vector<ValueType> ret;
                    static const FromJsonValue<ValueType, CharT> deserializer{};
                    for (const auto& sub_json : json.GetArray())
                    {
                        ValueType obj{ origin_obj };
                        OSPF_TRY_EXEC(deserializer(sub_json, obj, _transfer));
                        ret.push_back(std::move(obj));
                    }
                    return std::move(ret);
                }

            private:
                std::optional<NameTransfer<CharT>> _transfer;
            };

            template<typename T, CharType CharT = char>
                requires WithMetaInfo<T> && WithDefault<T>
            inline Result<T> from_file
            (
                const std::filesystem::path& path,
                std::optional<NameTransfer<CharT>> transfer = meta_programming::NameTransfer<NamingSystem::Camelcase, NamingSystem::Underscore, CharT>{}
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

                std::basic_ifstream<CharT> fin{ path };
                OSPF_TRY_GET(doc, read(fin));

                auto deserializer = transfer.has_value() ? Deserializer<T, CharT>{ std::move(transfer).value() } : Deserializer<T, CharT>{};
                OSPF_TRY_GET(obj, deserializer(doc));
                return std::move(obj);
            }

            template<typename T, CharType CharT = char>
                requires WithMetaInfo<T>
            inline Try<T> from_file
            (
                const std::filesystem::path& path,
                T& obj,
                std::optional<NameTransfer<CharT>> transfer = meta_programming::NameTransfer<NamingSystem::Camelcase, NamingSystem::Underscore, CharT>{}
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

                std::basic_ifstream<CharT> fin{ path };
                OSPF_TRY_GET(doc, read(fin));

                auto deserializer = transfer.has_value() ? Deserializer<T, CharT>{ std::move(transfer).value() } : Deserializer<T, CharT>{};
                OSPF_TRY_EXEC(deserializer(doc, obj));
                return succeed;
            }

            template<typename T, CharType CharT = char>
                requires WithDefault<T>
            inline Result<std::vector<T>> from_file_array
            (
                const std::filesystem::path& path,
                std::optional<NameTransfer<CharT>> transfer = meta_programming::NameTransfer<NamingSystem::Camelcase, NamingSystem::Underscore, CharT>{}
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

                std::basic_ifstream<CharT> fin{ path };
                OSPF_TRY_GET(doc, read(fin));
                assert(doc.IsArray());

                auto deserializer = transfer.has_value() ? Deserializer<T, CharT>{ std::move(transfer).value() } : Deserializer<T, CharT>{};
                OSPF_TRY_GET(objs, deserializer.parse_array(doc));
                return std::move(objs);
            }

            template<typename T, CharType CharT = char>
                requires std::copy_constructible<T>
            inline Result<std::vector<T>> from_file_array
            (
                const std::filesystem::path& path,
                std::vector<T>& origin_obj,
                std::optional<NameTransfer<CharT>> transfer = meta_programming::NameTransfer<NamingSystem::Camelcase, NamingSystem::Underscore, CharT>{}
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

                std::basic_ifstream<CharT> fin{ path };
                OSPF_TRY_GET(doc, read(fin));
                assert(doc.IsArray());

                auto deserializer = transfer.has_value() ? Deserializer<T, CharT>{ std::move(transfer).value() } : Deserializer<T, CharT>{};
                OSPF_TRY_GET(objs, deserializer.parse_array(doc, origin_obj));
                return std::move(objs);
            }

            template<typename T, CharType CharT = char>
                requires WithMetaInfo<T> && WithDefault<T>
            inline Result<T> from_string
            (
                const std::basic_string_view<CharT> str,
                std::optional<NameTransfer<CharT>> transfer = meta_programming::NameTransfer<NamingSystem::Camelcase, NamingSystem::Underscore, CharT>{}
            ) noexcept
            {
                std::basic_istringstream<CharT> sin{ str };
                OSPF_TRY_GET(doc, read(sin));

                auto deserializer = transfer.has_value() ? Deserializer<T, CharT>{ std::move(transfer).value() } : Deserializer<T, CharT>{};
                OSPF_TRY_GET(obj, deserializer(doc));
                return std::move(obj);
            }

            template<typename T, CharType CharT = char>
                requires WithMetaInfo<T>
            inline Try<T> from_string
            (
                const std::basic_string_view<CharT> str,
                T& obj,
                std::optional<NameTransfer<CharT>> transfer = meta_programming::NameTransfer<NamingSystem::Camelcase, NamingSystem::Underscore, CharT>{}
            ) noexcept
            {
                std::basic_istringstream<CharT> sin{ str };
                OSPF_TRY_GET(doc, read(sin));

                auto deserializer = transfer.has_value() ? Deserializer<T, CharT>{ std::move(transfer).value() } : Deserializer<T, CharT>{};
                OSPF_TRY_EXEC(deserializer(doc, obj));
                return succeed;
            }

            template<typename T, CharType CharT = char>
                requires WithDefault<T>
            inline Result<std::vector<T>> from_string_array
            (
                const std::basic_string_view<CharT> str,
                std::optional<NameTransfer<CharT>> transfer = meta_programming::NameTransfer<NamingSystem::Camelcase, NamingSystem::Underscore, CharT>{}
            ) noexcept
            {
                std::basic_istringstream<CharT> sin{ str };
                OSPF_TRY_GET(doc, read(sin));
                assert(doc.IsArray());

                auto deserializer = transfer.has_value() ? Deserializer<T, CharT>{ std::move(transfer).value() } : Deserializer<T, CharT>{};
                OSPF_TRY_GET(objs, deserializer.parse_array(doc));
                return std::move(objs);
            }

            template<typename T, CharType CharT = char>
                requires std::copy_constructible<T>
            inline Result<std::vector<T>> from_string_array
            (
                const std::basic_string_view<CharT> str,
                std::vector<T>& origin_obj,
                std::optional<NameTransfer<CharT>> transfer = meta_programming::NameTransfer<NamingSystem::Camelcase, NamingSystem::Underscore, CharT>{}
            ) noexcept
            {
                std::basic_istringstream<CharT> sin{ str };
                OSPF_TRY_GET(doc, read(sin));
                assert(doc.IsArray());

                auto deserializer = transfer.has_value() ? Deserializer<T, CharT>{ std::move(transfer).value() } : Deserializer<T, CharT>{};
                OSPF_TRY_GET(objs, deserializer.parse_array(doc, origin_obj));
                return std::move(objs);
            }

            template<typename T, CharType CharT = char>
                requires WithMetaInfo<T> && WithDefault<T>
            inline Result<T> from_json
            (
                const Json<CharT>& json,
                std::optional<NameTransfer<CharT>> transfer = meta_programming::NameTransfer<NamingSystem::Camelcase, NamingSystem::Underscore, CharT>{}
            ) noexcept
            {
                auto deserializer = transfer.has_value() ? Deserializer<T, CharT>{ std::move(transfer).value() } : Deserializer<T, CharT>{};
                OSPF_TRY_GET(obj, deserializer(json));
                return std::move(obj);
            }

            template<typename T, CharType CharT = char>
                requires WithMetaInfo<T>
            inline Try<T> from_json
            (
                const Json<CharT>& json,
                T& obj,
                std::optional<NameTransfer<CharT>> transfer = meta_programming::NameTransfer<NamingSystem::Camelcase, NamingSystem::Underscore, CharT>{}
            ) noexcept
            {
                auto deserializer = transfer.has_value() ? Deserializer<T, CharT>{ std::move(transfer).value() } : Deserializer<T, CharT>{};
                OSPF_TRY_EXEC(deserializer(json, obj));
                return succeed;
            }

            template<typename T, CharType CharT = char>
                requires WithDefault<T>
            inline Result<std::vector<T>> from_json_array
            (
                const Json<CharT>& json,
                std::optional<NameTransfer<CharT>> transfer = meta_programming::NameTransfer<NamingSystem::Camelcase, NamingSystem::Underscore, CharT>{}
            ) noexcept
            {
                auto deserializer = transfer.has_value() ? Deserializer<T, CharT>{ std::move(transfer).value() } : Deserializer<T, CharT>{};
                OSPF_TRY_GET(objs, deserializer.parse_array(json));
                return std::move(objs);
            }

            template<typename T, CharType CharT = char>
                requires std::copy_constructible<T>
            inline Result<std::vector<T>> from_json_array
            (
                const Json<CharT>& json,
                std::vector<T>& origin_obj,
                std::optional<NameTransfer<CharT>> transfer = meta_programming::NameTransfer<NamingSystem::Camelcase, NamingSystem::Underscore, CharT>{}
            ) noexcept
            {
                auto deserializer = transfer.has_value() ? Deserializer<T, CharT>{ std::move(transfer).value() } : Deserializer<T, CharT>{};
                OSPF_TRY_GET(objs, deserializer.parse_array(json, origin_obj));
                return std::move(objs);
            }

            // todo: from bytes
        };
    };
};
