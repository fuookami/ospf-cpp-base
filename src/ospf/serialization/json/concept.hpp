#pragma once

#include <ospf/exception.hpp>
#include <rapidjson/document.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>
#include <functional>
#include <string_view>
#include <sstream>

namespace ospf
{
    inline namespace serialization
    {
        namespace json
        {
            using Object = rapidjson::Value;
            using Array = rapidjson::GenericArray<true, rapidjson::Value>;
            using String = const char*;
            using NameTransfer = std::function<const std::string_view(const std::string_view)>;
        };
    };
};

namespace std
{
    template<typename CharT>
    struct formatter<rapidjson::Value, CharT>
        : public formatter<string_view, CharT>
    {
        template<typename FormatContext>
        inline decltype(auto) format(const rapidjson::Value& value, FormatContext& fc)
        {
            std::basic_ostream<CharT> sout;
            rapidjson::BasicOStreamWrapper osw{ sout };
            rapidjson::Writer writer{ osw };

            if (!value.Accept(writer))
            {
                throw ospf::OSPFException{ ospf::OSPFErrCode::SerializationFail };
            }

            static const auto _formatter = formatter<string_view, CharT>{};
            return _formatter.format(ospf::to_string(sout.str()), fc);
        }
    };
};
