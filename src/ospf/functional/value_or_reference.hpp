#pragma once

#include <ospf/functional/either.hpp>
#include <ospf/memory/reference.hpp>

namespace ospf
{
    inline namespace functional
    {
        template<typename T, reference::ReferenceCategory cat = reference::ReferenceCategory::Reference>
        class ValOrRef
        {
        public:
            using ValueType = OriginType<T>;
            using ReferenceType = reference::Ref<ValueType, cat>;
            using PtrType = PtrType<ValueType>;
            using CPtrType = CPtrType<ValueType>;
            using RefType = LRefType<ValueType>;
            using CRefType = CLRefType<ValueType>;

        private:
            using EitherType = Either<ValueType, ReferenceType>;

        public:
            inline static constexpr RetType<ValOrRef> value(ArgCLRefType<ValueType> val) noexcept
            {
                return ValOrRef{ val };
            }

            template<typename = void>
                requires ReferenceFaster<ValueType> && std::movable<ValueType>
            inline static constexpr RetType<ValOrRef> value(ArgRRefType<ValueType> val) noexcept
            {
                return ValOrRef{ move<ValueType>(val) };
            }

            template<typename... Args>
                requires std::constructible_from<ValueType, Args...>
            inline static constexpr RetType<ValOrRef> value(Args&&... args) noexcept
            {
                return ValOrRef{ ValueType{ std::forward<Args>(args)... }};
            }

            inline static constexpr RetType<ValOrRef> ref(CLRefType<ValueType> ref) noexcept
            {
                return ValOrRef{ ReferenceType{ ref } };
            }

            inline static constexpr RetType<ValOrRef> ref(ArgRRefType<ReferenceType> ref) noexcept
            {
                return ValOrRef{ move<ReferenceType>(ref) };
            }

        public:
            template<typename = void>
                requires WithDefault<ValueType>
            constexpr ValOrRef(void)
                : _either(EitherType::left(DefaultValue<ValueType>::value)) {}

        private:
            constexpr ValOrRef(ArgCLRefType<ValueType> value)
                : _either(EitherType::left(value)) {}

            template<typename = void>
                requires ReferenceFaster<ValueType> && std::movable<ValueType>
            constexpr ValOrRef(ArgRRefType<ValueType> value)
                : _either(EitherType::left(move<ValueType>(value))) {}

            constexpr ValOrRef(ArgRRefType<ReferenceType> ref)
                : _either(EitherType::right(move<ReferenceType>(ref))) {}

        public:
            constexpr ValOrRef(const ValOrRef& ano) = default;
            constexpr ValOrRef(ValOrRef&& ano) noexcept = default;
            constexpr ValOrRef& operator=(const ValOrRef& rhs) = default;
            constexpr ValOrRef& operator=(ValOrRef&& rhs) noexcept = default;
            constexpr ~ValOrRef(void) noexcept = default;

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
            inline constexpr operator RefType(void) noexcept
            {
                return deref();
            }

            inline constexpr operator CRefType(void) const noexcept
            {
                return deref();
            }

        public:
            template<typename U, reference::ReferenceCategory c>
            inline constexpr const bool operator==(const ValOrRef<U, c>& rhs) const noexcept
            {
                return deref() == *rhs;
            }

            template<typename U, reference::ReferenceCategory c>
            inline constexpr const bool operator!=(const ValOrRef<U, c>& rhs) const noexcept
            {
                return deref() != *rhs;
            }

            template<typename U, reference::ReferenceCategory c>
            inline constexpr const bool operator==(const reference::RefImpl<U, c>& rhs) const noexcept
            {
                return _value == *rhs;
            }

            template<typename U, reference::ReferenceCategory c>
            inline constexpr const bool operator!=(const reference::RefImpl<U, c>& rhs) const noexcept
            {
                return _value != *rhs;
            }

            template<typename U>
            inline constexpr const bool operator==(const U& rhs) const noexcept
            {
                return deref() == rhs;
            }

            template<typename U>
            inline constexpr const bool operator!=(const U& rhs) const noexcept
            {
                return deref() != rhs;
            }

        public:
            template<typename U, reference::ReferenceCategory c>
            inline constexpr const bool operator<(const ValOrRef<U, c>& rhs) const noexcept
            {
                return deref() < *rhs;
            }

            template<typename U, reference::ReferenceCategory c>
            inline constexpr const bool operator<=(const ValOrRef<U, c>& rhs) const noexcept
            {
                return deref() <= *rhs;
            }

            template<typename U, reference::ReferenceCategory c>
            inline constexpr const bool operator>(const ValOrRef<U, c>& rhs) const noexcept
            {
                return deref() > *rhs;
            }

            template<typename U, reference::ReferenceCategory c>
            inline constexpr const bool operator>=(const ValOrRef<U, c>& rhs) const noexcept
            {
                return deref() >= *rhs;
            }

            template<typename U, reference::ReferenceCategory c>
            inline constexpr const bool operator<(const reference::RefImpl<U, c>& rhs) const noexcept
            {
                return deref() < *rhs;
            }

            template<typename U, reference::ReferenceCategory c>
            inline constexpr const bool operator<=(const reference::RefImpl<U, c>& rhs) const noexcept
            {
                return deref() <= *rhs;
            }

            template<typename U, reference::ReferenceCategory c>
            inline constexpr const bool operator>(const reference::RefImpl<U, c>& rhs) const noexcept
            {
                return deref() > *rhs;
            }

            template<typename U, reference::ReferenceCategory c>
            inline constexpr const bool operator>=(const reference::RefImpl<U, c>& rhs) const noexcept
            {
                return deref() > *rhs;
            }

            template<typename U>
            inline constexpr const bool operator<(const U& rhs) const noexcept
            {
                return deref() < rhs;
            }

            template<typename U>
            inline constexpr const bool operator<=(const U& rhs) const noexcept
            {
                return deref() <= rhs;
            }

            template<typename U>
            inline constexpr const bool operator>(const U& rhs) const noexcept
            {
                return deref() > rhs;
            }

            template<typename U>
            inline constexpr const bool operator>=(const U& rhs) const noexcept
            {
                return deref() >= rhs;
            }

        public:
            template<typename U, reference::ReferenceCategory c>
            inline constexpr const bool operator<=>(const ValOrRef<U, c>& rhs) const noexcept
            {
                return deref() <=> *rhs;
            }

            template<typename U, reference::ReferenceCategory c>
            inline constexpr decltype(auto) operator<=>(const reference::RefImpl<U, c>& rhs) const noexcept
            {
                return deref() <=> *rhs;
            }

            template<typename U>
            inline constexpr const bool operator<=>(const U& rhs) const noexcept
            {
                return deref() <=> rhs;
            }

        private:
            inline constexpr RefType deref(void) noexcept
            {
                return const_cast<RefType>(const_cast<const ValOrRef&>(*this).deref());
            }

            inline constexpr CRefType deref(void) const noexcept
            {
                return visit([](const auto& arg)
                    {
                        using ThisType = OriginType<decltype(arg)>;
                        if constexpr (std::is_same_v<ThisType, ValueType>)
                        {
                            return arg;
                        }
                        else if constexpr (std::is_same_v<ThisType, ReferenceType>)
                        {
                            return *arg;
                        }
                        else
                        {
                            static_assert(false, "Non-exhaustive visitor!");
                        }
                    }, _either);
            }

        private:
            EitherType _either;
        };

        template<typename T, reference::ReferenceCategory cat>
            requires CopyFaster<T>
        class ValOrRef<T, cat>
        {
        public:
            using ValueType = OriginType<T>;
            using ReferenceType = reference::Ref<ValueType, cat>;
            using PtrType = PtrType<ValueType>;
            using CPtrType = CPtrType<ValueType>;
            using RefType = LRefType<ValueType>;
            using CRefType = CLRefType<ValueType>;

        public:
            inline static constexpr RetType<ValOrRef> value(ArgCLRefType<ValueType> val) noexcept
            {
                return ValOrRef{ val };
            }

            template<typename... Args>
                requires std::constructible_from<ValueType, Args...>
            inline static constexpr RetType<ValOrRef> value(Args&&... args) noexcept
            {
                return ValOrRef{ ValueType{ std::forward<Args>(args)... } };
            }

            inline static constexpr RetType<ValOrRef> ref(ArgCLRefType<ValueType> ref) noexcept
            {
                return ValOrRef{ ref };
            }

            inline static constexpr RetType<ValOrRef> ref(ArgCLRefType<ReferenceType> ref) noexcept
            {
                return ValOrRef{ ref };
            }

        public:
            template<typename = void>
                requires WithDefault<ValueType>
            constexpr ValOrRef(void)
                : _value(DefaultValue<ValueType>::value) {}

        private:
            constexpr ValOrRef(ArgCLRefType<ValueType> value)
                : _value(value) {}

        public:
            constexpr ValOrRef(const ValOrRef& ano) = default;
            constexpr ValOrRef(ValOrRef&& ano) noexcept = default;
            constexpr ValOrRef& operator=(const ValOrRef& rhs) = default;
            constexpr ValOrRef& operator=(ValOrRef&& rhs) noexcept = default;
            constexpr ~ValOrRef(void) = default;

        public:
            inline constexpr const PtrType operator->(void) noexcept
            {
                return &_value;
            }

            inline constexpr const CPtrType operator->(void) const noexcept
            {
                return &_value;
            }

            inline constexpr RefType operator*(void) noexcept
            {
                return _value;
            }

            inline constexpr CRefType operator*(void) const noexcept
            {
                return _value;
            }

        public:
            inline constexpr operator RefType(void) noexcept
            {
                return _value;
            }

            inline constexpr operator CRefType(void) const noexcept
            {
                return _value;
            }

        public:
            template<typename U, reference::ReferenceCategory c>
            inline constexpr const bool operator==(const ValOrRef<U, c>& rhs) const noexcept
            {
                return _value == *rhs;
            }

            template<typename U, reference::ReferenceCategory c>
            inline constexpr const bool operator!=(const ValOrRef<U, c>& rhs) const noexcept
            {
                return _value != *rhs;
            }

            template<typename U, reference::ReferenceCategory c>
            inline constexpr const bool operator==(const reference::RefImpl<U, c>& rhs) const noexcept
            {
                return _value == *rhs;
            }

            template<typename U, reference::ReferenceCategory c>
            inline constexpr const bool operator!=(const reference::RefImpl<U, c>& rhs) const noexcept
            {
                return _value != *rhs;
            }

            template<typename U>
            inline constexpr const bool operator==(const U& rhs) const noexcept
            {
                return _value == rhs;
            }

            template<typename U>
            inline constexpr const bool operator!=(const U& rhs) const noexcept
            {
                return _value != rhs;
            }

        public:
            template<typename U, reference::ReferenceCategory c>
            inline constexpr const bool operator<(const ValOrRef<U, c>& rhs) const noexcept
            {
                return _value < *rhs;
            }

            template<typename U, reference::ReferenceCategory c>
            inline constexpr const bool operator<=(const ValOrRef<U, c>& rhs) const noexcept
            {
                return _value <= *rhs;
            }

            template<typename U, reference::ReferenceCategory c>
            inline constexpr const bool operator>(const ValOrRef<U, c>& rhs) const noexcept
            {
                return _value > *rhs;
            }

            template<typename U, reference::ReferenceCategory c>
            inline constexpr const bool operator>=(const ValOrRef<U, c>& rhs) const noexcept
            {
                return _value > *rhs;
            }

            template<typename U, reference::ReferenceCategory c>
            inline constexpr const bool operator<(const reference::RefImpl<U, c>& rhs) const noexcept
            {
                return _value < *rhs;
            }

            template<typename U, reference::ReferenceCategory c>
            inline constexpr const bool operator<=(const reference::RefImpl<U, c>& rhs) const noexcept
            {
                return _value <= *rhs;
            }

            template<typename U, reference::ReferenceCategory c>
            inline constexpr const bool operator>(const reference::RefImpl<U, c>& rhs) const noexcept
            {
                return _value > *rhs;
            }

            template<typename U, reference::ReferenceCategory c>
            inline constexpr const bool operator>=(const reference::RefImpl<U, c>& rhs) const noexcept
            {
                return _value > *rhs;
            }

            template<typename U>
            inline constexpr const bool operator<(const U& rhs) const noexcept
            {
                return _value < rhs;
            }

            template<typename U>
            inline constexpr const bool operator<=(const U& rhs) const noexcept
            {
                return _value <= rhs;
            }

            template<typename U>
            inline constexpr const bool operator>(const U& rhs) const noexcept
            {
                return _value > rhs;
            }

            template<typename U>
            inline constexpr const bool operator>=(const U& rhs) const noexcept
            {
                return _value >= rhs;
            }

        public:
            template<typename U, reference::ReferenceCategory c>
            inline constexpr decltype(auto) operator<=>(const ValOrRef<U, c>& rhs) const noexcept
            {
                return _value <=> *rhs;
            }

            template<typename U, reference::ReferenceCategory c>
            inline constexpr decltype(auto) operator<=>(const reference::RefImpl<U, c>& rhs) const noexcept
            {
                return _value <=> *rhs;
            }

            template<typename U>
            inline constexpr decltype(auto) operator<=>(const U& rhs) const noexcept
            {
                return _value <=> rhs;
            }

        private:
            ValueType _value;
        };
    };
};

