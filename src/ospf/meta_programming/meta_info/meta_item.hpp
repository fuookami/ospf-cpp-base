#pragma once

#include <ospf/functional/sequence_tuple.hpp>
#include <ospf/meta_programming/function_trait.hpp>
#include <ospf/meta_programming/type_info.hpp>
#include <ospf/type_family.hpp>

namespace ospf
{
    inline namespace meta_programming
    {
        namespace meta_info
        {
            template<typename T, typename Self>
            class MetaItemImpl
            {
                OSPF_CRTP_IMPL
            };
        };
    };
};
