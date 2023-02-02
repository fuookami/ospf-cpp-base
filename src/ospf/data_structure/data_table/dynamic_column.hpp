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

                template<
                    typename C,
                    usize col,
                    StoreType st
                >
                friend class DataTable;

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
                using ColumnConstructor = std::function<RetType<CellType>(const usize)>;

            public:
                DataTable(void) = default;

                DataTable(HeaderType header)
                    : _header(std;:move(header)) 
                {
                    for (usize i{ 0_uz }; i != _header.size(); ++i)
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
                template<typename = void>
                    requires WithDefault<CellType>
                inline const usize insert_column(const usize pos, ArgRRefType<DataTableHeader> header)
                {
                    return insert_row(pos, move<DataTableHeader>(header), DefaultValue<CellType>::value);
                }

                inline const usize insert_column(const usize pos, ArgRRefType<DataTableHeader> header, ArgCLRefType<CellType> value)
                {
                    for (auto& [h, i] : _header_index)
                    {
                        if (i >= pos)
                        {
                            ++i;
                        }
                    }
                    _header.insert(_header.cbegin() + pos, move<DataTableHeader>(header));
                    _header_index.insert({ _header[i].name(), pos });
                    for (auto& row : _table)
                    {
                        row.insert(row.cbegin() + pos, value);
                    }
                    // todo: check column data is fix header
                    return pos + 1_uz;
                }

                template<typename U>
                inline const usize insert_column(const usize pos, ArgRRefType<DataTableHeader> header, U&& value)
                {
                    return insert_column(pos, move<DataTableHeader>(header), CellType{ std::forward<U>(value) });
                }

                inline const usize insert_column(const usize pos, ArgRRefType<DataTableHeader> header, const ColumnConstructor& constructor)
                {
                    for (auto& [h, i] : _header_index)
                    {
                        if (i >= pos)
                        {
                            ++i;
                        }
                    }
                    _header.insert(_header.cbegin() + pos, move<DataTableHeader>(header));
                    _header_index.insert({ _header[i].name(), pos });
                    for (usize i{ 0_uz }; i != this->row(); ++i)
                    {
                        auto& row = _table[i];
                        row.insert(row.cbegin() + pos, constructor(i));
                    }
                    // todo: check column data is fix header
                    return pos + 1_uz;
                }

                template<typename = void>
                    requires WithDefault<CellType>
                inline RetType<ColumnIterType> insert_column(ArgCLRefType<ColumnIterType> pos, ArgRRefType<DataTableHeader> header)
                {
                    return insert_column(pos, move<DataTableHeader>(header), DefaultValue<CellType>::value);
                }

                inline RetType<ColumnIterType> insert_column(ArgCLRefType<ColumnIterType> pos, ArgRRefType<DataTableHeader> header, ArgCLRefType<CellType> value)
                {
                    insert_column(static_cast<const usize>(pos), move<DataTableHeader>(header), value);
                    return pos + 1_iz;
                }

                template<typename U>
                inline RetType<ColumnIterType> insert_column(ArgCLRefType<ColumnIterType> pos, ArgRRefType<DataTableHeader> header, U&& value)
                {
                    return insert_column(pos, move<DataTableHeader>(header), CellType{ std::forward<U>(value) });
                }

                inline RetType<ColumnIterType> insert_column(ArgCLRefType<ColumnIterType> pos, ArgRRefType<DataTableHeader> header, const ColumnConstructor& constructor)
                {
                    insert_column(static_cast<const usize>(pos), move<DataTableHeader>(header), constructor);
                    return pos + 1_iz;
                }

            OSPF_CRTP_PERMISSION:
                inline LRefType<HeaderType> OSPF_CRTP_FUNCTION(get_header)(void) noexcept
                {
                    return _header;
                }

                inline void OSPF_CRTP_FUNCTION(set_header)(const usize col, ArgRRefType<DataTableHeader> header) noexcept
                {
                    if (!_header[col].empty())
                    {
                        _header_index.erase(_header[col].name());
                    }
                    _header[col] = move<DataTableHeader>(header);
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

                inline void OSPF_CRTP_FUNCTION(clear_header)(void)
                {
                    _header.clear();
                }

                inline void OSPF_CRTP_FUNCTION(insert_row_by_value)(const usize pos, ArgCLRefType<CellType> value)
                {
                    _table.insert(_table.cbegin() + pos, std::vector<CellType>{ this->column(), value });
                    // todo: check column data is fix header
                }

                inline void OSPF_CRTP_FUNCTION(insert_row_by_constructor)(const usize pos, const RowConstructor& constructor)
                {
                    std::vector<CellType> new_row;
                    new_row.reserve(this->column());
                    for (usize i{ 0_uz }; i != this->column(); ++i)
                    {
                        new_row.push_back(constructor(i, _header[i]));
                        // todo: check column data is fix header
                    }
                    _table.insert(_table.cbegin() + pos, std::move(new_row));
                }

                inline void OSPF_CRTP_FUNCTION(erase_row)(const usize pos)
                {
                    _table.erase(_table.begin() + pos);
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

                template<
                    typename C,
                    usize col,
                    StoreType st
                >
                friend class DataTable;

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
                using ColumnConstructor = std::function<RetType<CellType>(const usize)>;

            public:
                DataTable(void) = default;

                DataTable(HeaderType header)
                    : _header(std;:move(header)) 
                {
                    for (usize i{ 0_uz }; i != _header.size(); ++i)
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
                template<typename = void>
                    requires WithDefault<CellType>
                inline const usize insert_column(const usize pos, ArgRRefType<DataTableHeader> header)
                {
                    return insert_row(pos, move<DataTableHeader>(header), DefaultValue<CellType>::value);
                }

                inline const usize insert_column(const usize pos, ArgRRefType<DataTableHeader> header, ArgCLRefType<CellType> value)
                {
                    for (auto& [h, i] : _header_index)
                    {
                        if (i >= pos)
                        {
                            ++i;
                        }
                    }
                    _header.insert(_header.cbegin() + pos, move<DataTableHeader>(header));
                    _header_index.insert({ _header[i].name(), pos });
                    _table.insert(_table.cbegin() + pos, std::vector<CellType>{ this->row(), value });
                    // todo: check column data is fix header
                    return pos + 1_uz;
                }

                template<typename U>
                inline const usize insert_column(const usize pos, ArgRRefType<DataTableHeader> header, U&& value)
                {
                    return insert_column(pos, move<DataTableHeader>(header), CellType{ std::forward<U>(value) });
                }

                inline const usize insert_column(const usize pos, ArgRRefType<DataTableHeader> header, const ColumnConstructor& constructor)
                {
                    for (auto& [h, i] : _header_index)
                    {
                        if (i >= pos)
                        {
                            ++i;
                        }
                    }
                    _header.insert(_header.cbegin() + pos, move<DataTableHeader>(header));
                    _header_index.insert({ _header[i].name(), pos });
                    std::vector<CellType> new_column;
                    new_column.reserve(this->row());
                    for (usize i{ 0_uz }; i != this->row(); ++i)
                    {
                        new_column.push_back(constructor(i));
                    }
                    // todo: check column data is fix header
                    _table.insert(_table.cbegin() + pos, std::move(new_column));
                    return pos + 1_uz;
                }

                template<typename = void>
                    requires WithDefault<CellType>
                inline RetType<ColumnIterType> insert_column(ArgCLRefType<ColumnIterType> pos, ArgRRefType<DataTableHeader> header)
                {
                    return insert_column(pos, move<DataTableHeader>(header), DefaultValue<CellType>::value);
                }

                inline RetType<ColumnIterType> insert_column(ArgCLRefType<ColumnIterType> pos, ArgRRefType<DataTableHeader> header, ArgCLRefType<CellType> value)
                {
                    insert_column(static_cast<const usize>(pos), move<DataTableHeader>(header), value);
                    return pos + 1_iz;
                }

                template<typename U>
                inline RetType<ColumnIterType> insert_column(ArgCLRefType<ColumnIterType> pos, ArgRRefType<DataTableHeader> header, U&& value)
                {
                    return insert_column(pos, move<DataTableHeader>(header), CellType{ std::forward<U>(value) });
                }

                inline RetType<ColumnIterType> insert_column(ArgCLRefType<ColumnIterType> pos, ArgRRefType<DataTableHeader> header, const ColumnConstructor& constructor)
                {
                    insert_column(static_cast<const usize>(pos), move<DataTableHeader>(header), constructor);
                    return pos + 1_iz;
                }

            OSPF_CRTP_PERMISSION:
                inline LRefType<HeaderType> OSPF_CRTP_FUNCTION(get_header)(void) noexcept
                {
                    return _header;
                }

                inline void OSPF_CRTP_FUNCTION(set_header)(const usize col, ArgRRefType<DataTableHeader> header) noexcept
                {
                    if (!_header[col].empty())
                    {
                        _header_index.erase(_header[col].name());
                    }
                    _header[col] = move<DataTableHeader>(header);
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
                        column.insert(column.cbegin() + pos, value);
                        // todo: check column data is fix header
                    }
                }

                inline void OSPF_CRTP_FUNCTION(insert_row_by_constructor)(const usize pos, const RowConstructor& constructor)
                {
                    for (usize i{ 0_uz }; i != this->column(); ++i)
                    {
                        auto& column = _table[i];
                        column.insert(column.cbegin() + pos, constructor(i, _header[i]));
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