template<typename T, typename U, typename R, ospf::reference::ReferenceCategory cat>
inline constexpr const bool operator==(const ospf::reference::RefImpl<T, R>& lhs, const ospf::ValOrRef<U, cat>& rhs) noexcept
{
    return *lhs == *rhs;
}

template<typename T, typename U, typename R, ospf::reference::ReferenceCategory cat>
inline constexpr const bool operator!=(const ospf::reference::RefImpl<T, R>& lhs, const ospf::ValOrRef<U, cat>& rhs) noexcept
{
    return *lhs != *rhs;
}

template<typename T, typename U, ospf::reference::ReferenceCategory cat>
inline constexpr const bool operator==(const T& lhs, const ospf::ValOrRef<U, cat>& rhs) noexcept
{
    return lhs == *rhs;
}

template<typename T, typename U, ospf::reference::ReferenceCategory cat>
inline constexpr const bool operator!=(const T& lhs, const ospf::ValOrRef<U, cat>& rhs) noexcept
{
    return lhs != *rhs;
}

template<typename T, typename U, typename R, ospf::reference::ReferenceCategory cat>
inline constexpr const bool operator<(const ospf::reference::RefImpl<T, R>& lhs, const ospf::ValOrRef<U, cat>& rhs) noexcept
{
    return *lhs < *rhs;
}

