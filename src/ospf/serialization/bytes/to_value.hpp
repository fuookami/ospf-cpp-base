#pragma once

#include <ospf/functional/result.hpp>
#include <ospf/memory/bytes.hpp>
#include <ospf/meta_programming/meta_info.hpp>
#include <ospf/serialization/bytes/concepts.hpp>
#include <ospf/ospf_base_api.hpp>

namespace ospf
{
    inline namespace serialization
    {
        namespace bytes
        {
            template<typename T>
            struct ToBytesValue;

            template<typename T>
            concept SerializableToBytes = requires (const ToBytesValue<T> serializer)
            {
                { serializer.size(std::declval<T>()) } -> DecaySameAs<usize>;
                { serializer(std::declval<T>(), std::declval<std::vector<ubyte>::iterator>(), std::declval<Endian>()) } -> DecaySameAs<Try<>>;
            };

            template<EnumType T>
            struct ToBytesValue<T>
            {
                using ValueType = magic_enum::underlying_type_t<T>;

                inline const usize size(const T value) const noexcept
                {
                    return sizeof(ValueType) / address_length;
                }

                template<ToValueIter It>
                inline Try<> operator()(const T value, It& it, const Endian endian) const noexcept
                {
                    static constexpr const ToBytesValue<ValueType> serializer{};
                    return serializer(static_cast<ValueType>(value, it, endian));
                }
            };

            template<WithMetaInfo T>
            struct ToBytesValue<T>
            {
                inline const usize size(const T& value) const noexcept
                {
                    static constexpr const meta_info::MetaInfo<T> info{};
                    usize ret{ 0_uz };
                    info.for_each(value, [&ret](const auto& obj, const auto& field) 
                        {
                            using FieldValueType = OriginType<decltype(field.value(obj))>;
                            static_assert(SerializableToBytes<FieldValueType>);
                            const ToBytesValue<FieldValueType> serializer{};
                            ret += serializer.size(field.value(obj));
                        });
                    return ret;
                }

                template<ToValueIter It>
                inline Try<> operator()(const T& value, It& it, const Endian endian) const noexcept
                {
                    static constexpr const meta_info::MetaInfo<T> info{};
                    info.for_each(value, [&it](const auto& obj, const auto& field)
                        {
                            using FieldValueType = OriginType<decltype(field.value(obj))>;
                            static_assert(SerializableToBytes<FieldValueType>);
                            const ToBytesValue<FieldValueType> serializer{};
                            serializer(field.value(obj), it, endian);
                        });
                    return succeed;
                }
            };

            // todo: big int, decimal and chrono
            // todo: optional, ptr, variant, either, val/ref, range, span

            template<>
            struct ToBytesValue<bool>
            {
                inline const usize size(const bool value) const noexcept
                {
                    return 1_uz;
                }

                template<ToValueIter It>
                inline Try<> operator()(const bool value, It& it, const Endian endian) const noexcept
                {
                    *it = value ? 1_ub : 0_ub;
                    ++it;
                    return succeed;
                }
            };

            template<>
            struct ToBytesValue<u8>
            {
                inline const usize size(const u8 value) const noexcept
                {
                    return 1_uz;
                }

                template<ToValueIter It>
                inline Try<> operator()(const u8 value, It& it, const Endian endian) const noexcept
                {
                    *it = static_cast<ubyte>(value);
                    ++it;
                    return succeed;
                }
            };

            template<>
            struct ToBytesValue<i8>
            {
                inline const usize size(const i8 value) const noexcept
                {
                    return 1_uz;
                }

                template<ToValueIter It>
                inline Try<> operator()(const i8 value, It& it, const Endian endian) const noexcept
                {
                    *it = static_cast<ubyte>(value);
                    ++it;
                    return succeed;
                }
            };

            template<>
            struct ToBytesValue<u16>
            {
                inline const usize size(const u16 value) const noexcept
                {
                    return 2_uz;
                }

                template<ToValueIter It>
                inline Try<> operator()(const u16 value, It& it, const Endian endian) const noexcept
                {
                    to_bytes<u16>(value, it, endian);
                    return succeed;
                };
            };

            template<>
            struct ToBytesValue<i16>
            {
                inline const usize size(const i16 value) const noexcept
                {
                    return 2_uz;
                }

                template<ToValueIter It>
                inline Try<> operator()(const i16 value, It& it, const Endian endian) const noexcept
                {
                    to_bytes<i16>(value, it, endian);
                    return succeed;
                }
            };

            template<>
            struct ToBytesValue<u32>
            {
                inline const usize size(const u32 value) const noexcept
                {
                    return 4_uz;
                }

                template<ToValueIter It>
                inline Try<> operator()(const u32 value, It& it, const Endian endian) const noexcept
                {
                    to_bytes<u32>(value, it, endian);
                    return succeed;
                }
            };

            template<>
            struct ToBytesValue<i32>
            {
                inline const usize size(const i32 value) const noexcept
                {
                    return 4_uz;
                }

                template<ToValueIter It>
                inline Try<> operator()(const i32 value, It& it, const Endian endian) const noexcept
                {
                    to_bytes<i32>(value, it, endian);
                    return succeed;
                }
            };

            template<>
            struct ToBytesValue<u64>
            {
                inline const usize size(const u64 value) const noexcept
                {
                    return 8_uz;
                }

                template<ToValueIter It>
                inline Try<> operator()(const u64 value, It& it, const Endian endian) const noexcept
                {
                    to_bytes<u64>(value, it, endian);
                    return succeed;
                }
            };

            template<>
            struct ToBytesValue<i64>
            {
                inline const usize size(const i64 value) const noexcept
                {
                    return 8_uz;
                }

                template<ToValueIter It>
                inline Try<> operator()(const i64 value, It& it, const Endian endian) const noexcept
                {
                    to_bytes<i64>(value, it, endian);
                    return succeed;
                }
            };

            template<>
            struct ToBytesValue<std::string>
            {
                inline const usize size(const std::string value) const noexcept
                {
                    return 8_uz + value.size();
                }

                template<ToValueIter It>
                inline Try<> operator()(const std::string& value, It& it, const Endian endian) const noexcept
                {
                    to_bytes<usize>(value.size(), it, endian);
                    std::transform(value.cbegin(), value.cend(), it, [](const char ch) { return static_cast<ubyte>(ch); });
                    return succeed;
                }
            };

            template<>
            struct ToBytesValue<std::string_view>
            {
                inline const usize size(const std::string_view value) const noexcept
                {
                    return 8_uz + value.size();
                }

                template<ToValueIter It>
                inline Try<> operator()(const std::string_view value, It& it, const Endian endian) const noexcept
                {
                    to_bytes<usize>(value.size(), it, endian);
                    std::transform(value.cbegin(), value.cend(), it, [](const char ch) { return static_cast<ubyte>(ch); });
                    return succeed;
                }
            };
        };
    };
};
