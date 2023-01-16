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

        private:
            VariantType _variant;
        };

        template<typename R>
        concept RangeBounds = NotSameAs<typename R::IndexType, void>
            && requires (const R& range)
                {
                    { range.start_bound() } -> DecaySameAs<Bound<typename R::IndexType>>;
                    { range.end_bound() } -> DecaySameAs<Bound<typename R::IndexType>>;
                    { range.contains(std::declval<typename R::ValueType>()) } -> DecaySameAs<bool>;
                };
        
        template<typename I>
        struct Range
        {
            using IndexType = OriginType<I>;
            using BoundType = Bound<IndexType>;

            Range(ArgRRefType<IndexType> start_bound, ArgRRefType<IndexType> end_bound)
                : _start_bound(BoundType::Included{ move<IndexType>(start_bound) }), _end_bound(BoundType::Included{ move<IndexType>(end_bound) }) {}

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
                return *_start_bound <= value && value <= *_end_bound;
            }

            BoundType _start_bound;
            BoundType _end_bound
        };

        template<typename I>
        struct RangeFrom
        {

        };

        template<typename I>
        struct RangeTo
        {

        };

        template<typename I>
        struct RangeInclusive
        {

        };

        template<typename I>
        struct RangeToInclusive
        {

        };

        template<typename I>
        struct FullRange
        {
            using IndexType = OriginType<I>;
            using BoundType = Bound<IndexType>;

            inline static constexpr Bound<IndexType> start_bound(void) const noexcept
            {
                return BoundType{ unbounded };
            }

            inline static constexpr Bound<IndexType> end_bound(void) const noexcept
            {
                return BoundType{ unbounded };
            }

            template<typename = void>
                requires std::three_way_comparable<IndexType> || std::totally_ordered<IndexType>
            inline constexpr const bool contains(ArgCLRefType<IndexType> value) const noexcept
            {
                return true;
            }
        };
    };
};
