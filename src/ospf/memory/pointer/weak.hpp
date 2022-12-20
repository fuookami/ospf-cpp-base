#pragma once

#include <ospf/memory/pointer/shared.hpp>

namespace ospf
{
    inline namespace memory
    {
        namespace pointer
        {
            template<typename T>
            class Ptr<T, pointer::PointerCategory::Weak>
                : public pointer::PtrImpl<T, Ptr<T, pointer::PointerCategory::Weak>>
            {
                template<typename T, pointer::PointerCategory>
                friend class Ptr;

                template<typename T, reference::ReferenceCategory>
                friend class Ref;

            private:
                using Self = Ptr<T, PointerCategory::Weak>;
                using Impl = PtrImpl<T, Self>;

            public:
                using typename Impl::PtrType;
                using typename Impl::CPtrType;
                using typename Impl::RefType;
                using typename Impl::CRefType;
                using typename Impl::DeleterType;
                using typename Impl::DefaultDeleterType;
                using WeakPtrType = std::weak_ptr<T>;

            OSPF_CRTP_PERMISSION:
                inline const PtrType OSPF_CRTP_FUNCTION(get_ptr)(void) noexcept
                {
                    return _ptr.lock().get();
                }

                inline const CPtrType OSPF_CRTP_FUNCTION(get_cptr)(void) const noexcept
                {
                    return const_cast<CPtrType>(_ptr.lock().get());
                }

            private:
                WeakPtrType _ptr;
            };
        };
    };
};
