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

            class UniquePtrLockImpl
            {
                friend class UniquePtrLocker;

            protected:
                UniquePtrLockImpl(void)
                    : m_locked(false) {}
            public:
                UniquePtrLockImpl(const UniquePtrLockImpl& ano) = delete;
                UniquePtrLockImpl(UniquePtrLockImpl&& ano)
                    : m_locked(false)
                {
                    if (m_locked || ano.m_locked)
                    {
                        throw OSPFException{ { OPFErrCode::UniqueBoxLocked } };
                    }
                    std::swap(m_locked, ano.m_locked);
                }
                UniquePtrLockImpl& operator=(const UniquePtrLockImpl& rhs) = delete;
                UniquePtrLockImpl& operator=(UniquePtrLockImpl&& rhs)
                {
                    swap(rhs);
                    return *this;
                }
                ~UniquePtrLockImpl(void)
                {
                    assert(!m_locked);
                }

            public:
                inline void swap(UniquePtrLockImpl& ano)
                {
                    if (m_locked || ano.m_locked)
                    {
                        throw OSPFException{ { OPFErrCode::UniqueBoxLocked } };
                    }
                    std::swap(m_locked, ano.m_locked);
                }

            private:
                volatile mutable bool m_locked;
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

            public:
                Ptr(void)
                    : _ptr(nullptr) {}
                Ptr(std::nullptr_t _)
                    : _ptr(nullptr) {}
                Ptr(UniquePtrType&& ptr)
                    : _ptr(move<UniquePtrType>(ptr)) {}


            private:
#ifdef OSPF_UNIQUE_PTR_CHECK_NEEDED
                UniquePtrLockImpl _lock_impl;
#endif
                UniquePtrType _ptr;
            };
        };

        template<typename T, typename... Args>
        inline decltype(auto) make_unique(Args&&... args)
        {
            return pointer::Ptr<T, pointer::PointerCategory::Unique>{ new T{ std::forward<Args>(args)... } };
        }

        template<typename T, typename U, typename... Args>
            requires std::is_convertible_v<PtrType<U>, PtrType<T>>
        inline decltype(auto) make_base_unique(Args&&... args)
        {
            return pointer::Ptr<T, pointer::PointerCategory::Unique>{ static_cast<T*>(new U{ std::forward<Args>(args)... }) };
        }
    };
};
