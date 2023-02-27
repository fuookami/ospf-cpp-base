#pragma once

#include <ospf/serialization/bytes/from_value.hpp>
#include <ospf/serialization/bytes/to_value.hpp>
#include <ospf/string/hasher.hpp>
#include <bit>

namespace ospf
{
    inline namespace serialization
    {
        namespace bytes
        {
            enum class HeaderTag : u8
            {
                Value,
                Object,
                Array,
            };

            class Header;
            class SubHeader;
            using Fields = StringHashMap<std::string_view, Shared<SubHeader>>;

            OSPF_BASE_API const bool same(const Fields& lhs, const Fields& rhs, const bool recursive = false) noexcept;

            class SubHeader
            {
                friend class Header;

            public:
                SubHeader(const u64 id)
                    : _id(id), _tag(HeaderTag::Value) {}

                SubHeader(const u64 id, const HeaderTag tag, StringHashMap<std::string_view, Shared<SubHeader>> fields)
                    : _id(id), _tag(tag), _fields(std::move(fields)) {}

            public:
                SubHeader(const SubHeader& ano) = default;
                SubHeader(SubHeader&& ano) noexcept = default;
                SubHeader& operator=(const SubHeader& rhs) = default;
                SubHeader& operator=(SubHeader&& rhs) noexcept = default;
                ~SubHeader(void) noexcept = default;
                
            public:
                inline const u64 id(void) const noexcept
                {
                    return _id;
                }

                inline const HeaderTag tag(void) const noexcept
                {
                    return _tag;
                }

                inline const StringHashMap<std::string_view, Shared<SubHeader>>& fields(void) const noexcept
                {
                    return _fields;
                }

            public:
                OSPF_BASE_API const bool operator==(const SubHeader& rhs) const noexcept;
                OSPF_BASE_API const bool operator!=(const SubHeader& rhs) const noexcept;

            private:
                u64 _id;
                HeaderTag _tag;
                Fields _fields;
            };

            class Header
            {
            public:
                static constexpr const usize local_segement_size = 4_uz;

            public:
                template<WithMetaInfo T>
                inline static Header by(const T& obj, const Endian endian = local_endian) noexcept
                {
                    const auto root_tag = HeaderTag::Object;

                    static const ToBytesValue<OriginType<T>> serializer{};
                    const usize size = serializer.size(obj);

                    std::vector<u64> field_segement{ local_segement_size, 0_u64 };
                    std::vector<u64> segement{ local_segement_size, 0_u64 };
                    {
                        static const meta_info::MetaInfo<OriginType<T>> info{};
                        usize i{ 0_uz };
                        usize j{ 1_uz };
                        usize current_size{ 0_uz };
                        info.for_each(obj, [size, &field_segement, &segement, &i, &j, &current_size](const auto& obj, const auto& field)
                            {
                                using FieldValueType = OriginType<decltype(field.value(obj))>;
                                if (j == (local_segement_size - 1_uz))
                                {
                                    return;
                                }
                                
                                static const ToBytesValue<OriginType<T>> serializer{};
                                current_size += serializer.size(field.value(obj));
                                if (current_size >= (size * j / local_segement_size))
                                {
                                    field_segement[j] = static_cast<u64>(i + 1_uz);
                                    segement[j] = static_cast<u64>(current_size);
                                    ++j;
                                }
                                ++i;
                            });
                    }

                    auto [sub_headers, fields] = analysis<OriginType<T>>();
                    return Header{ root_tag, ospf::address_length, endian, size, std::move(field_segement), std::move(segement), std::move(sub_headers), std::move(fields) };
                }

                template<typename T, usize len>
                inline static Header by(const std::span<const T, len> objs, const Endian endian = local_endian) noexcept
                {
                    const usize root_tag = HeaderTag::Array;
                    
                    static const ToBytesValue<std::span<ConstType<T>, len>> serializer{};
                    const usize size = serializer.size(objs);

                    std::vector<u64> segement{ local_segement_size, 0_u64 };
                    for (usize i{ 0_uz }, j{ 1_uz }, current_size{ 0_uz }; i != objs.size(); ++i)
                    {
                        static const ToBytesValue<OriginType<T>> serializer{};
                        current_size += serializer.size();
                        if (i >= (objs.size() * j / local_segement_size))
                        {
                            segement[j] = static_cast<u64>(current_size);
                            ++j;
                        }
                    }

                    auto [sub_headers, fields] = analysis<OriginType<T>>();
                    return Header{ root_tag, ospf::address_length, endian, size, { local_segement_size, 0_u64 }, std::move(segement), std::move(sub_headers), std::move(fields) };
                }

            public:
                Header(
                    const HeaderTag tag, 
                    const u8 address_length,
                    const Endian endian, 
                    const u64 size, 
                    std::vector<u64> field_segement, 
                    std::vector<u64> segement, 
                    std::vector<Shared<SubHeader>> sub_headers,
                    StringHashMap<std::string_view, Shared<SubHeader>> fields
                ) : 
                    _root_tag(tag), 
                    _address_length(address_length), 
                    _endian(endian), _size(size), 
                    _field_segement(std::move(field_segement)), 
                    _segement(std::move(segement)), 
                    _fields(std::move(fields)) 
                {
                    assert(_field_segement.size() == _segement.size());
                }

            public:
                Header(const Header& ano) = default;
                Header(Header&& ano) noexcept = default;
                Header& operator=(const Header& rhs) = default;
                Header& operator=(Header&& rhs) noexcept = default;
                ~Header(void) noexcept = default;

            public:
                inline const HeaderTag root_tag(void) const noexcept
                {
                    return _root_tag;
                }

                inline const u8 address_length(void) const noexcept
                {
                    return _address_length;
                }

                inline const Endian endian(void) const noexcept
                {
                    return _endian;
                }

                inline const u64 size(void) const noexcept
                {
                    return _size;
                }

                inline const usize segement_size(void) const noexcept
                {
                    return _segement.size();
                }

                inline const std::span<const u64> field_segement(void) const noexcept
                {
                    return _field_segement;
                }

                inline const std::span<const u64> segement(void) const noexcept
                {
                    return _segement;
                }

                inline const std::span<const Shared<SubHeader>> sub_headers(void) const noexcept
                {
                    return _sub_headers;
                }

                inline const StringHashMap<std::string_view, Shared<SubHeader>>& fields(void) const noexcept
                {
                    return _fields;
                }

            public:
                template<typename T>
                inline Try<> fit(void) const noexcept
                {
                    auto [_, fields] = analysis<OriginType<T>>();
                    if (same(fields, _fields, true))
                    {
                        return succeed;
                    }
                    else
                    {
                        return OSPFError{ OSPFErrCode::DeserializationFail, std::format("not fit bytes for \"{}\"", TypeInfo<T>::name()) };
                    }
                }

                inline const usize index_of(const Shared<SubHeader>& sub_header) const noexcept
                {
                    const auto it = std::find(_sub_headers.cbegin(), _sub_headers.cend(), sub_header);
                    if (it == _sub_headers.cend())
                    {
                        return npos;
                    }
                    else
                    {
                        return static_cast<usize>(it - _sub_headers.cbegin());
                    }
                }

            private:
                template<typename T>
                inline static std::pair<std::vector<Shared<SubHeader>>, StringHashMap<std::string_view, Shared<SubHeader>>> analysis(void) noexcept
                {
                    if constexpr (WithMetaInfo<T>)
                    {
                        std::vector<Shared<SubHeader>> sub_headers{};
                        auto fields = analysis_fields<T>(sub_headers);
                        return std::make_pair(std::move(sub_headers), std::move(fields));
                    }
                    else
                    {
                        return std::make_pair({}, {});
                    }
                }

                template<typename T>
                inline static Shared<SubHeader> analysis(std::vector<Shared<SubHeader>>& sub_headers) noexcept
                {
                    const auto id = static_cast<u64>(TypeInfo<T>::code());
                    if constexpr (WithMetaInfo<T>)
                    {
                        auto it = std::find_if(sub_headers.cbegin(), sub_headers.cend(), [id](const Shared<SubHeader>& header)
                            {
                                return header->id() == id && header->tag() == HeaderTag::Object;
                            });
                        if (it == sub_headers.cend())
                        {
                            it = sub_headers.insert(sub_headers.end(), make_shared<SubHeader>(id, HeaderTag::Object, analysis_fields<T>(sub_headers)));
                        }
                        return *it;
                    }
                    else if constexpr (std::ranges::range<T>)
                    {
                        auto it = std::find_if(sub_headers.cbegin(), sub_headers.cend(), [id](const Shared<SubHeader>& header)
                            {
                                return header->id() == id && header->tag() == HeaderTag::Array;
                            });
                        if (it == sub_headers.cend())
                        {
                            it = sub_headers.insert(sub_headers.end(), make_shared<SubHeader>(id, HeaderTag::Array, analysis_fields<T>(sub_headers)));
                        }
                        return *it;
                    }
                    else
                    {
                        auto it = std::find_if(sub_headers.cbegin(), sub_headers.cend(), [id](const Shared<SubHeader>& header)
                            {
                                return header->id() == id && header->tag() == HeaderTag::Value;
                            });
                        if (it == sub_headers.cend())
                        {
                            it = sub_headers.insert(sub_headers.end(), make_shared<SubHeader>(id));
                        }
                        return *it;
                    }
                }

                template<typename T>
                inline static StringHashMap<std::string_view, Shared<SubHeader>> analysis_fields(std::vector<Shared<SubHeader>>& sub_headers) noexcept
                {
                    const auto id = static_cast<u64>(TypeInfo<T>::code());
                    const auto it = std::find_if(sub_headers.cbegin(), sub_headers.cend(), [id](const Shared<SubHeader>& header)
                        {
                            return header->id() == id;
                        });
                    if (it != sub_headers.cend())
                    {
                        return it->fields();
                    }
                    else
                    {
                        static const meta_info::MetaInfo<OriginType<T>> info{};
                        StringHashMap<std::string_view, Shared<SubHeader>> ret;
                        info.for_each([&ret, &sub_headers](const auto& field)
                            {
                                using FieldValueType = OriginType<decltype(field.value(std::declval<OriginType<T>>()))>;
                                ret.insert(std::make_pair(field.key(), analysis<FieldValueType>(sub_headers)));
                            });
                        return ret;
                    }
                }

            private:
                HeaderTag _root_tag;
                Endian _endian;
                u8 _address_length;
                u64 _size;
                std::vector<u64> _field_segement;
                std::vector<u64> _segement;
                // the dependence of a sub header is higher in the order than it
                std::vector<Shared<SubHeader>> _sub_headers;
                Fields _fields;
            };

            template<typename T>
            inline Header make_header(const T& obj, const Endian endian = local_endian) noexcept
            {
                return Header::by(obj, endian);
            }

            template<typename T, usize len>
            inline Header make_header(const std::span<const T, len> objs, const Endian endian = local_endian) noexcept
            {
                return Header::by(objs, endian);
            }

            template<>
            struct ToBytesValue<Header>
            {
                inline const usize size(const Header& header) const noexcept
                {
                    // todo
                    return 0_uz;
                }

                template<ToValueIter It>
                inline Try<> operator()(const Header& header, It& it, const Endian endian) const noexcept
                {
                    {
                        u8 flag{ 0_u8 };
                        // 2 bits
                        flag |= static_cast<u8>(header.root_tag());
                        flag <<= 1_u8;
                        // 1 bits
                        flag |= static_cast<u8>(header.endian());
                        flag <<= 5_u8;
                        flag |= static_cast<u8>(std::bit_width(header.address_length())) - 1_u8;

                        static const ToBytesValue<u8> serializer{};
                        serializer(flag, it, header.endian());
                    }
                    {
                        static const ToBytesValue<u64> serializer{};
                        serializer(header.size(), it, header.endian());
                    }
                    {
                        static const ToBytesValue<std::vector<u64>> serializer{};
                        serializer(header.field_segement(), it, header.endian());
                        serializer(header.segement(), it, header.endian());
                    }
                    to_bytes<u64>(static_cast<u64>(header.sub_headers().size()), it, header.endian());
                    for (const auto& sub_header : header.sub_headers())
                    {
                        OSPF_TRY_EXEC(serialize_sub_header(*sub_header, header, it));
                    }
                    OSPF_TRY_EXEC(serialize_fields(fields, header, it));
                    return succeed;
                }

            private:
                template<ToValueIter It>
                inline Try<> serialize_sub_header(const SubHeader& sub_header, const Header& header, It& it) const noexcept
                {
                    // todo
                    return succeed;
                }

                template<ToValueIter It>
                inline Try<> serialize_fields(const Fields& fields, const Header& header, It& it) const noexcept
                {
                    // todo
                    return succeed;
                }
            };

            template<>
            struct FromBytesValue<Header>
            {
                template<FromValueIter It>
                inline Result<Header> operator()(It& it, const usize address_length, const Endian endian) const noexcept
                {
                    static const FromBytesValue<u8> flag_deserializer{};
                    OSPF_TRY_GET(flag, flag_deserializer(it, address_length, endian));
                    const auto address_length = 1_u8 << (flag & 0b11111_u8);
                    flag >>= 5_u8;
                    const auto endian = static_cast<Endian>(flag & 0b1_u8);
                    flag >>= 1_u8;
                    const auto tag = static_cast<HeaderTag>(flag & 0b11_u8);
                    
                    static const FromBytesValue<u64> size_deserializer{};
                    OSPF_TRY_GET(size, size_deserializer(it, address_length, endian));

                    static const FromBytesValue<std::vector<u64>> segement_deserializer{};
                    OSPF_TRY_GET(field_segement, segement_deserializer(it, address_length, endian));
                    OSPF_TRY_GET(segement, segement_deserializer(it, address_length, endian));

                    std::vector<SubHeader> sub_headers;
                    Fields fields;
                    // todo
                    return Header{ tag, address_length, endian, size, std::move(field_segement), std::move(segement), std::move(sub_headers), std::move(fields) };
                }
            };
        };
    };
};
