#pragma once

#include <ospf/data_structure/data_table.hpp>
#include <ospf/meta_programming/meta_info.hpp>

namespace ospf
{
    inline namespace serialization
    {
        using CSVTable = DynDataTable<DataTableConfig<StoreType::Row, on, on>, std::string>;
        using CSVViewTable = DynDataTable<DataTableConfig<StoreType::Row, on, on>, std::string_view>;

        template<usize col>
        using ORMCSVTable = DataTable<col, DataTableConfig<StoreType::Row, off, on>, std::string>;

        template<usize col>
        using ORMCSVViewTable = DataTable<col, DataTableConfig<StoreType::Row, off, on>, std::string_view>;

        // todo: impl for different character

        namespace csv
        {
            template<WithMetaInfo T>
            struct ORMCSVTrait
            {
                inline static constexpr const usize col = meta_info::MetaInfo<T>{}.size();
                using HeaderType = std::array<std::string_view, col>;
                using RowType = std::array<std::string, col>;
                using RowViewType = std::array<std::string_view, col>;
                using TableType = ORMCSVTable<col>;
                using ViewTableType = ORMCSVViewTable<col>;
            };

            template<WithMetaInfo T>
            using ORMHeaderType = typename ORMCSVTrait<T>::HeaderType;

            template<WithMetaInfo T>
            using ORMRowType = typename ORMCSVTrait<T>::RowType;

            template<WithMetaInfo T>
            using ORMRowViewType = typename ORMCSVTrait<T>::RowViewType;

            template<WithMetaInfo T>
            using ORMTableType = typename ORMCSVTrait<T>::TableType;

            template<WithMetaInfo T>
            using ORMViewTableType = typename ORMCSVTrait<T>::ViewTableType;

            template<WithMetaInfo T>
            inline constexpr ORMHeaderType<T> header(const meta_info::MetaInfo<T>& info, const std::optional<std::function<const std::string_view(const std::string_view)>>& transfer) noexcept
            {
                ORMHeaderType<T> header{};
                usize i{ 0_uz };
                info.for_each([&header, &transfer](const auto& field)
                    {
                        header[i] = transfer.has_value() ? (*transfer)(field.key()) : field.key();
                        ++i;
                    });
                return header;
            }
        };

        template<WithMetaInfo T>
        inline csv::ORMTableType<T> make_csv_table(const std::optional<std::function<const std::string_view(const std::string_view)>>& transfer = std::nullopt) noexcept
        {
            static const meta_info::MetaInfo<T> info{};
            return csv::ORMTableType<T>{ csv::header(info, transfer) };
        }

        template<WithMetaInfo T>
        inline csv::ORMViewTableType<T> make_csv_view_table(const std::optional<std::function<const std::string_view(const std::string_view)>>& transfer = std::nullopt) noexcept
        {
            static const meta_info::MetaInfo<T> info{};
            return csv::ORMViewTableType<T>{ csv::header(info, transfer) };
        }
    };

    inline namespace data_structure
    {
        namespace data_table
        {
            extern template class DataTable<std::optional<std::string>, dynamic_column, StoreType::Row>;
            extern template class DataTable<std::optional<std::string_view>, dynamic_column, StoreType::Row>;

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