template<typename T, typename U, typename R, ospf::reference::ReferenceCategory cat>
inline constexpr const bool operator<=(const ospf::reference::RefImpl<T, R>& lhs, const ospf::ValOrRef<U, cat>& rhs) noexcept
{
    return *lhs <= *rhs;
}

template<typename T, typename U, typename R, ospf::reference::ReferenceCategory cat>
inline constexpr const bool operator>(const ospf::reference::RefImpl<T, R>& lhs, const ospf::ValOrRef<U, cat>& rhs) noexcept
{
    return *lhs > *rhs;
}

template<typename T, typename U, typename R, ospf::reference::ReferenceCategory cat>
inline constexpr const bool operator>=(const ospf::reference::RefImpl<T, R>& lhs, const ospf::ValOrRef<U, cat>& rhs) noexcept
{
    return *lhs >= *rhs;
}

template<typename T, typename U, ospf::reference::ReferenceCategory cat>
inline constexpr const bool operator<(const T& lhs, const ospf::ValOrRef<U, cat>& rhs) noexcept
{
    return lhs < *rhs;
}

template<typename T, typename U, ospf::reference::ReferenceCategory cat>
inline constexpr const bool operator<=(const T& lhs, const ospf::ValOrRef<U, cat>& rhs) noexcept
{
    return lhs <= *rhs;
}

