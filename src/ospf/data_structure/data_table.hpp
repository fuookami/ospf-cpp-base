#pragma once

#include <ospf/data_structure/data_table/dynamic_column.hpp>
#include <ospf/data_structure/data_table/static_column.hpp>
#include <ospf/data_structure/data_table/single_type.hpp>
#include <ospf/meta_programming/named_flag.hpp>

OSPF_NAMED_TERNARY_FLAG_TEMPLATE(DataTableNullable);
OSPF_NAMED_TERNARY_FLAG_TEMPLATE(DataTableMultiType);

namespace ospf
{
    inline namespace data_structure
    {
        namespace data_table
        {
            template<typename... Ts>
            struct CellTypeTrait
            {
                using Type = std::variant<OriginType<Ts>...>;
            };

            template<typename T>
            struct CellTypeTrait<T>
            {
                using Type = OriginType<T>;
            };
        };

        template<typename T>
        concept DataTableConfigType = requires
        {
            { T::store_type } -> DecaySameAs<StoreType>;
            { T::nullable } -> DecaySameAs<DataTableNullable>;
            { T::multi_type } -> DecaySameAs<DataTableMultiType>;
        };

        template<
            StoreType st = StoreType::Row,
            DataTableNullable n = off,
            DataTableMultiType mt = on
        >
        struct DataTableConfig
        {
            static constexpr const auto store_type = st;
            static constexpr const auto nullable = n;
            static constexpr const auto multi_type = mt;
        };

        template<
            usize col,
            DataTableConfigType C,
            typename... Ts
        >
            requires (C::multi_type == on || col == VariableTypeList<Ts...>::length)
        using DataTable = std::conditional_t<
            C::multi_type == off,
            data_table::STDataTable<C::store_type, Ts...>,
            std::conditional_t<
                C::nullable == on,
                data_table::DataTable<std::optional<typename data_table::CellTypeTrait<Ts...>::Type>, col, C::store_type>,
                data_table::DataTable<typename data_table::CellTypeTrait<Ts...>::Type, col, C::store_type>
            >
        >;

        static constexpr const auto value = (DataTableConfig<>::multi_type == on);

        template<
            DataTableConfigType C,
            typename... Ts
        >
            requires (C::multi_type == on)
        using DynDataTable = std::conditional_t<
            C::nullable == on,
            data_table::DataTable<std::optional<typename data_table::CellTypeTrait<Ts...>::Type>, dynamic_column, C::store_type>,
            data_table::DataTable<typename data_table::CellTypeTrait<Ts...>::Type, dynamic_column, C::store_type>
        >;
    };
};
