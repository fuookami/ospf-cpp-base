#pragma once

#include <ospf/functional/result.hpp>
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
            template<typename CharT>
            inline Try<> write(std::basic_ostream<CharT>& os, const rapidjson::Document& doc) noexcept
            {
                rapidjson::BasicOStreamWrapper osw{ sout };
                rapidjson::Writer writer{ osw };

                if (!doc.Accept(writer))
                {
                    throw ospf::OSPFException{ ospf::OSPFErrCode::SerializationFail };
                }
                return succeed;
            }

            template<typename CharT>
            inline Result<rapidjson::Document> read(std::basic_istream<CharT>& is) noexcept
            {
                rapidjson::Document doc;
                rapidjson::BasicIStreamWrapper isw{ is };
                rapidjson::ParseResult ok = doc.ParseStream(isw);
                if (!ok)
                {
                    return OSPFError{ OSPFErrCode::DeserializationFail, std::format("{} at {}", rapidjson::GetParseError_En(ok.Code()), ok.Offset()) };
                }
                else
                {
                    return std::move(doc);
                }
            }
        };
    };
};
