#pragma once

#include <ospf/memory/reference.hpp>
#include <deque>

namespace ospf
{
    inline namespace data_structure
    {
        template<
            typename T, 
            memory::reference::ReferenceCategory category = memory::reference::ReferenceCategory::Reference,
            template<typename U> class Container = std::vector
        >
        class ReferenceArray
        {
        public:
            using RefType = memory::reference::Ref<T, category>;
            using ArrayType = Container<RefType>;

        public;
            

        private:
            ArrayType _array;
        };
    };
};
