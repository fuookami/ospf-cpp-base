#pragma once

#include <boost/algorithm/string/split.hpp>
#include <typeinfo>
#include <typeindex>

namespace ospf
{
    inline namespace meta_programming
    {
        template<typename T_>
        struct TypeInfo
        {
        public:
            TypeInfo(void) = delete;

            inline static decltype(auto) info(void)
            {
                static const auto& ret = typeid(T_);
                return ret;
            }

            inline static decltype(auto) index(void)
            {
                static const auto ret = std::type_index(info());
                return ret;
            }

            inline static const std::string_view full_name(void)
            {
                return info().name();
            }

            inline static const std::string_view name(void)
            {
                static const std::string ret = boost::split(info().name(), " :").back();
                return ret;
            }
        };
    };
};
