#pragma once

#include <ospf/functional/value_or_reference.hpp>
#include <ospf/memory/pointer.hpp>

namespace ospf
{
    inline namespace functional
    {
        template<
            typename T,
            pointer::PointerCategory pcat = pointer::PointerCategory::Shared,
            reference::ReferenceCategory rcat = reference::ReferenceCategory::Reference
        >
        class PtrOrRef
        {
        public:
            using ValueType = OriginType<T>;
            using PointerType = pointer::Ptr<ValueType, pcat>;
            using ReferenceType = reference::Ref<ValueType, rcat>;
            using PtrType = PtrType<ValueType>;
            using CPtrType = CPtrType<ValueType>;
            using RefType = LRefType<ValueType>;
            using CRefType = CLRefType<ValueType>;

        private:
            using Either = functional::Either<PointerType, ReferenceType>;

        public:
            template<typename = void>
                requires std::copyable<PointerType>
            inline static constexpr PtrOrRef ptr(ArgCLRefType<PointerType> ptr)
            {
                return PtrOrRef{ ptr };
            }

            template<typename = void>
                requires ReferenceFaster<PointerType> && std::movable<PointerType>
            inline static constexpr PtrOrRef ptr(ArgRRefType<PointerType> ptr)
            {
                return PtrOrRef{ move<PointerType>(ptr) };
            }

            inline static constexpr PtrOrRef ref(CLRefType<ValueType> ref) noexcept
            {
                return PtrOrRef{ ReferenceType{ ref } };
            }

            template<typename = void>
                requires std::copyable<ReferenceType>
            inline static constexpr PtrOrRef ref(ArgCLRefType<ReferenceType> ref) noexcept
            {
                return PtrOrRef{ ref };
            }

            template<typename = void>
                requires ReferenceFaster<ReferenceType>&& std::movable<ReferenceType>
            inline static constexpr PtrOrRef ref(ArgRRefType<ReferenceType> ref) noexcept
            {
                return PtrOrRef{ move<ReferenceType>(ref) };
            }

        public:
            constexpr PtrOrRef(const std::nullptr_t) = delete;

            template<typename = void>
                requires std::copyable<PointerType>
            constexpr PtrOrRef(ArgCLRefType<PointerType> ptr)
                : _either(Either::left(ptr))
            {
                if (_either.left() == nullptr)
                {
                    throw OSPFException{ OSPFErrCode::ApplicationError, "invalid argument nullptr for PtrOrRef" };
                }
            }

            template<typename = void>
                requires ReferenceFaster<PointerType> && std::movable<PointerType>
            constexpr PtrOrRef(ArgRRefType<PointerType> ptr)
                : _either(Either::left(move<PointerType>(ptr)))
            {
                if (_either.left() == nullptr)
                {
                    throw OSPFException{ OSPFErrCode::ApplicationError, "invalid argument nullptr for PtrOrRef" };
                }
            }

        private:
            constexpr PtrOrRef(ArgCLRefType<ReferenceType> ref)
                : _either(Either::right(ref)) {}

            template<typename = void>
                requires ReferenceFaster<ReferenceType> && std::movable<ReferenceType>
            constexpr PtrOrRef(ArgRRefType<ReferenceType> ref)
                : _either(Either::right(move<ReferenceType>(ref))) {}

        public:
            constexpr PtrOrRef(const PtrOrRef& ano) = default;
            constexpr PtrOrRef(PtrOrRef&& ano) noexcept = default;
            constexpr PtrOrRef& operator=(const PtrOrRef& rhs) = default;
            constexpr PtrOrRef& operator=(PtrOrRef&& rhs) noexcept = default;
            constexpr ~PtrOrRef(void) noexcept = default;

        public:
            inline constexpr const bool is_ptr(void) const noexcept
            {
                return _either.is_left();
            }

            inline constexpr const bool is_reference(void) const noexcept
            {
                return _either.is_right();
            }

        public:
            inline constexpr const PtrType operator->(void) noexcept
            {
                return &deref();
            }

            inline constexpr const CPtrType operator->(void) const noexcept
            {
                return &deref();
            }

            inline constexpr RefType operator*(void) noexcept
            {
                return deref();
            }
            
            inline constexpr CRefType operator*(void) const noexcept
            {
                return deref();
            }

        public:
            template<typename U, pointer::PointerCategory pc, reference::ReferenceCategory rc>
            inline constexpr const bool operator==(const PtrOrRef<U, pc, rc>& rhs) const noexcept
            {
                return &deref() == &*rhs || deref() == *rhs;
            }

            template<typename U, pointer::PointerCategory pc, reference::ReferenceCategory rc>
            inline constexpr const bool operator!=(const PtrOrRef<U, pc, rc>& rhs) const noexcept
            {
                return &deref() != &*rhs && deref() != *rhs;
            }

            template<typename U, reference::ReferenceCategory c, CopyOnWrite cw>
            inline constexpr const bool operator==(const ValOrRef<U, c, cw>& rhs) const noexcept
            {
                return &deref() == &*rhs || deref() == *rhs;
            }

            template<typename U, reference::ReferenceCategory c, CopyOnWrite cw>
            inline constexpr const bool operator!=(const ValOrRef<U, c, cw>& rhs) const noexcept
            {
                return &deref() != &*rhs && deref() != *rhs;
            }

            template<typename U, pointer::PointerCategory c>
            inline constexpr const bool operator==(const pointer::Ptr<U, c>& rhs) const noexcept
            {
                return rhs != nullptr && (&deref() == &*rhs || deref() == *rhs);
            }

            template<typename U, pointer::PointerCategory c>
            inline constexpr const bool operator!=(const pointer::Ptr<U, c>& rhs) const noexcept
            {
                return rhs == nullptr || (&deref() != &*rhs && deref() != *rhs);
            }

            template<typename U, reference::ReferenceCategory c>
            inline constexpr const bool operator==(const reference::Ref<U, c>& rhs) const noexcept
            {
                return &deref() == &*rhs || deref() == *rhs;
            }

            template<typename U, reference::ReferenceCategory c>
            inline constexpr const bool operator!=(const reference::Ref<U, c>& rhs) const noexcept
            {
                return &deref() != &*rhs && deref() != *rhs;
            }

            template<typename U>
            inline constexpr const bool operator==(const U& rhs) const noexcept
            {
                return &deref() == &rhs || deref() == rhs;
            }

            template<typename U>
            inline constexpr const bool operator!=(const U& rhs) const noexcept
            {
                return &deref() != &rhs && deref() != rhs;
            }

            template<typename U>
            inline constexpr const bool operator==(const std::optional<U>& rhs) const noexcept
            {
                return static_cast<bool>(rhs) && (&deref() == &*rhs || deref() == *rhs);
            }

            template<typename U>
            inline constexpr const bool operator!=(const std::optional<U>& rhs) const noexcept
            {
                return !static_cast<bool>(rhs) && (&deref() != &*rhs && deref() != *rhs);
            }

        public:
            // operator<, operator>, operator<=, operator>=
            template<typename U, pointer::PointerCategory pc, reference::ReferenceCategory rc>
            inline constexpr const bool operator<(const PtrOrRef<U, pc, rc>& rhs) const noexcept
            {

            }

        public:
            template<typename U, pointer::PointerCategory pc, reference::ReferenceCategory rc>
            inline constexpr decltype(auto) operator<=>(const PtrOrRef<U, pc, rc>& rhs) const noexcept
            {
                return deref() <=> *rhs;
            }

            template<typename U, reference::ReferenceCategory rc, CopyOnWrite cw>
            inline constexpr decltype(auto) operator<=>(const ValOrRef<U, rc, cw>& rhs) const noexcept
            {
                return deref() <=> *rhs;
            }

            template<typename U, pointer::PointerCategory c>
            inline constexpr ospf::RetType<std::compare_three_way_result_t<T, U>> operator<=>(const pointer::Ptr<U, c>& rhs) const noexcept
            {
                if (rhs != nullptr)
                {
                    return deref() <=> *rhs;
                }
                else
                {
                    return true <=> static_cast<bool>(rhs);
                }
            }

            template<typename U, reference::ReferenceCategory c>
            inline constexpr decltype(auto) operator<=>(const reference::Ref<U, c>& rhs) const noexcept
            {
                return deref() <=> *rhs;
            }

            template<typename U>
            inline constexpr decltype(auto) operator<=>(const U& rhs) const noexcept
            {
                return deref() <=> rhs;
            }

            template<typename U>
            inline constexpr ospf::RetType<std::compare_three_way_result_t<T, U>> operator<=>(const std::optional<U>& rhs) const noexcept
            {
                if (static_cast<bool>(rhs))
                {
                    return deref() <=> *rhs;
                }
                else
                {
                    return true <=> static_cast<bool>(rhs);
                }
            }

        private:
            inline constexpr RefType deref(void) noexcept
            {
                return const_cast<RefType>(const_cast<const PtrOrRef&>(*this).deref());
            }

            inline constexpr CRefType deref(void) const noexcept
            {
                return std::visit([](const auto& arg)
                    {
                        using ThisType = OriginType<decltype(arg)>;
                        if constexpr (DecaySameAs<ThisType, PointerType>)
                        {
                            return *arg;
                        }
                        else if constexpr (DecaySameAs<ThisType, ReferenceType>)
                        {
                            return *arg;
                        }
                    }, _either);
            }

        private:
            Either _either;
        };


        template<
            typename T,
            reference::ReferenceCategory cat = reference::ReferenceCategory::Reference
        >
        using UniqueOrRef = PtrOrRef<T, pointer::PointerCategory::Unique, cat>;

        template<
            typename T,
            reference::ReferenceCategory cat = reference::ReferenceCategory::Reference
        >
        using SharedOrRef = PtrOrRef<T, pointer::PointerCategory::Shared, cat>;
    };
};

// operator==, operator!=
// operator<, operator<=, operator>, operator>=
// operator<=>

// hash
// format

// with_tag
