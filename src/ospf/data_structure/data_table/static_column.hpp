#pragma once

#include <ospf/data_structure/data_table/impl.hpp>
#include <ospf/data_structure/data_table/dynamic_column.hpp>
#include <ospf/data_structure/reference_array.hpp>
#include <ospf/string/hasher.hpp>

namespace ospf
{
    inline namespace data_structure
    {
        namespace data_table
        {
            template<typename C, usize col>
            class DataTable<C, col, StoreType::Row>
                : public DataTableImpl<
                    col,
                    StoreType::Row, 
                    OriginType<C>, 
                    std::array<DataTableHeader, col>, 
                    std::span<const OriginType<C>, col>,
                    DynRefArray<OriginType<C>>, 
                    std::vector<std::array<OriginType<C>, col>>, 
                    DataTable<C, col, StoreType::Row>
                >
            {
                using Impl = DataTableImpl<
                    col,
                    StoreType::Row,
                    OriginType<C>,
                    std::array<DataTableHeader, col>,
                    std::span<const OriginType<C>, col>,
                    DynRefArray<OriginType<C>>,
                    std::vector<std::array<OriginType<C>, col>>,
                    DataTable<C, col, StoreType::Row>
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
                // todo: to dynamic_column

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
                    for (auto& header : _header)
                    {
                        header.clear();
                    }
                }

                inline void OSPF_CRTP_FUNCTION(clear_table)(void)
                {
                    _table.clear();
                }

            private:
                HeaderType _header;
                StringHashMap<std::string_view, usize> _header_index;
                std::vector<std::array<CellType, col>> _table;
            };

            template<typename C, usize col>
            class DataTable<C, col, StoreType::Column>
                : public DataTableImpl<
                    col,
                    StoreType::Column,
                    OriginType<C>,
                    std::array<DataTableHeader, col>,
                    RefArray<OriginType<C>, col>,
                    std::span<const OriginType<C>>,
                    std::array<std::vector<OriginType<C>>, col>,
                    DataTable<C, col, StoreType::Column>
                >
            {
                using Impl = DataTableImpl<
                    col,
                    StoreType::Column,
                    OriginType<C>,
                    std::array<DataTableHeader, col>,
                    RefArray<OriginType<C>, col>,
                    std::span<const OriginType<C>>,
                    std::array<std::vector<OriginType<C>>, col>,
                    DataTable<C, col, StoreType::Column>
                >;

            public:
                using CellType = OriginType<C>;
                using HeaderType = typename Impl::HeaderType;
                using RowViewType = typename Impl::RowViewType;
                using ColumnViewType = typename Impl::ColumnViewType;
                using TableType = typename Impl::TableType;

            public:
                DataTable(const DataTable& ano) = default;

                // todo

            public:
                DataTable(DataTable&& ano) noexcept = default;
                DataTable& operator=(const DataTable& rhs) = default;
                DataTable& operator=(DataTable&& rhs) noexcept = default;
                ~DataTable(void) = default;

            public:
                // todo: to dynamic_column

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
                    RowViewType ret;
                    for (const auto& column : _table)
                    {
                        ret.push_back(column[i]);
                    }
                    return ret;
                }

                inline ColumnViewType OSPF_CRTP_FUNCTION(get_column)(const usize i) const
                {
                    return ColumnViewType{ _table[i] };
                }

                inline void OSPF_CRTP_FUNCTION(clear_header)(void)
                {
                    for (auto& header : _header)
                    {
                        header.clear();
                    }
                }

                inline void OSPF_CRTP_FUNCTION(clear_table)(void)
                {
                    for (auto& column : _table)
                    {
                        column.clear();
                    }
                }

            private:
                HeaderType _header;
                StringHashMap<std::string_view, usize> _header_index;
                std::array<std::vector<CellType>, col> _table;
            };
        };
    };
};
