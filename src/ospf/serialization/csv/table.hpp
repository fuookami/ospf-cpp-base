#pragma once

#include <ospf/data_structure/data_table.hpp>

namespace ospf
{
    inline namespace serialization
    {
        using CSVTable = DynDataTable<DataTableConfig<StoreType::Row, on, on>, std::string>;

        template<usize col>
        using ORMCSVTable = DataTable<col, DataTableConfig<StoreType::Row, off, on>, std::string>;

        template<usize col>
        using ORMCSVTableView = DataTable<col, DataTableConfig<StoreType::Row, off, on>, std::string_view>;
    };

    inline namespace data_structure
    {
        namespace data_table
        {
            extern template class DataTable<std::optional<std::string>, dynamic_column, StoreType::Row>;

            extern template class DataTable<std::string, 1_uz, StoreType::Row>;
            extern template class DataTable<std::string, 2_uz, StoreType::Row>;
            extern template class DataTable<std::string, 3_uz, StoreType::Row>;
            extern template class DataTable<std::string, 4_uz, StoreType::Row>;
            extern template class DataTable<std::string, 5_uz, StoreType::Row>;
            extern template class DataTable<std::string, 6_uz, StoreType::Row>;
            extern template class DataTable<std::string, 7_uz, StoreType::Row>;
            extern template class DataTable<std::string, 8_uz, StoreType::Row>;
            extern template class DataTable<std::string, 9_uz, StoreType::Row>;
            extern template class DataTable<std::string, 10_uz, StoreType::Row>;
            extern template class DataTable<std::string, 11_uz, StoreType::Row>;
            extern template class DataTable<std::string, 12_uz, StoreType::Row>;
            extern template class DataTable<std::string, 13_uz, StoreType::Row>;
            extern template class DataTable<std::string, 14_uz, StoreType::Row>;
            extern template class DataTable<std::string, 15_uz, StoreType::Row>;
            extern template class DataTable<std::string, 16_uz, StoreType::Row>;
            extern template class DataTable<std::string, 17_uz, StoreType::Row>;
            extern template class DataTable<std::string, 18_uz, StoreType::Row>;
            extern template class DataTable<std::string, 19_uz, StoreType::Row>;
            extern template class DataTable<std::string, 20_uz, StoreType::Row>;

            extern template class DataTable<std::string_view, 1_uz, StoreType::Row>;
            extern template class DataTable<std::string_view, 2_uz, StoreType::Row>;
            extern template class DataTable<std::string_view, 3_uz, StoreType::Row>;
            extern template class DataTable<std::string_view, 4_uz, StoreType::Row>;
            extern template class DataTable<std::string_view, 5_uz, StoreType::Row>;
            extern template class DataTable<std::string_view, 6_uz, StoreType::Row>;
            extern template class DataTable<std::string_view, 7_uz, StoreType::Row>;
            extern template class DataTable<std::string_view, 8_uz, StoreType::Row>;
            extern template class DataTable<std::string_view, 9_uz, StoreType::Row>;
            extern template class DataTable<std::string_view, 10_uz, StoreType::Row>;
            extern template class DataTable<std::string_view, 11_uz, StoreType::Row>;
            extern template class DataTable<std::string_view, 12_uz, StoreType::Row>;
            extern template class DataTable<std::string_view, 13_uz, StoreType::Row>;
            extern template class DataTable<std::string_view, 14_uz, StoreType::Row>;
            extern template class DataTable<std::string_view, 15_uz, StoreType::Row>;
            extern template class DataTable<std::string_view, 16_uz, StoreType::Row>;
            extern template class DataTable<std::string_view, 17_uz, StoreType::Row>;
            extern template class DataTable<std::string_view, 18_uz, StoreType::Row>;
            extern template class DataTable<std::string_view, 19_uz, StoreType::Row>;
            extern template class DataTable<std::string_view, 20_uz, StoreType::Row>;
        };
    };
};
