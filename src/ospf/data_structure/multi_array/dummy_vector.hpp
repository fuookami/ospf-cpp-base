#pragma once

#include <ospf/functional/either.hpp>
#include <ospf/functional/integer_iterator.hpp>
#include <ospf/functional/range_bounds.hpp>
#include <variant>

namespace ospf
{
    namespace data_structure
    {
        inline namespace multi_array
        {
            namespace dummy_vector
            {
                class DummyIndexInterator
                {
                    using Continuous = RangeBounds<usize>;
                    using Discrete = std::pair<>

                public:

                private:

                };

                struct Range
                {
                private:
                    ospf::Either<IntegerIterator<isize>, IntegerIterator<usize>> _either;
                };
            };
        };
    };
};
