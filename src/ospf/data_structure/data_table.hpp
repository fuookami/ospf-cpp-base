#pragma once

#include <ospf/basic_definition.hpp>
#include <ospf/data_structure/store_type.hpp>
#include <ospf/data_structure/data_table/concept.hpp>
#include <ospf/data_structure/data_table/cell.hpp>
#include <ospf/data_structure/data_table/line.hpp>
#include <ospf/data_structure/data_table/table.hpp>
#include <ospf/data_structure/optional_array.hpp>
#include <ospf/meta_programming/sequence_tuple.hpp>
#include <variant>

namespace ospf
{
    inline namespace data_structure
    {
        template<
            usize col,
            StoreType st = StoreType::Row,
            DataTableNullable nullable = on,
            DataTableMultiType mt = off,
            template<typename T, usize l> class C1 = std::array,
            template<typename T> class C2 = std::vector
        >
        struct DataTableConfig;

        template<
            StoreType st = StoreType::Row,
            DataTableNullable nullable = on,
            DataTableMultiType multi_type = off,
            template<typename T> class C1 = std::vector,
            template<typename T> class C2 = std::vector
        >
        struct DynDataTableConfig;

        template<
            typename C,
            typename... Args
        >
        using DataTable = typename C::template TableType<Args...>;
    };
};
