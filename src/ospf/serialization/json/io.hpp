#pragma once

#include <ospf/functional/result.hpp>
#include <ospf/string/format.hpp>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>
#include <rapidjson/error/en.h>
#include <istream>
#include <ostream>

namespace ospf
{
    inline namespace serialization
    {
        namespace json
        {
            template<CharType CharT>
            inline Try<> write(std::basic_ostream<CharT>& os, const Document<CharT>& doc) noexcept
            {
                rapidjson::BasicOStreamWrapper<decltype(os)> osw{ os };
                rapidjson::Writer<decltype(osw)> writer{ osw };

                if (!doc.Accept(writer))
                {
                    throw ospf::OSPFException{ ospf::OSPFErrCode::SerializationFail };
                }
                return succeed;
            }

            template<CharType CharT>
            inline Result<Document<CharT>> read(std::basic_istream<CharT>& is) noexcept
            {
                Document<CharT> doc;
                rapidjson::BasicIStreamWrapper<decltype(is)> isw{is};
                rapidjson::ParseResult ok = doc.ParseStream(isw);
                if (!ok)
                {
                    static const auto fmt = boost::locale::conv::to_utf<CharT>("{} at {}", std::locale{});
                    return OSPFError{ OSPFErrCode::DeserializationFail, std::vformat(fmt, make_format_args<CharT>(rapidjson::GetParseError_En(ok.Code()), ok.Offset())) };
                }
                else
                {
                    return std::move(doc);
                }
            }
        };
    };
};
