#pragma once

#include <ospf/data_structure/store_type.hpp>

namespace ospf
{
    inline namespace data_structure
    {
        inline namespace data_table
        {
            template<
                typename C,
                usize col,
                StoreType st
            >
            class DataTable;
        };
    };
};
