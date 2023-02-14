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
            template<CharType CharT>
            using NameTransfer = std::function<const std::basic_string_view<CharT>(const std::basic_string_view<CharT>)>;
        };
    };
};

namespace std
{
    template<ospf::CharType CharT>
    struct formatter<rapidjson::Value, CharT>
        : public formatter<basic_string_view<CharT>, CharT>
    {
        template<typename FormatContext>
        inline decltype(auto) format(const rapidjson::Value& value, FormatContext& fc)
        {
            std::basic_ostringstream<CharT> sout;
            rapidjson::BasicOStreamWrapper osw{ sout };
            rapidjson::Writer writer{ osw };

            if (!value.Accept(writer))
            {
                throw ospf::OSPFException{ ospf::OSPFErrCode::SerializationFail };
            }

            static const auto _formatter = formatter<basic_string_view<CharT>, CharT>{};
            return _formatter.format(sout.str(), fc);
        }
    };
};
