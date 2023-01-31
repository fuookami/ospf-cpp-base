#pragma once

#include <ospf/data_structure/data_table/concepts.hpp>

namespace ospf
{
    inline namespace data_structure
    {
        namespace data_table
        {
            template<typename... Ts>
            class STDataTable<StoreType::Row, Ts...>
            {
                // todo
            };

            template<typename... Ts>
            class STDataTable<StoreType::Column, Ts...>
            {
                // todo
            };
        };
    };
};
