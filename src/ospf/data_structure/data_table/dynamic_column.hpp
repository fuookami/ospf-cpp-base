#pragma once

#include <ospf/data_structure/data_table/impl.hpp>
#include <ospf/data_structure/reference_array.hpp>
#include <ospf/string/hasher.hpp>

namespace ospf
{
    inline namespace data_structure
    {
        namespace data_table
        {
            template<typename C>
            class DataTable<C, dynamic_column, StoreType::Row>
                : public DataTableImpl<
                    dynamic_column, 
                    StoreType::Row, 
                    OriginType<C>, 
                    std::vector<DataTableHeader>, 
                    std::span<const OriginType<C>>, 
                    DynRefArray<OriginType<C>>, 
                    std::vector<std::vector<OriginType<C>>>, 
                    DataTable<C, dynamic_column, StoreType::Row>
                >
            {
                using Impl = DataTableImpl<
                    dynamic_column,
                    StoreType::Row,
                    OriginType<C>,
                    std::vector<DataTableHeader>,
                    std::span<const OriginType<C>>,
                    DynRefArray<OriginType<C>>,
                    std::vector<std::vector<OriginType<C>>>,
                    DataTable<C, dynamic_column, StoreType::Row>
                >;

            public:
                using CellType = OriginType<C>;
                using HeaderType = typename Impl::HeaderType;
                using RowViewType = typename Impl::RowViewType;
                using ColumnViewType = typename Impl::ColumnViewType;
                using TableType = typename Impl::TableType;

            public:
                DataTable(void) = default;

                // todo

            public:
                DataTable(const DataTable& ano) = default;
                DataTable(DataTable&& ano) noexcept = default;
                DataTable& operator=(const DataTable& rhs) = default;
                DataTable& operator=(DataTable&& rhs) noexcept = default;
                ~DataTable(void) = default;

            public:
                // todo

            OSPF_CRTP_PERMISSION:
                inline LRefType<HeaderType> OSPF_CRTP_FUNCTION(get_header)(void) noexcept
                {
                    return _header;
                }

                inline CLRefType<HeaderType> OSPF_CRTP_FUNCTION(get_const_header)(void) const noexcept
                {
                    return _header;
                }

                inline const std::optional<usize> OSPF_CRTP_FUNCTION(get_column_index)(const std::string_view header) const noexcept
                {
                    const auto it = _header_index.find(header);
                    if (it != _header_index.cend())
                    {
                        return *it;
                    }
                    else
                    {
                        return std::nullopt;
                    }
                }

                inline LRefType<TableType> OSPF_CRTP_FUNCTION(get_table)(void) noexcept
                {
                    return _table;
                }

                inline CLRefType<TableType> OSPF_CRTP_FUNCTION(get_const_table)(void) const noexcept
                {
                    return _table;
                }

                inline RowViewType OSPF_CRTP_FUNCTION(get_row)(const usize i) const
                {
                    return RowViewType{ _table[i] };
                }

                inline ColumnViewType OSPF_CRTP_FUNCTION(get_column)(const usize i) const
                {
                    ColumnViewType ret;
                    for (const auto& row : _table)
                    {
                        ret.push_back(row[i]);
                    }
                    return ret;
                }

                inline void OSPF_CRTP_FUNCTION(clear_header)(void)
                {
                    _header.clear();
                }

                inline void OSPF_CRTP_FUNCTION(clear_table)(void)
                {
                    _table.clear();
                }

            private:
                HeaderType _header;
                StringHashMap<std::string_view, usize> _header_index;
                std::vector<std::vector<CellType>> _table;
            };

            template<typename C>
            class DataTable<C, dynamic_column, StoreType::Column>
                : public DataTableImpl<
                    dynamic_column, 
                    StoreType::Column,
                    OriginType<C>, 
                    std::vector<DataTableHeader>, 
                    std::span<const OriginType<C>>, 
                    DynRefArray<OriginType<C>>, 
                    std::vector<std::vector<OriginType<C>>>, 
                    DataTable<C, dynamic_column, StoreType::Column>
                >
            {
                using Impl = DataTableImpl<
                    dynamic_column,
                    StoreType::Column,
                    OriginType<C>,
                    std::vector<DataTableHeader>,
                    std::span<const OriginType<C>>,
                    DynRefArray<OriginType<C>>,
                    std::vector<std::vector<OriginType<C>>>,
                    DataTable<C, dynamic_column, StoreType::Column>
                >;

            public:
                using CellType = OriginType<C>;
                using HeaderType = typename Impl::HeaderType;
                using RowViewType = typename Impl::RowViewType;
                using ColumnViewType = typename Impl::ColumnViewType;
                using TableType = typename Impl::TableType;

            public:
                DataTable(void) = default;

                // todo

            public:
                DataTable(const DataTable& ano) = default;
                DataTable(DataTable&& ano) noexcept = default;
                DataTable& operator=(const DataTable& rhs) = default;
                DataTable& operator=(DataTable&& rhs) noexcept = default;
                ~DataTable(void) = default;

            public:
                // todo

            OSPF_CRTP_PERMISSION:
                inline LRefType<HeaderType> OSPF_CRTP_FUNCTION(get_header)(void) noexcept
                {
                    return _header;
                }

                inline CLRefType<HeaderType> OSPF_CRTP_FUNCTION(get_const_header)(void) const noexcept
                {
                    return _header;
                }

                inline const std::optional<usize> OSPF_CRTP_FUNCTION(get_column_index)(const std::string_view header) const noexcept
                {
                    const auto it = _header_index.find(header);
                    if (it != _header_index.cend())
                    {
                        return *it;
                    }
                    else
                    {
                        return std::nullopt;
                    }
                }

                inline LRefType<TableType> OSPF_CRTP_FUNCTION(get_table)(void) noexcept
                {
                    return _table;
                }

                inline CLRefType<TableType> OSPF_CRTP_FUNCTION(get_const_table)(void) const noexcept
                {
                    return _table;
                }

                inline RowViewType OSPF_CRTP_FUNCTION(get_row)(const usize i) const
                {
                    return RowViewType{ _table[i] };
                }

                inline ColumnViewType OSPF_CRTP_FUNCTION(get_column)(const usize i) const
                {
                    ColumnViewType ret;
                    for (const auto& row : _table)
                    {
                        ret.push_back(row[i]);
                    }
                    return ret;
                }

                inline void OSPF_CRTP_FUNCTION(clear_header)(void)
                {
                    _header.clear();
                }

                inline void OSPF_CRTP_FUNCTION(clear_table)(void)
                {
                    _table.clear();
                }

            private:
                HeaderType _header;
                StringHashMap<std::string_view, usize> _header_index;
                std::vector<std::vector<CellType>> _table;
            };
        };
    };
};
