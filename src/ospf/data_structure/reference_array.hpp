#pragma once

#include <ospf/basic_definition.hpp>
#include <ospf/concepts/with_default.hpp>
#include <ospf/literal_constant.hpp>
#include <ospf/memory/reference.hpp>
#include <ospf/meta_programming/iterator.hpp>
#include <boost/iterator/transform_iterator.hpp>

namespace ospf
{
    inline namespace data_structure
    {
        namespace reference_array
        {
            template<
                typename T,
                usize len,
                reference::ReferenceCategory cat,
                template<typename T, usize l> class C
            >
            class StaticReferenceArray;

            template<
                typename T,
                reference::ReferenceCategory cat,
                template<typename T> class C
            >
            class DynamicReferenceArray;

            template<typename T, reference::ReferenceCategory cat, typename C>
            class ReferenceArrayConstIterator
                : public RandomIteratorImpl<reference::Ref<OriginType<T>, cat>, typename OriginType<C>::const_iterator, ReferenceArrayConstIterator<T, cat, C>>
            {
                template<
                    typename T,
                    usize len,
                    reference::ReferenceCategory cat,
                    template<typename T, usize l> class C
                >
                friend class StaticReferenceArray;

                template<
                    typename T,
                    reference::ReferenceCategory cat,
                    template<typename T> class C
                >
                friend class DynamicReferenceArray;
            };
        };

        template<
            typename T,
            usize len,
            reference::ReferenceCategory cat = reference::ReferenceCategory::Reference,
            template<typename T, usize l> class C = std::array
        >
        using RefArray = reference_array::StaticReferenceArray<T, len, cat, C>;

        template<
            typename T,
            usize len,
            template<typename T, usize l> class C = std::array
        >
        using BorrowArray = reference_array::StaticReferenceArray<T, len, reference::ReferenceCategory::Borrow, C>;

        template<
            typename T,
            usize len,
            template<typename T, usize l> class C = std::array
        >
        using UniqueBorrowArray = reference_array::StaticReferenceArray<T, len, reference::ReferenceCategory::UniqueBorrow, C>;

        template<
            typename T,
            reference::ReferenceCategory cat = reference::ReferenceCategory::Reference,
            template<typename T> class C = std::vector
        >
        using DynRefArray = reference_array::DynamicReferenceArray<T, cat, C>;

        template<
            typename T,
            template<typename T> class C = std::vector
        >
        using DynBorrowArray = reference_array::DynamicReferenceArray<T, reference::ReferenceCategory::Borrow, C>;

        template<
            typename T,
            template<typename T> class C = std::vector
        >
        using DynUniqueBorrowArray = reference_array::DynamicReferenceArray<T, reference::ReferenceCategory::UniqueBorrow, C>;
    };
};
