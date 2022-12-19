#pragma once

#include <ospf/type_family.hpp>
#include <ospf/meta_programming/crtp.hpp>

namespace ospf
{
    inline namespace memory
    {
        namespace pointer
        {
            template<typename T, typename Self>
            class PtrImpl
            {
                OSPF_CRTP_IMPL

            public:
                using PtrType = PtrType<T>;
                using CPtrType = CPtrType<T>;
                using RefType = LRefType<T>;
                using CRefType = CLRefType<T>;

                using DeleterType = std::function<void(T*)>;
                using DefaultDeleterType = std::default_delete<T>;

            protected:
                PtrImpl(void) = default;
            public:
                PtrImpl(const PtrImpl& ano) = default;
                PtrImpl(PtrImpl&& ano) noexcept = default;
                PtrImpl& operator=(const PtrImpl& rhs) = default;
                PtrImpl& operator=(PtrImpl&& rhs) noexcept = default;
                ~PtrImpl(void) noexcept = default;

            public:
                inline const bool null(void) const noexcept
                {
                    return get_cptr() == nullptr;
                }

                inline const bool operator!(void) const noexcept
                {
                    return null();
                }

                inline operator const bool(void) const noexcept
                {
                    return !null();
                }

            public:
                inline const bool operator==(const std::nullptr_t _) const noexcept
                {
                    return get_cptr() == nullptr;
                }

                inline const bool operator!=(const std::nullptr_t _) const noexcept
                {
                    return get_cptr() != nullptr;
                }

            public:
                template<typename U, typename P>
                inline const bool operator==(const PtrImpl<U, P>& ptr) const noexcept
                {
                    return get_cptr() == ptr.get_cptr();
                }

                template<typename U, typename P>
                inline const bool operator!=(const PtrImpl<U, P>& ptr) const noexcept
                {
                    return get_cptr() != ptr.get_cptr();
                }

                template<typename U, typename P>
                inline const bool operator<(const PtrImpl<U, P>& ptr) const noexcept
                {
                    return get_cptr() < ptr.get_cptr();
                }

                template<typename U, typename P>
                inline const bool operator<=(const PtrImpl<U, P>& ptr) const noexcept
                {
                    return get_cptr() <= ptr.get_cptr();
                }

                template<typename U, typename P>
                inline const bool operator>(const PtrImpl<U, P>& ptr) const noexcept
                {
                    return get_cptr() > ptr.get_cptr();
                }

                template<typename U, typename P>
                inline const bool operator>=(const PtrImpl<U, P>& ptr) const noexcept
                {
                    return get_cptr() >= ptr.get_cptr();
                }

            public:
                inline const PtrType operator->(void) noexcept
                {
                    return get_ptr();
                }

                inline const CPtrType operator->(void) const noexcept
                {
                    return get_cptr();
                }

                inline RefType operator*(void)
                {
                    assert(!null());
                    return *get_ptr();
                }

                inline CRefType operator*(void) const
                {
                    assert(!null());
                    return *get_cptr();
                }

            public:
                inline operator const PtrType(void) noexcept
                {
                    return get_ptr();
                }

                inline operator const CPtrType(void) const noexcept
                {
                    return get_cptr();
                }

                inline operator const ptraddr(void) const noexcept
                {
                    return reinterpret_cast<ptraddr>(get_cptr());
                }

            protected:
                inline const PtrType get_ptr(void) noexcept
                {
                    return Trait::get_ptr(self());
                }

                inline const CPtrType get_cptr(void) const noexcept
                {
                    return Trait::get_cptr(self());
                }

            private:
                struct Trait : public Self
                {
                    inline static const PtrType get_ptr(Self& self) noexcept
                    {
                        static const auto impl = OSPF_CRTP_FUNCTION(get_ptr);
                        return (self.*impl)();
                    }

                    inline static const CPtrType get_cptr(const Self& self) noexcept
                    {
                        static const auto impl = OSPF_CRTP_FUNCTION(get_cptr);
                        return (self.*impl)();
                    }
                };
            };

            template<typename T, typename Ptr>
            class PtrImpl<T[], Ptr>
                : public PtrImpl<T, Ptr>
            {
            public:
                using typename PtrImpl<T, Ptr>::PtrType;
                using typename PtrImpl<T, Ptr>::CPtrType;
                using typename PtrImpl<T, Ptr>::RefType;
                using typename PtrImpl<T, Ptr>::CRefType;
                using DeleterType = std::function<void(T*)>;
                using DefaultDeleterType = std::default_delete<T[]>;

            protected:
                PtrImpl(void) = default;
            public:
                PtrImpl(const PtrImpl& ano) = default;
                PtrImpl(PtrImpl&& ano) noexcept = default;
                PtrImpl& operator=(const PtrImpl& rhs) = default;
                PtrImpl& operator=(PtrImpl&& rhs) noexcept = default;
                ~PtrImpl(void) noexcept = default;

            public:
                inline CRefType operator[](const usize i) const
                {
                    return this->get_cptr()[i];
                }
            };
        };
    };
};

namespace std
{
    template<typename T, typename Ptr>
    struct hash<ospf::memory::pointer::PtrImpl<T, Ptr>>
    {
        using PtrType = ospf::memory::pointer::PtrImpl<T, Ptr>;

        inline const ospf::usize operator()(const PtrType& ptr) const noexcept
        {
            static const auto func = hash<typename PtrType::CPtrType>();
            return func(reinterpret_cast<typename PtrType::CPtrType>(static_cast<ospf::ptraddr>(ptr)));
        }
    };
};
