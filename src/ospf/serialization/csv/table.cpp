#include <ospf/serialization/csv/table.hpp>

namespace ospf::data_structure::data_table
{
    template class DataTable<std::optional<std::variant<i64, f64, std::string>>, dynamic_column, StoreType::Row>;
};
