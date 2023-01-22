#pragma once

#include <ospf/meta_programming/named_flag.hpp>

OSPF_NAMED_TERNARY_FLAG_TEMPLATE(DataTableNullable);
OSPF_NAMED_TERNARY_FLAG_TEMPLATE(DataTableMultiType);

namespace ospf
{
    inline namespace data_structure
    {
        namespace data_table
        {
            class DataTableHeader;

            template<typename L>
            class DataTableLine;

            template<typename T>
            class DataTableColumn;

            template<
                typename H,
                typename T
            >
            class LSDataTable;

            template<
                typename H,
                typename T
            >
            class CSDataTable;
        };
    };
};
