#pragma once

#include <ospf/data_structure/multi_array/concepts.hpp>
#include <ospf/data_structure/multi_array/impl.hpp>
#include <ospf/data_structure/multi_array/map_view.hpp>
#include <ospf/data_structure/multi_array/view.hpp>

namespace ospf
{
    inline namespace data_structure
    {
        namespace multi_array
        {
            template<typename T>
                requires NotSameAs<T, void>
            class MultiArray<T, dynamic_dimension>
            {
                // todo
            };
        };
    };
};
