#include <ospf/functional/range_bounds.hpp>

namespace ospf::function
{
    template class Bound<usize>;
    template class Bound<isize>;
    template class RangeBounds<usize>;
    template class RangeBounds<isize>;
};
