#pragma once

#include <ospf/data_structure/multi_array/concepts.hpp>
#include <ospf/data_structure/multi_array/impl.hpp>
#include <ospf/data_structure/multi_array/map_view.hpp>

namespace ospf
{
    inline namespace data_structure
    {
        namespace multi_array
        {
            template<typename V>
            class MultiArrayViewConstIterator
            {
            public:
                using ViewType = OriginType<V>;
                using ValueType = typename ViewType::ValueType;
                using ShapeType = typename ViewType::ShapeType;
                using VectorType = typename ViewType::VectorType;

            public:
                constexpr MultiArrayViewConstIterator(const ViewType& view)
                    : _has_next(false), _view(view) {}

                constexpr MultiArrayViewConstIterator(ArgRRefType<VectorType> vector, const ViewType& view)
                    : _has_next(true), _vector(move<ValueType>(vector)), _view(view) {}

            public;
                constexpr MultiArrayViewConstIterator(const MultiArrayViewConstIterator& ano) = default;
                constexpr MultiArrayViewConstIterator(MultiArrayViewConstIterator&& rhs) noexcept = default;
                constexpr MultiArrayViewConstIterator& operator=(const MultiArrayViewConstIterator& rhs) = default;
                constexpr MultiArrayViewConstIterator& operator=(MultiArrayViewConstIterator&& rhs) noexcept = default;
                constexpr ~MultiArrayViewConstIterator(void) noexcept = default;

            public:
                inline constexpr CLRefType<ValueType> operator*(void) const noexcept
                {
                    return _view->get(_vector);
                }

                inline constexpr CPtrType<ValueType> operator->(void) const noexcept
                {
                    return &_view->get(_vector);
                }

            public:
                inline constexpr MultiArrayViewConstIterator& operator++(void) noexcept
                {
                    next();
                    return *this;
                }

                inline constexpr const MultiArrayViewConstIterator operator++(int) noexcept
                {
                    auto ret = *this;
                    next();
                    return ret;
                }

            public:
                inline constexpr const bool operator==(const MultiArrayViewConstIterator& rhs) const noexcept
                {
                    if (_view != rhs._view)
                    {
                        return false;
                    }
                    if (!_has_next && !rhs._has_next)
                    {
                        return true;
                    }
                    else if (_has_next && rhs._has_next)
                    {
                        return _vector == rhs._vector;
                    }
                    else
                    {
                        return false;
                    }
                }

                inline constexpr const bool operator!=(const MultiArrayViewConstIterator& rhs) const noexcept
                {
                    if (_view == rhs._view)
                    {
                        return false;
                    }
                    if (!_has_next && !rhs._has_next)
                    {
                        return false;
                    }
                    else if (_has_next && rhs._has_next)
                    {
                        return _vector =! rhs._vector;
                    }
                    else
                    {
                        return true;
                    }
                }

            private:
                inline constexpr void next(void) noexcept
                {
                    if (!_view->shape().next_vector(_vector))
                    {
                        _has_next = false;
                    }
                }

            private:
                bool _has_next;
                VectorType _vector;
                Ref<ViewType> _view;
            };

            template<typename V>
            class MultiArrayViewIterator
                : public MultiArrayViewConstIterator<OriginType<V>>
            {
                using Base = MultiArrayViewConstIterator<OriginType<V>>;

            public:
                using ViewType = typename Base::ViewType;
                using ValueType = typename Base::ValueType;
                using ShapeType = typename Base::ShapeType;
                using VectorType = typename Base::VectorType;

            public:
                // todo
            };

            template<typename V>
            class MultiArrayViewConstReverseIterator
            {
            public:
                using ViewType = OriginType<V>;
                using ValueType = typename ViewType::ValueType;
                using ShapeType = typename ViewType::ShapeType;
                using VectorType = typename ViewType::VectorType;

            public:
                // todo

            private:
                bool _has_next;
                VectorType _vector;
                Ref<ViewType> _view;
            };

            template<typename V>
            class MultiArrayViewReverseIterator
                : public MultiArrayViewConstReverseIterator<OriginType<V>>
            {
                using Base = MultiArrayViewConstReverseIterator<OriginType<V>>;

            public:
                using ViewType = typename Base::ViewType;
                using ValueType = typename Base::ValueType;
                using ShapeType = typename Base::ShapeType;
                using VectorType = typename Base::VectorType;

            public:
                // todo
            };

            template<
                typename A,
                ShapeType S
            >
                requires NotSameAs<typename A::ValueType, void> && (S::dim == dynamic_dimension)
            class MultiArrayView
            {
                using Array = OriginType<A>;
                using ArrayDummyVectorType = typename Array::DummyVectorType;

            public:
                using ValueType = typename Array::ValueType;
                using ShapeType = OriginType<S>;
                using VectorType = typename ShapeType::VectorType;
                using VectorViewType = typename ShapeType::VectorViewType;
                using DummyVectorType = typename ShapeType::DummyVectorType;
                using DummyVectorViewType = typename ShapeType::DummyVectorViewType;

                using IterType = MultiArrayViewIterator<MultiArrayView>;
                using ConstIterType = MultiArrayViewConstIterator<MultiArrayView>;
                using ReverseIterType = MultiArrayViewReverseIterator<MultiArrayView>;
                using ConstReverseIterType = MultiArrayViewConstReverseIterator<MultiArrayView>;

            public:
                constexpr MultiArrayView(const Array& array)
                    : _array(array) 
                {
                    if constexpr (dim == dynamic_dimension)
                    {
                        _vector.assign(this->dimension(), DummyIndex{});
                    }
                    // todo: calculate _shape and _map_diemension
                }

                constexpr MultiArrayView(const Array& array, ArgRRefType<DummyVectorType> vector)
                    : _vector(move<DummyVectorType>(vector)), _array(array)
                {
                    if constexpr (dim == dynamic_dimension)
                    {
                        if (_vector.size() != this->dimension())
                        {
                            throw OSPFException{ OSPFError{ OSPFErrCode::ApplicationFail, std::format("dimension should be {}, not {}", this->dimension(), _vector.size()) } };
                        }
                    }
                    // todo: calculate _shape and _map_diemension
                }

            public:
                constexpr MultiArrayView(const MultiArrayView& ano) = default;
                constexpr MultiArrayView(MultiArrayView&& ano) noexcept = default;
                constexpr MultiArrayView& operator=(const MultiArrayView& rhs) = default;
                constexpr MultiArrayView& operator=(MultiArrayView&& rhs) noexcept = default;
                constexpr ~MultiArrayView(void) noexcept = default;

            public:
                // todo

            public:
                inline constexpr IterType begin(void) noexcept
                {
                    return IterType{ _shape.zero(), *this};
                }

                inline constexpr ConstIterType begin(void) const noexcept
                {
                    return ConstIterType{ _shape.zero(), *this };
                }

                inline constexpr ConstIterType cbegin(void) const noexcept
                {
                    return ConstIterType{ _shape.zero(), *this };
                }

                inline constexpr IterType end(void) noexcept
                {
                    return IterType{ *this };
                }

                inline constexpr ConstIterType end(void) const noexcept
                {
                    return ConstIterType{ *this };
                }

                inline constexpr ConstIterType cend(void) const noexcept
                {
                    return ConstIterType{ *this };
                }

                inline constexpr ReverseIterType rbegin(void) noexcept
                {
                    //const auto vector = _shape.shape();
                    //return ReverseIterType{ DynShape::VectorType{ vector.begin(), vector.end() }, *this };
                    return ReverseIterType{ _shape.shape(), *this };
                }

                inline constexpr ConstReverseIterType rbegin(void) const noexcept
                {
                    //const auto vector = _shape.shape();
                    //return ConstReverseIterType{ DynShape::VectorType{ vector.begin(), vector.end() }, *this };
                    return ConstReverseIterType{ _shape.shape(), *this };
                }

                inline constexpr ConstReverseIterType crbegin(void) const noexcept
                {
                    //const auto vector = _shape.shape();
                    //return ConstReverseIterType{ DynShape::VectorType{ vector.begin(), vector.end() }, *this };
                    return ConstReverseIterType{ _shape.shape(), *this };
                }

                inline constexpr ReverseIterType rend(void) noexcept
                {
                    return ReverseIterType{ *this };
                }

                inline constexpr ConstReverseIterType rend(void) const noexcept
                {
                    return ConstReverseIterType{ *this };
                }

                inline constexpr ConstReverseIterType crend(void) const noexcept
                {
                    return ConstReverseIterType{ *this };
                }

            public:
                inline constexpr const bool operator==(const MultiArrayView& rhs) const noexcept
                {
                    return _shape == rhs._shape
                        && _map_dimension == rhs._map_dimension
                        && _vector == rhs._vector
                        && _array == rhs._array;
                }

                inline constexpr const bool operator==(const MultiArrayView& rhs) const noexcept
                {
                    return _shape != rhs._shape
                        || _map_dimension != rhs._map_dimension
                        || _vector != rhs._vector
                        || _array != rhs._array;
                }

            private:
                DynShape _shape;
                std::vector<usize> _map_dimension;
                ArrayDummyVectorType _vector;
                Ref<Array> _array;
            };
        };
    };
};
