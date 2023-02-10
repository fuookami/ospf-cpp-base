#pragma once

#include <rapidjson/document.h>
#include <functional>
#include <string_view>

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
