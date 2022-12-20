#pragma once

#include <ospf/memory/pointer/impl.hpp>
#include <ospf/memory/pointer/category.hpp>
#include <ospf/memory/pointer/unique.hpp>
#include <ospf/memory/pointer/shared.hpp>
#include <ospf/memory/pointer/weak.hpp>
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
                Ptr(void) noexcept
                    : _from(PointerCategory::Raw), _ptr(nullptr) {}

                Ptr(std::nullptr_t _) noexcept
                    : _from(PointerCategory::Raw), _ptr(nullptr) {}

                Ptr(const PtrType ptr) noexcept
                    : _from(PointerCategory::Raw), _ptr(ptr) {}

                Ptr(const CPtrType cptr) noexcept
                    : _from(PointerCategory::Raw), _ptr(const_cast<PtrType>(cptr)) {}

                Ptr(RefType ref) noexcept
                    : _from(PointerCategory::Raw), _ptr(&ref) {}

                Ptr(CRefType cref) noexcept
                    : _from(PointerCategory::Raw), _ptr(const_cast<PtrType>(&cref)) {}

            public:
                template<typename U>
                    requires std::is_convertible_v<ospf::PtrType<U>, PtrType>
                explicit Ptr(const ospf::PtrType<U> ptr) noexcept
                    : Ptr(static_cast<PtrType>(ptr)) {}

                template<typename U>
                    requires std::is_convertible_v<ospf::CPtrType<U>, CPtrType>
                explicit Ptr(const ospf::CPtrType<U> ptr) noexcept
                    : Ptr(static_cast<CPtrType>(ptr)) {}

                template<typename U>
                    requires std::is_convertible_v<ospf::PtrType<U>, PtrType>
                explicit Ptr(ospf::LRefType<U> ref) noexcept
                    : Ptr(static_cast<PtrType>(&ref)) {}

                template<typename U>
                    requires std::is_convertible_v<ospf::CPtrType<U>, CPtrType>
                explicit Ptr(ospf::CLRefType<U> cref) noexcept
                    : Ptr(static_cast<CPtrType>(&cref)) {}

            public:
                explicit Ptr(const std::unique_ptr<T>& ptr) noexcept
                    : _from(PointerCategory::Unique), _ptr(ptr.get()) {}

                explicit Ptr(const std::shared_ptr<T>& ptr) noexcept
                    : _from(PointerCategory::Shared), _ptr(ptr.get()) {}

                explicit Ptr(const std::weak_ptr<T> ptr) noexcept
                    : _from(PointerCategory::Weak), _ptr(ptr.lock().get()) {}

            public:
                template<typename U>
                    requires std::is_convertible_v<ospf::PtrType<U>, PtrType>
                explicit Ptr(const std::unique_ptr<U>& ptr) noexcept
                    : _from(PointerCategory::Unique), _ptr(static_cast<PtrType>(ptr.get())) {}

                template<typename U>
                    requires std::is_convertible_v<ospf::PtrType<U>, PtrType>
                explicit Ptr(const std::shared_ptr<U>& ptr) noexcept
                    : _from(PointerCategory::Shared), _ptr(static_cast<PtrType>(ptr.get())) {}

                template<typename U>
                    requires std::is_convertible_v<ospf::PtrType<U>, PtrType>
                explicit Ptr(const std::weak_ptr<U> ptr) noexcept
                    : _from(PointerCategory::Weak), _ptr(static_cast<PtrType>(ptr.lock().get())) {}

            public:
                explicit Ptr(const Ptr<T, PointerCategory::Unique>& ptr)
                    : _from(PointerCategory::Unique), _ptr(ptr._ptr.get()) 
                {
#ifdef OSPF_UNIQUE_PTR_CHECK_NEEDED
                    _locker = std::make_unique<UniquePtrLocker>{ ptr };
#endif
                }

                template<typename U>
                    requires std::is_convertible_v<ospf::PtrType<U>, PtrType>
                explicit Ptr(const Ptr<U, PointerCategory::Unique>& ptr)
                    : _from(PointerCategory::Unique), _ptr(static_cast<PtrType>(ptr._ptr.get()))
                {
#ifdef OSPF_UNIQUE_PTR_CHECK_NEEDED
                    _locker = std::make_unique<UniquePtrLocker>{ ptr };
#endif
                }

            public:
                explicit Ptr(const Ptr<T, PointerCategory::Shared>& ptr) noexcept
                    : _from(PointerCategory::Shared), _ptr(ptr._ptr.get()) {}

                template<typename U>
                    requires std::is_convertible_v<ospf::PtrType<U>, PtrType>
                explicit Ptr(const Ptr<U, PointerCategory::Shared>& ptr) noexcept
                    : _from(PointerCategory::Shared), _ptr(static_cast<PtrType>(ptr._ptr.get())) {}

            public:
                explicit Ptr(const Ptr<T, PointerCategory::Weak> ptr) noexcept
                    : _from(PointerCategory::Weak), _ptr(ptr._ptr.lock().get()) {}

                template<typename U>
                    requires std::is_convertible_v<ospf::PtrType<U>, PtrType>
                explicit Ptr(const Ptr<U, PointerCategory::Weak> ptr) noexcept
                    : _from(PointerCategory::Weak), _ptr(static_cast<PtrType>(ptr._ptr.lock().get())) {}

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
                inline void reset(const std::nullptr_t _ = nullptr) noexcept
                {
                    _from = PointerCategory::Raw;
                    _ptr = nullptr;
#ifdef OSPF_UNIQUE_PTR_CHECK_NEEDED
                    _locker.reset();
#endif
                }

                // todo: impl reset functions

                inline void swap(Ptr<T, PointerCategory::Raw>& ano)
                {
                    std::swap(_from, ano._from);
                    std::swap(_ptr, ano._ptr);
#ifdef OSPF_UNIQUE_PTR_CHECK_NEEDED
                    std::swap(_locker, anp._locker);
#endif
                }

            OSPF_CRTP_PERMISSION:
                inline const PtrType OSPF_CRTP_FUNCTION(get_ptr)(void) noexcept
                {
                    return _ptr;
                }

                inline const CPtrType OSPF_CRTP_FUNCTION(get_cptr)(void) const noexcept
                {
                    return const_cast<CPtrType>(_ptr);
                }

            private:
                PointerCategory _from;
                PtrType _ptr;
#ifdef OSPF_UNIQUE_PTR_CHECK_NEEDED
                std::unique<UniquePtrLocker> _locker;
#endif
            };
        };
    };
};
