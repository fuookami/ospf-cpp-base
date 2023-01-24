#pragma once

#include <ospf/basic_definition.hpp>
#include <ospf/concepts/base.hpp>

namespace ospf
{
    inline namespace data_structure
    {
        static constexpr const auto dynamic_dimension = std::dynamic_extent;

        namespace multi_array
        {
            template<
                typename T,
                usize dim
            >
                requires NotSameAs<T, void>
            class MultiArray;

            template<
                typename T,
                usize dim
            >
                requires NotSameAs<T, void>
            class MultiArrayView;

            template<
                typename T,
                usize dim
            >
                requires NotSameAs<T, void> && (dim != dynamic_dimension)
            class MultiArrayMapView;
        };
    };
};
