#pragma once

#include <ospf/basic_definition.hpp>
#include <ospf/concepts/base.hpp>
#include <ospf/data_structure/multi_array/shape.hpp>

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

            // for Einstein Notation
            template<
                typename A,
                ShapeType S = DynShape
            >
                requires NotSameAs<typename A::ValueType, void> && (S::dim == dynamic_dimension)
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
