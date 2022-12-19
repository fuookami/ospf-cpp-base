#pragma once

#include <ospf/memory/pointer/impl.hpp>
#include <ospf/memory/pointer/category.hpp>
#include <memory>

#if defined(_DEBUG) && defined(OSPF_UNIQUE_PTR_CHECK)
#ifndef OSPF_UNIQUE_PTR_CHECK_NEEDED
#define OSPF_UNIQUE_PTR_CHECK_NEEDED
#endif
#endif

namespace ospf
{
    inline namespace memory
    {
        namespace pointer
        {
#ifdef OSPF_UNIQUE_PTR_CHECK_NEEDED
            class UniquePtrLocker
            {
            };
#endif

            template<typename T>
            class Ptr<T, PointerCategory::Unique>
                : public PtrImpl<T, Ptr<T, PointerCategory::Unique>>
            {
            private:
                using Self = Ptr<T, PointerCategory::Raw>;
                using Impl = PtrImpl<T, Self>;

            public:
                using typename Impl::PtrType;
                using typename Impl::CPtrType;
                using typename Impl::RefType;
                using typename Impl::CRefType;
                using typename Impl::DeleterType;
                using typename Impl::DefaultDeleterType;
                using UniquePtrType = std::unique_ptr<T, DeleterType>;

            private:
#ifdef OSPF_UNIQUE_PTR_CHECK_NEEDED
                volatile mutable bool _locked;
#endif
                UniquePtrType _ptr;
            };
        };
    };
};
