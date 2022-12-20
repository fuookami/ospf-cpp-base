#pragma once

#include <ospf/memory/pointer/impl.hpp>
#include <ospf/memory/pointer/category.hpp>
#include <ospf/memory/reference/category.hpp>

namespace ospf
{
    inline namespace memory
    {
        namespace pointer
        {
            template<typename T>
            class Ptr<T, PointerCategory::Raw>
                : public PtrImpl<T, Ptr<T, PointerCategory::Raw>>
            {
                template<typename U, reference::ReferenceCategory category>
                friend class Ref;

            private:
                using Self = Ptr<T, PointerCategory::Raw>;
                using Impl = PtrImpl<T, Self>;

            public:
                using typename Impl::PtrType;
                using typename Impl::CPtrType;
                using typename Impl::RefType;
                using typename Impl::CRefType;

            public:
                Ptr(void)
                    : _from(PointerCategory::Raw), _ptr(nullptr) {}
                Ptr(std::nullptr_t _)
                    : _from(PointerCategory::Raw), _ptr(nullptr) {}
                Ptr(const PtrType ptr)
                    : _from(PointerCategory::Raw), _ptr(ptr) {}
                Ptr(const CPtrType cptr)
                    : _from(PointerCategory::Raw), _ptr(const_cast<PtrType>(cptr)) {}
                Ptr(RefType ref)
                    : _from(PointerCategory::Raw), _ptr(&ref) {}
                Ptr(CRefType cref)
                    : _from(PointerCategory::Raw), _ptr(const_cast<PtrType>(&cref)) {}
            public:
                template<typename U>
                    requires std::is_convertible_v<ospf::PtrType<U>, PtrType>
                explicit Ptr(const ospf::PtrType<U> ptr)
                    : Ptr(static_cast<PtrType>(ptr)) {}
                template<typename U>
                    requires std::is_convertible_v<ospf::CPtrType<U>, CPtrType>
                explicit Ptr(const ospf::CPtrType<U> ptr)
                    : Ptr(static_cast<CPtrType>(ptr)) {}
                template<typename U>
                    requires std::is_convertible_v<ospf::PtrType<U>, PtrType>
                explicit Ptr(ospf::LRefType<U> ref)
                    : Ptr(static_cast<PtrType>(&ref)) {}
                template<typename U>
                    requires std::is_convertible_v<ospf::CPtrType<U>, CPtrType>
                explicit Ptr(ospf::CLRefType<U> cref)
                    : Ptr(static_cast<CPtrType>(&cref)) {}

            public:
                //todo: constructor for unique pointer

            public:
                //todo: constructor for shared pointer

            public:
                //todo: constructor for weak pointer

            public:
                Ptr(const Ptr& ano) = default;
                Ptr(Ptr&& ano) noexcept = default;
                Ptr& operator=(const Ptr& rhs) = default;
                Ptr& operator=(Ptr&& rhs) noexcept = default;
                ~Ptr(void) noexcept = default;

            public:
                inline const PointerCategory from(void) const noexcept
                {
                    return _from;
                }

            public:
                inline void swap(Ptr<T, PointerCategory::Raw>& ano)
                {
                    std::swap(_from, ano._from);
                    std::swap(_ptr, ano._ptr);
                }

            OSPF_CRTP_PERMISSION:
                inline const PtrType OSPF_CRTP_FUNCTION(get_ptr)(void) noexcept
                {
                    return _ptr;
                }

                inline const CPtrType OSPF_CRTP_FUNCTION(get_cptr)(void) const noexcept
                {
                    return _ptr;
                }

            private:
                PointerCategory _from;
                PtrType _ptr;
            };
        };
    };
};
