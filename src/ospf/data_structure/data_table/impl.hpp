#pragma once

#include <ospf/data_structure/store_type.hpp>
#include <ospf/data_structure/data_table/header.hpp>
#include <ospf/functional/range_bounds.hpp>
#include <ospf/meta_programming/crtp.hpp>
#include <span>

namespace ospf
{
    inline namespace data_structure
    {
        static constexpr const auto dynamic_column = npos;

        namespace data_table
        {
            using RangeFull = range_bounds::RangeFull;

            template<typename T>
            class DataTableRowIterator
            {
            public:
                using TableType = OriginType<T>;
                using RowViewType = typename TableType::RowViewType;

            public:
                inline static DataTableRowIterator begin(const TableType& table) noexcept
                {
                    return DataTableRowIterator{ 0_uz, table };
                }

                inline static DataTableRowIterator end(const TableType& table) noexcept
                {
                    return DataTableRowIterator{ table.row(), table };
                }

            private:
                DataTableRowIterator(const usize i, const TableType& table)
                    : _i(i), _table(table) {}
            public:
                DataTableRowIterator(const DataTableRowIterator& ano) = default;
                DataTableRowIterator(DataTableRowIterator&& ano) noexcept = default;
                DataTableRowIterator& operator=(const DataTableRowIterator& rhs) = default;
                DataTableRowIterator& operator=(DataTableRowIterator&& rhs) noexcept = default;
                ~DataTableRowIterator(void) = default;

            public:
                inline RowViewType operator*(void) const
                {
                    return _table->row(_i);
                }

            public:
                inline DataTableRowIterator& operator++(void)
                {
                    next();
                    return *this;
                }

                inline DataTableRowIterator operator++(int)
                {
                    auto ret = *this;
                    next();
                    return ret;
                }

            public:
                inline const bool operator==(const DataTableRowIterator& rhs) const noexcept
                {
                    return _i == rhs._i && _table == rhs._table;
                }

                inline const bool operator!=(const DataTableRowIterator& rhs) const noexcept
                {
                    return _i != rhs._i || _table != rhs._table;
                }

            private:
                inline void next(void)
                {
                    if (_i == _table->row())
                    {
                        throw OSPFException{ OSPFErrCode::ApplicationFail, "out of row range" };
                    }
                    ++_i;
                }

            private:
                usize _i;
                Ref<TableType> _table;
            };

            template<typename T>
            class DataTableRowReverseIterator
            {
            public:
                using TableType = OriginType<T>;
                using RowViewType = typename TableType::RowViewType;

            public:
                inline static DataTableRowReverseIterator begin(const TableType& table) noexcept
                {
                    return DataTableRowReverseIterator{ table.row() - 1_uz, table };
                }

                inline static DataTableRowReverseIterator end(const TableType& table) noexcept
                {
                    return DataTableRowReverseIterator{ npos, table };
                }

            private:
                DataTableRowReverseIterator(const usize i, const TabelType& table)
                    : _i(i), _table(table) {}
            public:
                DataTableRowReverseIterator(const DataTableRowReverseIterator& ano) = default;
                DataTableRowReverseIterator(DataTableRowReverseIterator&& ano) noexcept = default;
                DataTableRowReverseIterator& operator=(const DataTableRowReverseIterator& rhs) = default;
                DataTableRowReverseIterator& operator=(DataTableRowReverseIterator&& rhs) noexcept = default;
                ~DataTableRowReverseIterator(void) = default;

            public:
                inline RowViewType operator*(void) const
                {
                    return _table->row(_i);
                }

            public:
                inline DataTableRowReverseIterator& operator++(void)
                {
                    next();
                    return *this;
                }

                inline DataTableRowReverseIterator operator++(int)
                {
                    auto ret = *this;
                    next();
                    return ret;
                }

            public:
                inline const bool operator==(const DataTableRowReverseIterator& rhs) const noexcept
                {
                    return _i == rhs._i && _table == rhs._table;
                }

                inline const bool operator!=(const DataTableRowReverseIterator& rhs) const noexcept
                {
                    return _i != rhs._i || _table != rhs._table;
                }

            private:
                inline void next(void)
                {
                    if (_i == npos)
                    {
                        throw OSPFException{ OSPFErrCode::ApplicationFail, "out of row range" };
                    }
                    --_i;
                }

            private:
                usize _i;
                Ref<TableType> _table;
            };

            template<typename T>
            class DataTableColumnIterator
            {
            public:
                using TableType = OriginType<T>;
                using RowViewType = typename TableType::RowViewType;

            public:
                inline static DataTableColumnIterator begin(const TableType& table) noexcept
                {
                    return DataTableColumnIterator{ 0_uz, table };
                }

                inline static DataTableColumnIterator end(const TableType& table) noexcept
                {
                    return DataTableColumnIterator{ table.column(), table };
                }

            private:
                DataTableColumnIterator(const usize i, const TableType& table)
                    : _i(i), _table(table) {}
            public:
                DataTableColumnIterator(const DataTableColumnIterator& ano) = default;
                DataTableColumnIterator(DataTableColumnIterator&& ano) noexcept = default;
                DataTableColumnIterator& operator=(const DataTableColumnIterator& rhs) = default;
                DataTableColumnIterator& operator=(DataTableColumnIterator&& rhs) noexcept = default;
                ~DataTableColumnIterator(void) = default;

            public:
                inline RowViewType operator*(void) const
                {
                    return _table->column(_i);
                }

            public:
                inline DataTableColumnIterator& operator++(void)
                {
                    next();
                    return *this;
                }

                inline DataTableColumnIterator operator++(int)
                {
                    auto ret = *this;
                    next();
                    return ret;
                }

            public:
                inline const bool operator==(const DataTableColumnIterator& rhs) const noexcept
                {
                    return _i == rhs._i && _table == rhs._table;
                }

                inline const bool operator!=(const DataTableColumnIterator& rhs) const noexcept
                {
                    return _i != rhs._i || _table != rhs._table;
                }

            private:
                inline void next(void)
                {
                    if (_i == _table->column())
                    {
                        throw OSPFException{ OSPFErrCode::ApplicationFail, "out of column range" };
                    }
                    ++_i;
                }

            private:
                usize _i;
                Ref<TableType> _table;
            };

            template<typename T>
            class DataTableColumnReverseIterator
            {
            public:
                using TableType = OriginType<T>;
                using RowViewType = typename TableType::RowViewType;

            public:
                inline static DataTableColumnReverseIterator begin(const TableType& table) noexcept
                {
                    return DataTableColumnReverseIterator{ table.column() - 1_uz, table};
                }

                inline static DataTableColumnReverseIterator end(const TableType& table) noexcept
                {
                    return DataTableColumnReverseIterator{ npos, table };
                }

            private:
                DataTableColumnReverseIterator(const usize i, const TableType& table)
                    : _i(i), _table(table) {}
            public:
                DataTableColumnReverseIterator(const DataTableColumnReverseIterator& ano) = default;
                DataTableColumnReverseIterator(DataTableColumnReverseIterator&& ano) noexcept = default;
                DataTableColumnReverseIterator& operator=(const DataTableColumnReverseIterator& rhs) = default;
                DataTableColumnReverseIterator& operator=(DataTableColumnReverseIterator&& rhs) noexcept = default;
                ~DataTableColumnReverseIterator(void) = default;

            public:
                inline RowViewType operator*(void) const
                {
                    return _table->column(_i);
                }

            public:
                inline DataTableColumnIterator& operator++(void)
                {
                    next();
                    return *this;
                }

                inline DataTableColumnIterator operator++(int)
                {
                    auto ret = *this;
                    next();
                    return ret;
                }

            public:
                inline const bool operator==(const DataTableColumnIterator& rhs) const noexcept
                {
                    return _i == rhs._i && _table == rhs._table;
                }

                inline const bool operator!=(const DataTableColumnIterator& rhs) const noexcept
                {
                    return _i != rhs._i || _table != rhs._table;
                }

            private:
                inline void next(void)
                {
                    if (_i == npos)
                    {
                        throw OSPFException{ OSPFErrCode::ApplicationFail, "out of column range" };
                    }
                    --_i;
                }

            private:
                usize _i;
                Ref<TableType> _table;
            };

            template<typename T>
            class DataTableRows
            {
            public:
                using TableType = OriginType<T>;
                using RowViewType = typename TableType::RowViewType;

                // todo: operator[]
                // todo: begin, end
                // todo: rbegin, rend
            };

            template<typename T>
            class DataTableColumns
            {
            public:
                using TableType = OriginType<T>;
                using ColumnViewType = typename TableType::ColumnViewType;

                // todo: operator[]
                // todo: begin, end
                // todo: rbegin, rend
            };

            template<
                usize col,
                StoreType st,
                typename C,
                typename H,
                typename R,
                typename C,
                typename T, 
                typename Self
            >
            class DataTableImpl
            {
                OSPF_CRTP_IMPL

            public:
                static constexpr const StoreType store_type = st;
                using CellType = OriginType<C>;
                using HeaderType = OriginType<H>;
                using HeaderViewType = std::span<DataTableHeader, col>;
                using RowViewType = OriginType<R>;
                using ColumnViewType = OriginType<C>;
                using TableType = OriginType<T>;

            protected:
                DataTableImpl(void) = default;
            public:
                DataTableImpl(const DataTableImpl& ano) = default;
                DataTableImpl(DataTableImpl&& ano) noexcept = default;
                DataTableImpl& operator=(const DataTableImpl& rhs) = default;
                DataTableImpl& operator=(DataTableImpl&& rhs) noexcept = default;
                ~DataTableImpl(void) = default;

            public:
                inline const bool empty(void) const noexcept
                {
                    return body().empty();
                }

                inline const usize row(void) const noexcept
                {
                    if constexpr (st == StoreType::Row)
                    {
                        return body().size();
                    }
                    else
                    {
                        return body().empty() ? 0_uz : body().front().size();
                    }
                }

                inline const usize column(void) const noexcept
                {
                    return header().size();
                }

            public:
                inline const HeaderViewType header(void) const noexcept
                {
                    return Trait::get_const_header(self());
                }

                inline const bool contains_header(const std::string_view header) const noexcept
                {
                    return header_index(header) != std::nullopt;
                }

                inline const std::optional<usize> header_index(const std::string_view header) const noexcept
                {
                    return Trait::get_column_index(header);
                }

                inline CLRefType<TableType> body(void) const noexcept
                {
                    return Trait::get_const_table(self());
                }

            public:
                inline LRefType<CellType> operator[](const std::array<usize, 2_uz> vector)
                {
                    if constexpr (st == StoreType::Row)
                    {
                        return Trait::get_table(self())[vector[0_uz]][vector[1_uz]];
                    }
                    else
                    {
                        return Trait::get_table(self())[vector[1_uz]][vector[0_uz]];
                    }
                }

                inline CLRefType<CellType> operator[](const std::array<usize, 2_uz> vector) const
                {
                    if constexpr (st == StoreType::Row)
                    {
                        return Trait::get_const_table(self())[vector[0_uz]][vector[1_uz]];
                    }
                    else
                    {
                        return Trait::get_const_table(self())[vector[1_uz]][vector[0_uz]];
                    }
                }

                inline LRefType<CellType> operator[](const std::pair<usize, std::string_view> vector)
                {
                    if constexpr (st == StoreType::Row)
                    {
                        return Trait::get_table(self())[vector.first][Trait::get_column_index(self(), vector.second)];
                    }
                    else
                    {
                        return Trait::get_table(self())[Trait::get_column_index(self(), vector.second)][vector.first];
                    }
                }

                inline CLRefType<CellType> operator[](const std::pair<usize, std::string_view> vector) const
                {
                    if constexpr (st == StoreType::Row)
                    {
                        return Trait::get_const_table(self())[vector.first][Trait::get_column_index(self(), vector.second)];
                    }
                    else
                    {
                        return Trait::get_const_table(self())[Trait::get_column_index(self(), vector.second)][vector.first];
                    }
                }

                inline RowViewType operator[](const std::pair<usize, RangeFull> vector) const
                {
                    return row(vector.first);
                }

                inline ColumnViewType operator[](const std::pair<RangeFull, usize> vector) const
                {
                    return column(vector.second);
                }

                inline ColumnViewType operator[](const std::pair<RangeFull, std::string_view> vector) const
                {
                    return column(vector.second);
                }

            public:
                inline DataTableRows<Self> rows(void) const noexcept
                {
                    return DataTableRows<Self>{ self() };
                }

                inline DataTableColumns<Self> columns(void) const noexcept
                {
                    return DataTableRows<Self>{ self() };
                }

                inline RowViewType row(const usize i) const
                {
                    return Trait::get_row(self(), i);
                }

                inline ColumnViewType column(const usize i) const
                {
                    return Trait::get_column(self(), i);
                }

                inline ColumnViewType column(const std::string_view header) const
                {
                    return Trait::get_column(self(), header_index(header));
                }

            public:
                // todo: insert row
                // todo: insert column

            public:
                // todo: clear
                // todo: erase row
                // todo: erase column

            private:
                struct Trait : public Self
                {
                    inline static LRefType<HeaderType> get_header(Self& self) noexcept
                    {
                        static const auto get_impl = &Self::OSPF_CRTP_FUNCTION(get_header);
                        return (self.*get_impl)();
                    }

                    inline static CLRefType<HeaderType> get_const_header(const Self& self) noexcept
                    {
                        static const auto get_impl = &Self::OSPF_CRTP_FUNCTION(get_const_header);
                        return (self.*get_impl)();
                    }

                    inline static const std::optional<usize> get_column_index(const Self& self, const std::string_view header) noexcept
                    {
                        static const auto get_impl = &Self::OSPF_CRTP_FUNCTION(get_column_index);
                        return (self.*get_impl)(header);
                    }

                    inline static LRefType<TableType> get_table(Self& self) noexcept
                    {
                        static const auto get_impl = &Self::OSPF_CRTP_FUNCTION(get_const_table);
                        return (self.*get_impl)();
                    }

                    inline static CLRefType<TableType> get_const_table(const Self& self) noexcept
                    {
                        static const auto get_impl = &Self::OSPF_CRTP_FUNCTION(get_const_table);
                        return (self.*get_impl)();
                    }

                    inline static RowViewType get_row(const Self& self, const usize i) noexcept
                    {
                        static const auto get_impl = &Self::OSPF_CRTP_FUNCTION(get_row);
                        return (self.*get_impl)(i);
                    }

                    inline static ColumnViewType get_column(const Self& self, const usize i) noexcept
                    {
                        static const auto get_impl = &Self::OSPF_CRTP_FUNCTION(get_column);
                        return (self.*get_impl)(i);
                    }
                };
            };
        };
    };
};