template<typename T, typename U, ospf::reference::ReferenceCategory cat>
inline constexpr const bool operator>(const T& lhs, const ospf::ValOrRef<U, cat>& rhs) noexcept
{
    return lhs > *rhs;
}

template<typename T, typename U, ospf::reference::ReferenceCategory cat>
inline constexpr const bool operator>=(const T& lhs, const ospf::ValOrRef<U, cat>& rhs) noexcept
{
    return lhs >= *rhs;
}

template<typename T, typename U, typename R, ospf::reference::ReferenceCategory cat>
inline constexpr decltype(auto) operator<=>(const ospf::reference::RefImpl<T, R>& lhs, const ospf::ValOrRef<U, cat>& rhs) noexcept
{
    return *lhs <=> *rhs;
}

template<typename T, typename U, ospf::reference::ReferenceCategory cat>
inline constexpr decltype(auto) operator<=>(const T& lhs, const ospf::ValOrRef<U, cat>& rhs) noexcept
{
    return lhs <=> *rhs;
}

namespace std
{
    template<typename T, ospf::reference::ReferenceCategory cat>
    struct hash<ospf::ValOrRef<T, cat>>
    {
        using ValueType = ospf::ValOrRef<T, cat>;

        inline const ospf::usize operator()(ospf::ArgCLRefType<ValueType> value) const noexcept
        {
            static const auto func = hash<T>{};
            return func(*value);
        }
    };

    template<typename T, ospf::reference::ReferenceCategory cat, typename CharT>
    struct formatter<ospf::ValOrRef<T, cat>, CharT>
        : public formatter<T, CharT>
    {
        using ValueType = ospf::ValOrRef<T, cat>;

        template<typename FormatContext>
        inline static decltype(auto) format(ospf::ArgCLRefType<ValueType> value, FormatContext& fc)
        {
            return formatter<T, CharT>::format(*value, fc);
        }
    };
};

namespace ospf
{
    template<typename T, ospf::reference::ReferenceCategory cat>
        requires WithTag<T>
    struct TagValue<ValOrRef<T, cat>>
    {
        using Type = typename TagValue<T>::Type;
        using ValueType = ValOrRef<T, cat>;

        inline RetType<Type> value(ArgCLRefType<ValueType> value) const noexcept
        {
            static constexpr const auto extractor = TagValue<T>{};
            return extractor(*value);
        }
    };
};