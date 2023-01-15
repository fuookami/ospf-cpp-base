#pragma once

#include <ospf/data_structure/data_table.hpp>

namespace ospf
{
    inline namespace serialization
    {
        using CSVTable = DataTable<DynDataTableConfig<StoreType::Row, off, off>, i64, f64, std::string>;
    };
};
