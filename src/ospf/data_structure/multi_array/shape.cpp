#include <ospf/data_structure/multi_array/shape.hpp>

namespace ospf::data_structure
{
    template class Shape<1_uz>;
    template class Shape<2_uz>;
    template class Shape<3_uz>;
    template class Shape<4_uz>;
    template class Shape<dynamic_dimension>;
};
