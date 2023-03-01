#pragma once

#include <ospf/functional/result.hpp>
#include <ospf/bytes/auto_link.hpp>
#include <ospf/bytes/bytes.hpp>
#include <cryptopp/base32.h>
#include <cryptopp/base64.h>

namespace ospf
{
    inline namespace bytes
    {
        enum class Encoding : u8
        {
            BASE32,
            BASE64
        };

        template<usize len>
        inline Result<std::string> encode(const Bytes<len>& bytes, const Encoding encoding) noexcept
        {
            using namespace CryptoPP;

            switch (encoding)
            {
            case Encoding::BASE32:
            {
                std::string ret;
                StringSource ss{ bytes.data(), bytes.size(), true, new Base32Encoder{ new StringSink{ ret } } };
                return ret;
            }
            case Encoding::BASE64:
            {
                std::string ret;
                StringSource ss{ bytes.data(), bytes.size(), true, new Base64Encoder{ new StringSink{ ret } } };
                return ret;
            }
            default:
                break;
            }
            return OSPFError{ OSPFErrCode::ApplicationError, "unsupported encoding" };
        }

        inline Result<Bytes<>> decode(const std::string_view str, const Encoding encoding) noexcept
        {
            using namespace CryptoPP;

            switch (encoding)
            {
            case Encoding::BASE32:
            {
                Base32Decoder decoder;
                usize size = decoder.PutMessageEnd(reinterpret_cast<const CryptoPP::byte*>(str.data()), str.size(), -1, true);
                if (!decoder.AnyRetrievable())
                {
                    return OSPFError{ OSPFErrCode::ApplicationError, "failed to decoding by base32" };
                }
                const auto size = static_cast<usize>(decoder.MaxRetrievable());
                Bytes<> ret;
                ret.resize(size, 0_ub);
                decoder.Get((reinterpret_cast<CryptoPP::byte*>(ret.data())), size);
                return ret;
            }
            case Encoding::BASE64:
            {
                Base64Decoder decoder;
                usize size = decoder.PutMessageEnd(reinterpret_cast<const CryptoPP::byte*>(str.data()), str.size(), -1, true);
                if (!decoder.AnyRetrievable())
                {
                    return OSPFError{ OSPFErrCode::ApplicationError, "failed to decoding by base64" };
                }
                const auto size = static_cast<usize>(decoder.MaxRetrievable());
                Bytes<> ret;
                ret.resize(size, 0_ub);
                decoder.Get((reinterpret_cast<CryptoPP::byte*>(ret.data())), size);
                return ret;
            }
            default:
                break;
            }
            return OSPFError{ OSPFErrCode::ApplicationError, "unsupported encoding" };
        }
    };
};
