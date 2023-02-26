#pragma once

#include <ospf/serialization/bytes/from_value.hpp>
#include <ospf/serialization/bytes/to_value.hpp>
#include <ospf/string/hasher.hpp>

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

            class SubHeader
            {
                friend class Header;

            private:
                SubHeader(const HeaderTag tag, StringHashMap<std::string_view, Shared<SubHeader>> fields)
                    : _tag(tag), _fields(std::move(fields)) {}

            public:
                SubHeader(const SubHeader& ano) = default;
                SubHeader(SubHeader&& ano) noexcept = default;
                SubHeader& operator=(const SubHeader& rhs) = default;
                SubHeader& operator=(SubHeader&& rhs) noexcept = default;
                ~SubHeader(void) noexcept = default;
                
            public:
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
                HeaderTag _tag;
                StringHashMap<std::string_view, Shared<SubHeader>> _fields;
            };

            class Header
            {
            public:
                static constexpr const usize local_segement_size = 4_uz;

            public:
                template<WithMetaInfo T>
                inline static Header by(const T& obj) noexcept
                {
                    // todo
                    const auto root_tag = HeaderTag::Object;
                    const usize size = 0_uz;
                    std::array<u64, 4_uz> segement{ 0_uz };
                    auto [sub_headers, fields] = analysis<T>();
                    return Header{ root_tag, size, std::move(segement), std::move(sub_headers), std::move(fields) };
                }

                template<typename T, usize len>
                inline static Header by(const std::span<T, len> objs) noexcept
                {
                    // todo
                    const usize root_tag = HeaderTag::Array;
                    const usize size = 0_uz;
                    std::array<u64, 4_uz> segement{ 0_uz };
                    auto [sub_headers, fields] = analysis<T>();
                    return Header{ root_tag, size, std::move(segement), std::move(sub_headers), std::move(fields) };
                }

            public:
                Header(const HeaderTag tag, const u8 address_length, const Endian endian, const u64 size, std::vector<usize> field_segement, std::vector<u64> segement, std::vector<Shared<SubHeader>> sub_headers, StringHashMap<std::string_view, Shared<SubHeader>> fields)
                    : _root_tag(tag), _address_length(address_length), _endian(endian), _size(size), _field_segement(std::move(field_segement)), _segement(std::move(segement)), _fields(std::move(fields)) 
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
                    auto [_, fields] = analysis<T>();
                    return fit(fields);
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
                OSPF_BASE_API Try<> fit(const StringHashMap<std::string_view, Shared<SubHeader>> fields) const noexcept;

                template<typename T>
                inline static std::pair<std::vector<Shared<SubHeader>>, StringHashMap<std::string_view, Shared<SubHeader>>> analysis(void) noexcept
                {
                    if constexpr (WithMetaInfo<T>)
                    {
                        // todo
                    }
                    else
                    {
                        return std::make_pair({}, {});
                    }
                }

            private:
                HeaderTag _root_tag;
                u8 _address_length;
                Endian _endian;
                u64 _size;
                std::vector<usize> _field_segement;
                std::vector<u64> _segement;
                std::vector<Shared<SubHeader>> _sub_headers;
                StringHashMap<std::string_view, Shared<SubHeader>> _fields;
            };

            template<typename T>
            inline Header make_header(const T& obj) noexcept
            {
                return Header::by(obj);
            }

            template<typename T, usize len>
            inline Header make_header(const std::span<T, len> objs) noexcept
            {
                return Header::by(objs);
            }

            template<>
            struct ToBytesValue<SubHeader>
            {
                inline const usize size(const SubHeader& header) const noexcept
                {
                    // todo
                    return 0_uz;
                }

                template<ToValueIter It>
                inline Try<> operator()(const SubHeader& header, It& it, const Endian endian) const noexcept
                {
                    // todo
                    return succeed;
                }
            };

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
                    // todo
                    return succeed;
                }
            };

            template<>
            struct FromBytesValue<SubHeader>
            {
                template<FromValueIter It>
                inline Result<SubHeader> operator()(It& it, const usize address_length, const Endian endian) const noexcept
                {
                    // todo
                }
            };

            template<>
            struct FromBytesValue<Header>
            {
                template<FromValueIter It>
                inline Result<Header> operator()(It& it, const usize address_length, const Endian endian) const noexcept
                {
                    // todo
                }
            };
        };
    };
};
