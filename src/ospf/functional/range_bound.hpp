#pragma once

#include <ospf/concepts/base.hpp>
#include <ospf/type_family.hpp>
#include <ospf/meta_programming/iterator.hpp>
#include <ospf/memory/reference.hpp>
#include <ospf/exception.hpp>
#include <variant>

namespace ospf
{
    inline namespace functional
    {
        struct Unbounded {};
        static constexpr const auto unbounded = Unbounded{};

        template<typename T>
            requires std::integral<T>
                && requires
                { 
                    { static_cast<T>(0) } -> DecaySameAs<T>;
                    { static_cast<T>(1) } -> DecaySameAs<T>;
                    { -std::declval<T>() } -> DecaySameAs<T>;
                }
        class IntegerIterator
        {
        public:
            using ValueType = OriginType<T>;

        public:
            constexpr IntegerIterator(void)
                : _has_next(false), _curr(static_cast<ValueType>(0)), _last(static_cast<ValueType>(0)), _step(static_cast<ValueType>(0)) {}

            constexpr IntegerIterator(ArgRRefType<ValueType> curr, ArgRRefType<ValueType> last, ArgRRefType<ValueType> step, const bool reverse = false)
                : _has_next(true), _curr(static_cast<ValueType>(0)), _last(static_cast<ValueType>(0)), _step(reverse ? move<ValueType>(step) : -move<ValueType>(step))
            {
                // todo
            }

        public:
            constexpr IntegerIterator(const IntegerIterator& ano) = default;
            constexpr IntegerIterator(IntegerIterator&& ano) noexcept = default;
            constexpr IntegerIterator& operator=(const IntegerIterator& rhs) = default;
            constexpr IntegerIterator& operator=(IntegerIterator&& rhs) noexcept = default;
            constexpr ~IntegerIterator(void) noexcept = default;

        public:
            inline constexpr ArgCLRefType<ValueType> operator*(void) const noexcept
            {
                return _curr;
            }

            inline constexpr const CPtrType<ValueType> operator->(void) const noexcept
            {
                return &_curr;
            }

        public:
            inline constexpr LRefType<IntegerIterator> operator++(void) noexcept
            {
                next();
                return *this;
            }

            inline constexpr RetType<IntegerIterator> operator++(int) noexcept
            {
                auto ret = *this;
                next();
                return ret;
            }

        public:
            template<typename I>
            inline constexpr const bool operator==(const IntegerIterator<I>& ano) const noexcept
            {
                if (!_has_next && !_has_next)
                {
                    return true;
                }
                else if (_has_next && _has_next)
                {
                    return _curr == ano._curr
                        && _last == ano._last
                        && _step == ano._step;
                }
                else
                {
                    return false;
                }
            }

            template<typename I>
            inline constexpr const bool operator!=(const IntegerIterator<I>& ano) const noexcept
            {
                if (!_has_next && !_has_next)
                {
                    return false;
                }
                else if (_has_next && _has_next)
                {
                    return _curr != ano._curr
                        || _last != ano._last
                        || _step != ano._step;
                }
                else
                {
                    return true;
                }
            }

        private:
            inline constexpr void next(void) noexcept
            {
                // todo
            }

        private:
            bool _has_next;
            ValueType _curr;
            ValueType _last;
            ValueType _step;
        };

        template<typename T>
            requires std::unsigned_integral<T>
                && requires
                {
                    { static_cast<T>(0) } -> DecaySameAs<T>;
                    { static_cast<T>(1) } -> DecaySameAs<T>;
                }
        class IntegerIterator<T>
        {
        public:
            using ValueType = OriginType<T>;

        public:
            constexpr IntegerIterator(const IntegerIterator& ano) = default;
            constexpr IntegerIterator(IntegerIterator&& ano) noexcept = default;
            constexpr IntegerIterator& operator=(const IntegerIterator& rhs) = default;
            constexpr IntegerIterator& operator=(IntegerIterator&& rhs) noexcept = default;
            constexpr ~IntegerIterator(void) noexcept = default;

            // todo

        private:
            bool _has_next;
            bool _reverse;
            ValueType _curr;
            ValueType _last;
            ValueType _step;
        };

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
            constexpr Bound(const Unbounded _ = unbounded)
                : _varaint(unbounded) {}

            constexpr Bound(ArgCLRefType<Included> included)
                : _variant(included) {}

            constexpr Bound(ArgRRefType<Included> included)
                : _variant(move<Included>(included)) {}

        public:
            constexpr Bound(const Bound& ano) = default;
            constexpr Bound(Bound&& ano) noexcept = default;
            constexpr Bound& operator=(const Bound& rhs) = default;
            constexpr Bound& operator=(Bound&& rhs) noexcept = default;
            constexpr ~Bound(void) noexcept = default;

        public:
            inline constexpr const bool inclusive(void) const noexcept
            {
                return _variant.index() == 0_uz;
            }

            inline constexpr const bool exclusive(void) const noexcept
            {
                return _variant.index() == 1_uz;
            }

            inline constexpr const bool unbounded(void) const noexcept
            {
                return _variant.index() == 2_uz;
            }

        public:
            inline constexpr ArgCLRefType<IndexType> operator*(void) const
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
                            throw OSPFException{ OSPFErrCode::ApplicationError, "unbounded accessed" };
                            return 0_uz;
                        }
                    }, _variant);
            }

        private:
            VariantType _variant;
        };

        template<typename I>
        class RangeBounds;

        template<typename I>
        class RangeBoundsReverseWrapper;

        template<typename R>
        concept RangeBoundsType = requires (const R& r)
        {
            { r.start_bound() } -> DecaySameAs<typename R::BoundType>;
            // todo
        };

        template<typename I>
            requires std::integral<I>
        class IntegerRangeBoundsWithStepWrapper
        {
            friend class RangeBounds<I>;
            friend class RangeBoundsReverseWrapper<I>;

        public:
            using RangeBoundsType = RangeBounds<I>;
            using IndexType = typename RangeBoundsType::IndexType;
            using BoundType = typename RangeBoundsType::BoundType;
            using IncludedType = typename RangeBoundsType::Included;
            using ExcludedType = typename RangeBoundsType::Excluded;

        private:
            constexpr IntegerRangeBoundsWithStepWrapper(CLRefType<RangeBoundsType> bounds, ArgRRefType<IndexType> step, const bool reverse = false)
                : _reverse(reverse), _bounds(bounds), _step(move<IndexType>(step)) {}

        public:
            constexpr IntegerRangeBoundsWithStepWrapper(const IntegerRangeBoundsWithStepWrapper& ano) = default;
            constexpr IntegerRangeBoundsWithStepWrapper(IntegerRangeBoundsWithStepWrapper&& ano) noexcept = default;
            constexpr IntegerRangeBoundsWithStepWrapper& operator=(const IntegerRangeBoundsWithStepWrapper& rhs) = default;
            constexpr IntegerRangeBoundsWithStepWrapper& operator=(IntegerRangeBoundsWithStepWrapper&& rhs) noexcept = default;
            constexpr ~IntegerRangeBoundsWithStepWrapper(void) noexcept = default;

        public:
            inline constexpr RetType<IntegerIterator<IndexType>> begin(void) const noexcept
            {
                if (_reverse)
                {
                    // todo
                }
                else
                {
                    return IntegerIterator<IndexType>{ *_start_bound, * _end_bound, _step };
                }
            }

            inline constexpr RetType<IntegerIterator<IndexType>> end(void) const noexcept
            {
                return IntegerIterator<IndexType>{};
            }

        private:
            bool _reverse;
            IndexType _step;
            Ref<RangeBoundsType> _bounds;
        };

        template<typename I>
        class RangeBoundsReverseWrapper
        {
            friend class RangeBounds<I>;

        public:
            using RangeBoundsType = RangeBounds<I>;
            using IndexType = typename RangeBoundsType::IndexType;
            using BoundType = typename RangeBoundsType::BoundType;
            using IncludedType = typename RangeBoundsType::Included;
            using ExcludedType = typename RangeBoundsType::Excluded;

        private:
            constexpr RangeBoundsReverseWrapper(const RangeBoundsType& bounds)
                : _bounds(bounds) {}

        public:
            constexpr RangeBoundsReverseWrapper(const RangeBoundsReverseWrapper& ano) = default;
            constexpr RangeBoundsReverseWrapper(RangeBoundsReverseWrapper&& ano) noexcept = default;
            constexpr RangeBoundsReverseWrapper& operator=(const RangeBoundsReverseWrapper& rhs) = default;
            constexpr RangeBoundsReverseWrapper& operator=(RangeBoundsReverseWrapper&& rhs) noexcept = default;
            constexpr ~RangeBoundsReverseWrapper(void) noexcept = default;

        public:
            inline constexpr const bool empty(void) const noexcept
            {
                return _bounds->empty();
            }

            inline constexpr ArgCLRefType<BoundType> start_bound(void) const noexcept
            {
                return _bounds->end_bound();
            }

            inline constexpr ArgCLRefType<BoundType> end_bound(void) const noexcept
            {
                return _bounds->start_bound();
            }

            template<typename = void>
                requires std::three_way_comparable<IndexType> || std::totally_ordered<IndexType>
            inline constexpr const bool contains(ArgCLRefType<IndexType> value) const noexcept
            {
                return _bounds.contains(value);
            }
        
        public:
            inline constexpr RetType<IntegerRangeBoundsWithStepWrapper<IndexType>> step(ArgRRefType<IndexType> step) const noexcept
            {
                return IntegerRangeBoundsWithStepWrapper<IndexType>{ *this, move<IndexType>(step), true };
            }

        private:
            Ref<RangeBoundsType> _bounds;
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

        private:
            constexpr RangeBounds(ArgRRefType<BoundType> start_bound, ArgRRefType<BoundType> end_bound)
                : _start_bound(move<BoundType>(start_bound)), _end_bound(move<BoundType>(end_bound)) {}

        public:
            constexpr RangeBounds(const RangeBounds& ano) = default;
            constexpr RangeBounds(RangeBounds&& ano) noexcept = default;
            constexpr RangeBounds& operator=(const RangeBounds& rhs) = default;
            constexpr RangeBounds& operator=(RangeBounds&& rhs) noexcept = default;
            constexpr ~RangeBounds(void) noexcept = default;

        public:
            inline constexpr const bool empty(void) const noexcept
            {
                if (_start_bound.unbounded() || _end_bound.unbounded())
                {
                    return false;
                }
                else if (_start_bound.inclusive() && _start_bound.inclusive())
                {
                    return *_start_bound > *_end_bound;
                }
                else
                {
                    return *_start_bound >= *_end_bound;
                }
            }

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

        public:
            inline constexpr RetType<RangeBoundsReverseWrapper<IndexType>> reverse(void) const noexcept
            {
                return RangeBoundsReverseWrapper<IndexType>{ *this };
            }

            inline constexpr RetType<IntegerRangeBoundsWithStepWrapper<IndexType>> step(ArgRRefType<IndexType> step) const noexcept
            {
                return IntegerRangeBoundsWithStepWrapper<IndexType>{ *this, move<IndexType>(step) };
            }

        public:
            template<typename = void>
                requires std::integral<IndexType>
                    && requires
                    {
                        { static_cast<IndexType>(1) } -> DecaySameAs<IndexType>;
                    }
            inline constexpr RetType<IntegerIterator<IndexType>> begin(void) const noexcept
            {
                return IntegerIterator<IndexType>{ *_start_bound, *_end_bound, static_cast<IndexType>(1) };
            }

            template<typename = void>
                requires std::integral<IndexType>
            inline constexpr RetType<IntegerIterator<IndexType>> end(void) const noexcept
            {
                return IntegerIterator<IndexType>{ };
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
            BoundType _end_bound;
        };
    };
};

// todo: DSL to make range bounds
