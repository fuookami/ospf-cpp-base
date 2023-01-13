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
            // todo: impl it

        public:
            using ValueType = OriginType<T>;
            using RefType = reference::Ref<ValueType, cat>;

        public:
            inline static ValOrRef value(CLRefType<ValueType> val) noexcept
            {
                return ValOrRef{ val };
            }

            inline static ValOrRef ref(CLRefType<ValueType> val) noexcept
            {
                return ValOrRef{ RefType{ val } };
            }

        private:
            template<typename = void>
                requires std::is_copy_constructible_v<RefType>
            ValOrRef(const RefType ref)
                : _either(ref) {}

            template<typename = void>
                requires ReferenceFaster<RefType> && std::movable<RefType>
            ValOrRef(RRefType<RefType> ref)
                : _either(move<RefType>(ref)) {}

        public:

        public:
            inline constexpr ValueType& operator*(void) noexcept
            {
                return ospf::visit([](auto& arg)
                    {
                        using ThisType = std::decay_t<decltype(arg)>;
                        if constexpr (std::is_same_v<ThisType, ValueType>)
                        {
                            return arg;
                        }
                        else if constexpr (std::is_same_v<ThisType, RefType>)
                        {
                            return *arg;
                        }
                        else
                        {
                            static_assert(false, "Non-exhaustive visitor!");
                        }
                    }, _either);
            }

            inline constexpr const ValueType& operator*(void) const noexcept
            {
                return ospf::visit([](const auto& arg)
                    {
                        using ThisType = std::decay_t<decltype(arg)>;
                        if constexpr (std::is_same_v<ThisType, ValueType>)
                        {
                            return arg;
                        }
                        else if constexpr (std::is_same_v<ThisType, RefType>)
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
            Either<ValueType, RefType> _either;
        };
    };
};
