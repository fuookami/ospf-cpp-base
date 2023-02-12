#pragma once

#include <ospf/data_structure/store_type.hpp>
#include <ospf/meta_programming/variable_type_list.hpp>

namespace ospf
{
    inline namespace data_structure
    {
        namespace data_table
        {
            template<
                typename C,
                usize col,
                StoreType st
            >
            class DataTable;

            template<
                StoreType st,
                typename... Ts
            >
                requires (VariableTypeList<Ts...>::length >= 1_uz)
            class STDataTable;
        };
    };
};
