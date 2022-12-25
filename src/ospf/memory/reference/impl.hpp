#pragma once

#include <ospf/type_family.hpp>
#include <ospf/concepts/with_tag.hpp>
#include <ospf/meta_programming/crtp.hpp>

namespace ospf
{
    inline namespace memory
    {
        namespace reference
        {
            template<typename T, typename Self>
            class RefImpl
            {
                OSPF_CRTP_IMPL

            public:
                using PtrType = PtrType<T>;
                using CPtrType = CPtrType<T>;
                using RefType = LRefType<T>;
                using CRefType = CLRefType<T>;

            protected:
                RefImpl(void) noexcept = default;
            public:
                RefImpl(const RefImpl& ano) = default;
                RefImpl(RefImpl&& ano) noexcept = default;
                RefImpl& operator=(const RefImpl& rhs) = default;
                RefImpl& operator=(RefImpl&& rhs) noexcept = default;
                ~RefImpl(void) noexcept = default;

            public:
                inline const PtrType operator->(void) noexcept
                {
                    return ptr();
                }

                inline const CPtrType operator->(void) const noexcept
                {
                    return cptr();
                }

                inline RefType operator*(void) noexcept
                {
                    return ref();
                }

                inline CRefType operator*(void) const noexcept
                {
                    return cref();
                }

            public:
                inline operator RefType(void) noexcept
                {
                    return ref();
                }

                inline operator CRefType(void) const noexcept
                {
                    return cref();
                }

            protected:
                inline RefType ref(void) noexcept
                {
                    return Trait::get_ref(self());
                }

                inline CRefType cref(void) const noexcept
                {
                    return Trait::get_cref(self());
                }

            private:
                struct Trait : public Self
                {
                    inline static RefType get_ref(Self& self) noexcept
                    {
                        static const auto get_impl = &Self::OSPF_CRTP_FUNCTION(get_ref);
                        return (self.*get_impl)();
                    }

                    inline static CRefType get_cref(const Self& self) noexcept
                    {
                        static const auto get_impl = &Self::OSPF_CRTP_FUNCTION(get_cref);
                        return (self.*get_impl)();
                    }
                };
            };
        };
    };
};

namespace std
{
    template<typename T, typename Ref>
    struct hash<ospf::memory::reference::RefImpl<T, Ref>>
    {
        using RefType = ospf::memory::reference::RefImpl<T, Ref>;

        inline const ospf::usize operator()(const RefType& ref) const noexcept
        {
            static const auto func = hash<T>{};
            return func(*ref);
        }
    };
};

template<typename T, typename Ref>
    requires ospf::WithTag<T>
struct ospf::TagValue<ospf::memory::reference::RefImpl<T, Ref>>
{
    using Type = typename TagValue<T>::Type;
    using RefType = typename memory::reference::RefImpl<T, Ref>;

    inline decltype(auto) value(const RefType& ref) const noexcept
    {
        static constexpr const auto extractor = TagValue<T>{};
        return extractor(*ref);
    }
};