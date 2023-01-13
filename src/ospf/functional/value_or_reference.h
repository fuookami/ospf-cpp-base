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
            using PtrType = PtrType<ValueType>;
            using CPtrType = CPtrType<ValueType>;
            using RefType = LRefType<ValueType>;
            using CRefType = CLRefType<ValueType>;
            using ReferenceType = reference::Ref<ValueType, cat>;
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

            inline static constexpr RetType<ValOrRef> ref(CLRefType<ValueType> val) noexcept
            {
                return ValOrRef{ ReferenceType{ val } };
            }

            inline static constexpr RetType<ValOrRef> ref(ArgRRefType<ReferenceType> ref) noexcept
            {
                return ValOrRef{ move<ReferenceType>(ref) };
            }

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
            inline constexpr LRefType<ValueType> operator*(void) noexcept
            {
                return visit([](auto& arg)
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

            inline constexpr CLRefType<ValueType> operator*(void) const noexcept
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

        public:


        private:
            EitherType _either;
        };
    };
};
