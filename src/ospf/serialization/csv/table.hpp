#pragma once

#include <ospf/data_structure/data_table.hpp>

namespace ospf
{
    inline namespace serialization
    {
        using CSVTable = DynDataTable<DataTableConfig<StoreType::Row, on, on>, i64, f64, std::string>;

        template<typename... Ts>
        using ORMCSVTable = DataTable<VariableTypeList<Ts...>::length, DataTableConfig<StoreType::Row, off, off>, Ts...>;
    };

    inline namespace data_structure
    {
        namespace data_table
        {
            extern template class DataTable<std::optional<std::variant<i64, f64, std::string>>, dynamic_column, StoreType::Row>;
        };
    };
};
