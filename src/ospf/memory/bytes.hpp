#pragma once

#include <ospf/basic_definition.hpp>
#include <ospf/literal_constant.hpp>
#include <ospf/system_info.hpp>
#include <ospf/type_family.hpp>

namespace ospf
{
    inline namespace memory
    {
        template<usize len = npos>
        using Bytes = std::conditional_t<
            len == npos,
            std::vector<ubyte>,
            std::array<ubyte, len>
        >;

        template<typename T>
            requires std::copyable<T> && std::is_trivially_copyable_v<T>
        inline Bytes<sizeof(T)> to_bytes(ArgCLRefType<T> value, const Endian endian = local_endian) noexcept
        {
            Bytes<sizeof(T)> bytes{ 0_ub };
            const auto ptr = reinterpret_cast<ubyte*>(&value);
            if (endian == local_endian)
            {
                std::copy(ptr, ptr + sizeof(T) / address_length, bytes.begin());
            }
            else
            {
                std::copy(ptr, ptr + sizeof(T) / address_length, bytes.rbegin());
            }
            return bytes;
        }

        template<typename T, typename It>
            requires std::copyable<T> && std::is_trivially_copyable_v<T> && std::output_iterator<It, ubyte>
        inline void to_bytes(ArgCLRefType<T> value, It& it, const Endian endian = local_endian) noexcept
        {
            if (endian == local_endian)
            {
                const auto ptr = reinterpret_cast<ubyte*>(&value);
                std::copy(ptr, ptr + sizeof(T) / address_length, it);
            }
            else
            {
                const auto bytes = sizeof(T) / address_length;
                const auto ptr = reinterpret_cast<ubyte*>(&value) + bytes - 1_iz;
                for (usize i{ 0_uz }; i != bytes; ++i)
                {
                    *it = *ptr;
                    ++it;
                    --ptr;
                }
            }
            return bytes;
        }

        template<typename T>
            requires std::default_initializable<T> && std::copyable<T> && std::is_trivially_copyable_v<T>
        inline T from_bytes(const Bytes<sizeof(T)>& bytes, const Endian endian = local_endian) noexcept
        {
            T value{};
            from_bytes(bytes, value, endian);
            return value;
        }

        template<typename T>
            requires std::copyable<T> && std::is_trivially_copyable_v<T>
        inline void from_bytes(const Bytes<sizeof(T)>& bytes, T& value, const Endian endian = local_endian) noexcept
        {
            const auto ptr = reinterpret_cast<ubyte*>(&value);
            if (endian == local_endian)
            {
                std::copy(bytes.cbegin(), bytes.cend(), ptr);
            }
            else
            {
                std::copy(bytes.crbegin(), bytes.crend(), ptr);
            }
        }

        template<typename T, typename It>
            requires std::default_initializable<T> && std::copyable<T> && std::is_trivially_copyable_v<T> && std::input_iterator<It>
                && requires (const It& it)
                {
                    { *it } -> DecaySameAs<ubyte>;
                }
        inline T from_bytes(It& it, const Endian endian = local_endian) noexcept
        {
            T value{};
            from_bytes(it, value, endian);
            return value;
        }

        template<typename T, typename It>
            requires std::copyable<T> && std::is_trivially_copyable_v<T> && std::input_iterator<It>
                && requires (const It& it)
                {
                    { *it } -> DecaySameAs<ubyte>;
                }
        inline void from_bytes(It& it, T& value, const Endian endian = local_endian) noexcept
        {
            const auto bytes = sizeof(T) / address_length;
            if (endian == local_endian)
            {
                const auto ptr = reinterpret_cast<ubyte*>(&value);
                for (usize i{ 0_uz }; i != bytes; ++i)
                {
                    *ptr = *it;
                    ++it;
                    ++ptr;
                }
            }
            else
            {
                const auto ptr = reinterpret_cast<ubyte*>(&value) + bytes - 1_iz;
                for (usize i{ 0_uz }; i != bytes; ++i)
                {
                    *ptr = *it;
                    ++it;
                    --ptr;
                }
            }
        }
    };
};
