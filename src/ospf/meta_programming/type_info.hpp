#pragma once

#include <boost/algorithm/string/split.hpp>
#include <typeinfo>
#include <typeindex>

namespace ospf
{
    inline namespace meta_programming
    {
        template<typename T>
        struct TypeInfo
        {
        public:
            TypeInfo(void) = delete;

            inline static decltype(auto) info(void)
            {
                static const auto& ret = typeid(T);
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
                static const std::string ret = name(index());
                return ret;
            }
        };

        inline const std::string name(const std::type_index type) noexcept
        {
            std::vector<std::string> split_result;
            return boost::split(split_result, type.name(), " :").back();
        }
    };
};
