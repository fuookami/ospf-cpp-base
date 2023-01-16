#pragma once

#include <ospf/concepts/base.hpp>
#include <ospf/type_family.hpp>
#include <variant>

namespace ospf
{
    inline namespace functional
    {
        struct Unbounded {};
        static constexpr const auto unbounded = Unbounded{};

        template<typename I>
        class Bound
        {
        public:
            using IndexType = OriginType<I>;

            struct Included 
            {
                IndexType value;

                inline constexpr operator LRefType<IndexType>(void) noexcept
                {
                    return value;
                }

                inline constexpr operator CLRefType<IndexType>(void) noexcept
                {
                    return value;
                }
            };

            struct Excluded
            {
                IndexType value;

                inline constexpr operator LRefType<IndexType>(void) noexcept
                {
                    return value;
                }

                inline constexpr operator CLRefType<IndexType>(void) noexcept
                {
                    return value;
                }
            };

            using VariantType = std::variant<Included, Excluded, Unbounded>;

        public:
            Bound(const Unbounded _ = unbounded)
                : _varaint(unbounded) {}

            Bound(ArgCLRefType<Included> included)
                : _variant(included) {}

            Bound(ArgRRefType<Included> included)
                : _variant(move<Included>(included)) {}

        public:
            inline const bool inclusive(void) const noexcept
            {
                return _variant.index() == 0_uz;
            }

            inline const bool exclusive(void) const noexcept
            {
                return _variant.index() == 1_uz;
            }

            inline const bool unbounded(void) const noexcept
            {
                return _variant.index() == 2_uz;
            }

        public:
            inline ArgCLRefType<IndexType> operator*(void) const
            {
                return std::visit([](const auto& arg)
                    {
                        using Type = OriginType<decltype(arg)>;
                        if constexpr (std::is_same_v<Type, Included> || std::is_same_v<Type, Excluded>)
                        {
                            return arg.value;
                        }
                        else
                        {
                            throw std::bad_variant_access{};
                            return 0_uz;
                        }
                    }, _variant);
            }

        private:
            VariantType _variant;
        };

        template<typename I>
        class RangeBounds
        {
        public:
            using IndexType = OriginType<I>;
            using BoundType = Bound<IndexType>;
            using IncludedType = typename BoundType::Included;
            using ExcludedType = typename BoundType::Excluded;

            //tex:$(- \infty , \infty)$
            inline static constexpr RetType<RangeBounds> full(void) noexcept
            {
                return RangeBounds{ BoundType{ unbounded }, BoundType{ unbounded } };
            }

            //tex:$[L, \infty )$
            inline static constexpr RetType<RangeBounds> from(ArgRRefType<IndexType> start_bound) noexcept
            {
                return RangeBounds{ BoundType{ IncludedType{ move<IndexType>(start_bound) } }, BoundType{ unbounded } };
            }

            //tex:$(- \infty , R)$
            inline static constexpr RetType<RangeBounds> to(ArgRRefType<IndexType> end_bound) noexcept
            {
                return RangeBounds{ BoundType{ unbounded } }, BoundType{ ExcludedType{ move<IndexType>(end_bound) } };
            }

            //tex:$[L, R)$
            inline static constexpr RetType<RangeBounds> range(ArgRRefType<IndexType> start_bound, ArgRRefType<IndexType> end_bound) noexcept
            {
                return RangeBounds{ BoundType{ IncludedType{ move<IndexType>(start_bound) } }, BoundType{ ExcludedType{ move<IndexType>(end_bound) } } };
            }

            //tex:$[L, R]$
            inline static constexpr RetType<RangeBounds> inclusive(ArgRRefType<IndexType> start_bound, ArgRRefType<IndexType> end_bound) noexcept
            {
                return RangeBounds{ BoundType{ IncludedType{ move<IndexType>(start_bound) } }, BoundType{ IncludedType{ move<IndexType>(end_bound) } } };
            }

            //tex:$(- \infty, R]$
            inline static constexpr RetType<RangeBounds> to_inclusive(ArgRRefType<IndexType> end_bound) noexcept
            {
                return RangeBounds{ BoundType{ unbounded } }, BoundType{ IncludedType{ move<IndexType>(end_bound) } };
            }

        public:
            inline constexpr ArgCLRefType<Bound<IndexType>> start_bound(void) const noexcept
            {
                return _start_bound;
            }

            inline constexpr ArgCLRefType<Bound<IndexType>> end_bound(void) const noexcept
            {
                return _end_bound;
            }

            template<typename = void>
                requires std::three_way_comparable<IndexType> || std::totally_ordered<IndexType>
            inline constexpr const bool contains(ArgCLRefType<IndexType> value) const noexcept
            {
                return in_start_bound(value) && in_end_bound(value);
            }

        private:
            inline constexpr const bool in_start_bound(ArgCLRefType<IndexType> value) const noexcept
            {
                if (_start_bound.inclusive())
                {
                    return *_start_bound <= value;
                }
                else if (_start_bound.exclusive())
                {
                    return *_start_bound < value;
                }
                else
                {
                    return true;
                }
            }

            inline constexpr const bool in_end_bound(ArgCLRefType<IndexType> value) const noexcept
            {
                if (_end_bound.inclusive())
                {
                    return value <= *_end_bound;
                }
                else if (_end_bound.exclusive())
                {
                    return value < *_end_bound;
                }
                else
                {
                    return true;
                }
            }

        private:
            BoundType _start_bound;
            BoundType _end_bound
        };
    };
};
