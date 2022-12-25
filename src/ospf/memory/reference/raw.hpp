#pragma once

#include <ospf/memory/pointer.hpp>
#include <ospf/memory/reference/borrow.hpp>

namespace ospf
{
    inline namespace memory
    {
        namespace reference
        {
            template<typename T>
            class Ref<T, ReferenceCategory::Reference>
                : public RefImpl<T, Ref<T, ReferenceCategory::Reference>>
            {
            private:
                using Self = Ref<T, ReferenceCategory::Reference>;
                using Impl = RefImpl<T, Self>;

            public:
                using typename Impl::PtrType;
                using typename Impl::CPtrType;
                using typename Impl::RefType;
                using typename Impl::CRefType;

            public:
                Ref(CRefType cref) noexcept
                    : _ptr(cref) {}

            public:
                Ref(const Ref& ano) = default;
                Ref(Ref&& ano) noexcept = default;
                Ref& operator=(const Ref& rhs) = default;
                Ref& operator=(Ref&& rhs) noexcept = default;
                ~Ref(void) noexcept = default;

            OSPF_CRTP_PERMISSION:
                inline RefType OSPF_CRTP_FUNCTION(get_ref)(void) noexcept
                {
                    return *_ptr;
                }

                inline CRefType OSPF_CRTP_FUNCTION(get_cref)(void) const noexcept
                {
                    return *_ptr;
                }

            private:
                Ptr<T> _ptr;
            };
        };
    };
};