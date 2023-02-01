#pragma once

#include <ospf/data_structure/data_table/impl.hpp>
#include <ospf/data_structure/data_table/dynamic_column.hpp>
#include <ospf/data_structure/reference_array.hpp>
#include <ospf/functional/array.hpp>
#include <ospf/string/hasher.hpp>
#include <iterator>

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
                using typename Impl::CellType;
                using typename Impl::HeaderType;
                using typename Impl::RowViewType;
                using typename Impl::ColumnViewType;
                using typename Impl::TableType;
                using typename Impl::CellWrapperType;
                using typename Impl::RowIterType;
                using typename Impl::RowReverseIterType;
                using typename Impl::ColumnIterType;
                using typename Impl::ColumnReverseIterType;
                using typename Impl::RowConstructor;

            public:
                DataTable(void) = default;

                DataTable(HeaderType header)
                    : _header(std;:move(header)) 
                {
                    for (usize i{ 0_uz }; i != col; ++i)
                    {
                        _header_index.insert({ _header[i].name(), i });
                    }
                }

            public:
                DataTable(const DataTable& ano) = default;
                DataTable(DataTable&& ano) noexcept = default;
                DataTable& operator=(const DataTable& rhs) = default;
                DataTable& operator=(DataTable&& rhs) noexcept = default;
                ~DataTable(void) = default;

            public:
                inline DataTable<CellType, dynamic_column, StoreType::Row> to_dynamic(void) const & noexcept
                {
                    DataTable<CellType, dynamic_column, StoreType::Row> ret{ _header };
                    ret._header_index = _header_index;
                    for (auto& row : _table)
                    {
                        ret._table.push_back(std::vector<CellType>{ row.cbegin(), row.cend() });
                    }
                    return ret;
                }

                inline DataTable<CellType, dynamic_column, StoreType::Row> to_dynamic(void) && noexcept
                {
                    DataTable<CellType, dynamic_column, StoreType::Row> ret{ std::move(_header) };
                    ret._header_index = std::move(_header_index);
                    for (auto& row : _table)
                    {
                        std::vector<CellType> new_row;
                        std::move(row.begin(), row.end(), std::back_inserter(new_row));
                        ret._table.push_back(std::move(new_row));
                    }
                }

            OSPF_CRTP_PERMISSION:
                inline LRefType<HeaderType> OSPF_CRTP_FUNCTION(get_header)(void) noexcept
                {
                    return _header;
                }

                inline void OSPF_CRTP_FUNCTION(set_header)(const usize col, DataTableHeader header) noexcept
                {
                    if (!_header[col].empty())
                    {
                        _header_index.erase(_header[col].name());
                    }
                    _header[col] = std::move(header);
                    _header_index.insert({ _header[col].name(), col });
                    // todo: check column data is fix header
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

                inline void OSPF_CRTP_FUNCTION(insert_row_by_value)(const usize pos, ArgCLRefType<CellType> value)
                {
                    _table.insert(_table.cbegin() + pos, make_array<CellType, col>(value));
                    // todo: check column data is fix header
                }
                
                inline void OSPF_CRTP_FUNCTION(insert_row_by_constructor)(const usize pos, const RowConstructor& constructor)
                {
                    _table.insert(_table.cbegin() + pos, make_array<CellType, col>([this, &constructor](const usize col)
                        {
                            return constructor(col, _header[col]);
                        });
                    // todo: check column data is fix header
                }

                inline void OSPF_CRTP_FUNCTION(erase_row)(const usize pos)
                {
                    _table.erase(_table.begin() + pos);
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
                using typename Impl::CellType;
                using typename Impl::HeaderType;
                using typename Impl::RowViewType;
                using typename Impl::ColumnViewType;
                using typename Impl::TableType;
                using typename Impl::CellWrapperType;
                using typename Impl::RowIterType;
                using typename Impl::RowReverseIterType;
                using typename Impl::ColumnIterType;
                using typename Impl::ColumnReverseIterType;
                using typename Impl::RowConstructor;

            public:
                DataTable(void) = default;

                DataTable(HeaderType header)
                    : _header(std;:move(header)) 
                {
                    for (usize i{ 0_uz }; i != col; ++i)
                    {
                        _header_index.insert({ _header[i].name(), i });
                    }
                }

            public:
                DataTable(const DataTable& ano) = default;
                DataTable(DataTable&& ano) noexcept = default;
                DataTable& operator=(const DataTable& rhs) = default;
                DataTable& operator=(DataTable&& rhs) noexcept = default;
                ~DataTable(void) = default;

            public:
                inline DataTable<CellType, dynamic_column, StoreType::Column> to_dynamic(void) const & noexcept
                {
                    DataTable<CellType, dynamic_column, StoreType::Column> ret{ _header };
                    ret._header_index = _header_index;
                    ret._table.assign(_table.cbegin(), _table.cend());
                    return ret;
                }
                
                inline DataTable<CellType, dynamic_column, StoreType::Column> to_dynamic(void) && noexcept
                {
                    DataTable<CellType, dynamic_column, StoreType::Column> ret{ std::move(_header) };
                    ret._header_index = std::move(_header_index);
                    std::move(_table.begin(), _table.end(), std::back_inserter(ret._table));
                    return ret;
                }

            OSPF_CRTP_PERMISSION:
                inline LRefType<HeaderType> OSPF_CRTP_FUNCTION(get_header)(void) noexcept
                {
                    return _header;
                }

                inline void OSPF_CRTP_FUNCTION(set_header)(const usize col, DataTableHeader header) noexcept
                {
                    if (!_header[col].empty())
                    {
                        _header_index.erase(_header[col].name());
                    }
                    _header[col] = std::move(header);
                    _header_index.insert({ _header[col].name(), col });
                    // todo: check column data is fix header
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

                inline void OSPF_CRTP_FUNCTION(insert_row_by_value)(const usize pos, ArgCLRefType<CellType> value)
                {
                    for (auto& column : _table)
                    {
                        column.insert(column.cbegin(), value);
                        // todo: check column data is fix header
                    }
                }

                inline void OSPF_CRTP_FUNCTION(insert_row_by_constructor)(const usize pos, const RowConstructor& constructor)
                {
                    for (usize i{ 0_uz }; i != col; ++i)
                    {
                        auto& column = _table[i];
                        column.insert(column.cbegin(), constructor(i, _header[i]));
                        // todo: check column data is fix header
                    }
                }

                inline void OSPF_CRTP_FUNCTION(erase_row)(const usize pos)
                {
                    for (auto& column : _table)
                    {
                        column.erase(column.begin() + pos);
                    }
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
