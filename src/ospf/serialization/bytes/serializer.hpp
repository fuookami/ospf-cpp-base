#pragma once

#include <ospf/config.hpp>
#include <ospf/serialization/bytes/header.hpp>
#include <ospf/serialization/bytes/to_value.hpp>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iterator>

#ifdef OSPF_MULTI_THREAD
#include <future>
#endif

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
                Serializer(const Endian endian = local_endian)
                    : _endian(endian) {}
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
                    const auto header_size = header_serializer.size(header);
                    ret.resize(header_size + header.size(), 0_ub);
                    header_serializer(header, ret.begin(), _endian);
                    to_bytes<usize>(objs.size(), ret.begin() + header_size, _endian);
#ifdef OSPF_MULTI_THREAD
                    std::vector<std::future<Try<>>> futures;
                    for (usize i{ 0_uz }; i != Header::segement_size; ++i)
                    {
                        const auto bg = header.field_segement()[i];
                        const auto ed = (i != Header::segement_size - 1_uz) ? header.field_segement()[i + 1_uz] : objs.size();
                        const auto offset = header.size() + address_length + header.segement()[i];
                        futures.push_back(std::async(std::launch::async, [this, bg, ed, offset, &ret, &objs](void) -> Try<>
                            {
                                for (usize i{ bg }, this_offset{ offset }; i != ed; ++i)
                                {
                                    static const ToBytesValue<ValueType> serializer{};
                                    serializer(objs[i], ret.begin() + this_offset, this->_endian);
                                    this_offset += serializer.size(objs[i]);
                                }
                            }));
                    }
                    for (auto& future : futures)
                    {
                        OSPF_TRY_EXEC(future.get());
                    }
#else
                    static const ToBytesValue<std::span<const ValueType, len>> serializer{};
                    serializer(objs, ret.begin() + header_size, _endian);
#endif
                    return std::move(ret);
                }

                template<ToValueIter It, usize len>
                inline Try<> operator()(const std::span<const ValueType, len> objs, It& it) const noexcept
                {
                    const auto header = make_header(objs);
                    static const ToBytesValue<Header> header_serializer{};
                    header_serializer(header, it, _endian);
                    static const ToBytesValue<std::span<const ValueType, len>> serializer{};
                    serializer(objs, it, _endian);
                    return succeed;
                }

                template<typename = void>
                    requires WithMetaInfo<ValueType>
                inline Result<Bytes<>> operator()(const ValueType& obj) const noexcept
                {
                    Bytes<> ret;
                    const auto header = make_header(obj);
                    static const ToBytesValue<Header> header_serializer{};
                    const auto header_size = header_serializer.size(header);
                    ret.resize(header_size + header.size(), 0_ub);
#ifdef OSPF_MULTI_THREAD
                    std::vector<std::future<Try<>>> futures;
                    for (usize i{ 0_uz }; i != Header::segement_size; ++i)
                    {
                        const auto bg = header.field_segement()[i];
                        const auto ed = (i != Header::segement_size - 1_uz) ? header.field_segement()[i + 1_uz] : npos;
                        const auto offset = header.size() + address_length + header.segement()[i];
                        futures.push_back(std::async(std::launch::async, [this, bg, ed, offset, &ret](void) -> Try<>
                            {
                                static const meta_info::MetaInfo<ValueType> info{};
                                std::optional<OSPFError> err;
                                usize i{ bg };
                                usize this_offset{ offset };
                                info.for_each(obj, [this, &i, ed, &this_offset, &ret, &err](const auto& obj, const auto& field)
                                    {
                                        using FieldValueType = OriginType<decltype(field.value(obj))>;
                                        static_assert(SerializableToBytes<FieldValueType>);

                                        if (err.has_value() || i == ed)
                                        {
                                            return;
                                        }

                                        static const ToBytesValue<FieldValueType> serializer{};
                                        const auto& value = field.value(obj);
                                        const auto ret = serializer(value, ret.begin() + this_offset, this->_endian);
                                        if (ret.is_failed())
                                        {
                                            err = std::move(ret).err();
                                        }
                                        else
                                        {
                                            ++i;
                                            this_offset += serializer.size(value);
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
                            }));
                    }
                    for (auto& future : futures)
                    {
                        OSPF_TRY_EXEC(future.get());
                    }
#else
                    static const ToBytesValue<std::span<const ValueType, len>> serializer{};
                    serializer(objs, ret.begin() + header_size, _endian);
#endif
                    return std::move(ret);
                }

                template<ToValueIter It>
                    requires WithMetaInfo<ValueType>
                inline Try<> operator()(const ValueType& obj, It& it) const noexcept
                {
                    const auto header = make_header(obj);
                    static const ToBytesValue<Header> header_serializer{};
                    header_serializer(header, it, _endian);
                    static const ToBytesValue<std::span<const ValueType, len>> serializer{};
                    serializer(obj, it, _endian);
                    return succeed;
                }

            private:
                Endian _endian;
            };

            template<typename T, usize len>
            inline Try<> to_file(const std::filesystem::path& path, const std::span<const T, len> objs, const Endian endian = local_endian) noexcept
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
                static const Serializer<T> serializer{ endian };
                OSPF_TRY_EXEC(serializer(objs, std::ostreambuf_iterator{ fout }));
                return succeed;
            }

            template<typename T, typename CharT = char>
            inline Try<> to_file(const std::filesystem::path& path, const T& obj, const Endian endian = local_endian) noexcept
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
                static const Serializer<T> serializer{ endian };
                OSPF_TRY_EXEC(serializer(obj, std::ostreambuf_iterator{ fout }));
                return succeed;
            }

            template<typename T, usize len>
            inline Result<std::string> to_string(const std::span<const T, len> objs, const Endian endian = local_endian) noexcept
            {
                std::ostringstream sout;
                static const Serializer<T> serializer{ endian };
                OSPF_TRY_EXEC(serializer(objs, std::ostreambuf_iterator{ sout }));
                return sout.str();
            }

            template<typename T>
            inline Result<std::string> to_string(const T& obj, const Endian endian = local_endian) noexcept
            {
                std::ostringstream sout;
                static const Serializer<T> serializer{ endian };
                OSPF_TRY_EXEC(serializer(obj, std::ostreambuf_iterator{ sout }));
                return sout.str();
            }

            template<typename T, usize len, typename CharT = char>
            inline Result<Bytes<>> to_bytes(const std::span<const T, len> objs, const Endian endian = local_endian) noexcept
            {
                static const Serializer<T> serializer{ endian };
                return serializer(objs);
            }

            template<typename T, typename CharT = char>
            inline Result<Bytes<>> to_bytes(const T& obj, const Endian endian = local_endian) noexcept
            {
                static const Serializer<T> serializer{ endian };
                return serializer(obj);
            }
        };
    };
};
