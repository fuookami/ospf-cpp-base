#pragma once

#include <ospf/serialization/bytes/header.hpp>
#include <ospf/serialization/bytes/to_value.hpp>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iterator>

namespace ospf
{
    inline namespace serialization
    {
        namespace bytes
        {
            // todo: impl multi-thread optimization

            template<typename T>
                requires SerializableToBytes<T>
            class Serializer
            {
            public:
                using ValueType = OriginType<T>;

            public:
                Serializer(void) = default;
                Serializer(const Serializer& ano) = default;
                Serializer(Serializer&& ano) noexcept = default;
                Serializer& operator=(const Serializer& rhs) = default;
                Serializer& operator=(Serializer&& rhs) noexcept = default;
                ~Serializer(void) noexcept = default;

            public:
                template<usize len>
                inline Result<Bytes<>> operator()(const std::span<const ValueType, len> objs) const noexcept
                {
                    Bytes<> ret;
                    const auto header = make_header(objs);
                    static const ToBytesValue<Header> header_serializer{};
                    ret.resize(header_serializer.size(header), header.size());
                    // todo
                    return std::move(ret);
                }

                template<ToValueIter It, usize len>
                inline Try<> operator()(const std::span<const ValueType, len> objs, It& it) const noexcept
                {
                    const auto header = make_header(objs);
                    // todo
                    return succeed;
                }

                template<typename = void>
                    requires WithMetaInfo<ValueType>
                inline Result<Bytes<>> operator()(const ValueType& obj) const noexcept
                {
                    Bytes<> ret;
                    const auto header = make_header(obj);
                    static const ToBytesValue<Header> serializer{};
                    ret.resize(header_serializer.size(header), header.size());
                    // todo
                    return std::move(ret);
                }

                template<ToValueIter It>
                    requires WithMetaInfo<ValueType>
                inline Try<> operator()(const ValueType& obj, It& it) const noexcept
                {
                    const auto header = make_header(obj);
                    // todo
                    return succeed;
                }
            };

            template<typename T, usize len>
            inline Try<> to_file(const std::filesystem::path& path, const std::span<const T, len> objs) noexcept
            {
                if (std::filesystem::is_directory(path))
                {
                    return OSPFError{ OSPFErrCode::NotAFile, std::format("\"{}\" is not a file", path) };
                }

                const auto parent_path = path.parent_path();
                if (!std::filesystem::exists(parent_path))
                {
                    if (!std::filesystem::create_directories(parent_path))
                    {
                        return OSPFError{ OSPFErrCode::DirectoryUnusable, std::format("directory \"{}\" unusable", parent_path) };
                    }
                }

                std::ofstream fout{ path };
                static const Serializer<T> serializer{};
                OSPF_TRY_EXEC(serializer(objs, std::ostreambuf_iterator{ fout }));
                return succeed;
            }

            template<typename T, typename CharT = char>
            inline Try<> to_file(const std::filesystem::path& path, const T& obj) noexcept
            {
                if (std::filesystem::is_directory(path))
                {
                    return OSPFError{ OSPFErrCode::NotAFile, std::format("\"{}\" is not a file", path) };
                }

                const auto parent_path = path.parent_path();
                if (!std::filesystem::exists(parent_path))
                {
                    if (!std::filesystem::create_directories(parent_path))
                    {
                        return OSPFError{ OSPFErrCode::DirectoryUnusable, std::format("directory \"{}\" unusable", parent_path) };
                    }
                }

                std::ofstream fout{ path };
                static const Serializer<T> serializer{};
                OSPF_TRY_EXEC(serializer(obj, std::ostreambuf_iterator{ fout }));
                return succeed;
            }

            template<typename T, usize len>
            inline Result<std::string> to_string(const std::span<const T, len> objs) noexcept
            {
                std::ostringstream sout;
                static const Serializer<T> serializer{};
                OSPF_TRY_EXEC(serializer(objs, std::ostreambuf_iterator{ sout }));
                return sout.str();
            }

            template<typename T>
            inline Result<std::string> to_string(const T& obj) noexcept
            {
                std::ostringstream sout;
                static const Serializer<T> serializer{};
                OSPF_TRY_EXEC(serializer(obj, std::ostreambuf_iterator{ sout }));
                return sout.str();
            }

            template<typename T, usize len, typename CharT = char>
            inline Result<Bytes<>> to_bytes(const std::span<const T, len> objs) noexcept
            {
                static const Serializer<T> serializer{};
                return serializer(objs);
            }

            template<typename T, typename CharT = char>
            inline Result<Bytes<>> to_bytes(const T& obj) noexcept
            {
                static const Serializer<T> serializer{};
                return serializer(obj);
            }
        };
    };
};
