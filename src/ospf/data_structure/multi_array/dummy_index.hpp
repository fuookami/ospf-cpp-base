#pragma once

#include <ospf/data_structure/multi_array/shape.hpp>
#include <ospf/functional/integer_iterator.hpp>
#include <ospf/functional/range_bounds.hpp>
#include <ospf/meta_programming/variable_type_list.hpp>
#include <ospf/ospf_base_api.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <variant>

namespace ospf
{
    namespace data_structure
    {
        namespace multi_array
        {
            namespace dummy_index
            {
                using RangeFull = range_bounds::RangeFull;

                class DummyIndexEnumerator
                {
                    using Transformer = std::function<std::optional<usize>(const isize)>;
                    using Continuous1 = IntegerIterator<usize>;
                    using Continuous2 = IntegerIterator<isize>;
                    using Discrete1 = std::vector<usize>::const_iterator;
                    using Discrete2 = std::vector<isize>::const_iterator;
                    using Variant = std::variant<Continuous1, Continuous2, Discrete1, Discrete2>;

                public:
                    OSPF_BASE_API constexpr DummyIndexEnumerator(ArgRRefType<Continuous1> first, ArgRRefType<Continuous1> last);
                    OSPF_BASE_API constexpr DummyIndexEnumerator(ArgRRefType<Continuous2> first, ArgRRefType<Continuous2> last, ArgRRefType<Transformer> transformer);
                    OSPF_BASE_API constexpr DummyIndexEnumerator(ArgRRefType<Discrete1> first, ArgRRefType<Discrete1> last);
                    OSPF_BASE_API constexpr DummyIndexEnumerator(ArgRRefType<Discrete2> first, ArgRRefType<Discrete2> last, ArgRRefType<Transformer> transformer);

                public:
                    OSPF_BASE_API constexpr DummyIndexEnumerator(const DummyIndexEnumerator& ano) = default;
                    OSPF_BASE_API constexpr DummyIndexEnumerator(DummyIndexEnumerator&& ano) noexcept = default;
                    OSPF_BASE_API constexpr DummyIndexEnumerator& operator=(const DummyIndexEnumerator& rhs) = default;
                    OSPF_BASE_API constexpr DummyIndexEnumerator& operator=(DummyIndexEnumerator&& rhs) noexcept = default;
                    OSPF_BASE_API constexpr ~DummyIndexEnumerator(void) noexcept = default;

                public:
                    inline constexpr operator const bool(void) const noexcept
                    {
                        return _has_next;
                    }

                public:
                    inline constexpr std::optional<usize> operator*(void) const noexcept
                    {
                        if (_curr == _end)
                        {
                            return std::nullopt;
                        }
                        else
                        {
                            return _next;
                        }
                    }

                public:
                    inline constexpr DummyIndexEnumerator& operator++(void) noexcept
                    {
                        next();
                        return *this;
                    }

                    inline constexpr DummyIndexEnumerator operator++(int) noexcept
                    {
                        auto ret = *this;
                        next();
                        return ret;
                    }

                private:
                    OSPF_BASE_API constexpr void next(void) noexcept;

                private:
                    bool _has_next;
                    usize _next;
                    Variant _curr;
                    Variant _end;
                    std::optional<Transformer> _transformer;
                };

                class DummyIndex
                {
                    using Index1 = usize;
                    using Index2 = isize;
                    using Range1 = RangeBounds<usize>;
                    using Range2 = RangeBounds<isize>;
                    using Array1 = std::vector<usize>;
                    using Array2 = std::vector<isize>;
                    using Variant = std::variant<Index1, Index2, Range1, Range2, Array1, Array2>;

                public:
                    using Types = VariableTypeList<Index1, Index2, Range1, Range2, Array1, Array2, RangeFull>;

                public:
                    constexpr DummyIndex(const Index1 index)
                        : _variant(index) {}

                    constexpr DummyIndex(const Index2 index)
                        : _variant(index) {}

                    constexpr DummyIndex(const Range1 range)
                        : _variant(range) {}

                    constexpr DummyIndex(const Range2 range)
                        : _variant(range) {}

                    constexpr DummyIndex(const Array1& array)
                        : _variant(array) {}

                    constexpr DummyIndex(Array1&& array)
                        : _variant(std::move(array)) {}

                    constexpr DummyIndex(const Array2& array)
                        : _variant(array) {}

                    constexpr DummyIndex(Array2&& array)
                        : _variant(std::move(array)) {}

                    constexpr DummyIndex(const RangeFull _)
                        : _variant(RangeBounds<usize>::full()) {}

                public:
                    constexpr DummyIndex(const DummyIndex& ano) = default;
                    constexpr DummyIndex(DummyIndex&& ano) noexcept = default;
                    constexpr DummyIndex& operator=(const DummyIndex& rhs) = default;
                    constexpr DummyIndex& operator=(DummyIndex&& rhs) noexcept = default;
                    constexpr ~DummyIndex(void) noexcept = default;

                public:
                    template<ShapeType S>
                    inline constexpr DummyIndexEnumerator iter(const S& shape, const usize dimension) const noexcept
                    {
                        return std::visit([](const auto& index)
                            {
                                using IndexType = OriginType<decltype(index)>;
                                if constexpr (DecaySameAs<IndexType, Index1>)
                                {
                                    return DummyIndexEnumerator{ IntegerIterator<usize>{ index, index + 1_uz, 1_uz }, IntegerIterator<isize>{} };
                                }
                                else if constexpr (DecaySameAs<IndexType, Index2>)
                                {
                                    return DummyIndexEnumerator{ IntegerIterator<isize>{ index, index + 1_iz, 1_iz }, IntegerIterator<isize>{}, [&shape, dimension](const isize index) { return shape.actual_index(dimension, index); } };
                                }
                                else if constexpr (DecaySameAs<IndexType, Range1, Array1>)
                                {
                                    return DummyIndexEnumerator{ index.begin(), index.end() };
                                }
                                else if constexpr (DecaySameAs<IndexType, Range2, Array2>)
                                {
                                    return DummyIndexEnumerator{ index.begin(), index.end(), [&shape, dimension](const isize index) { return shape.actual_index(dimension, index); } };
                                }
                                //else
                                //{
                                //    static_assert(false, "non-exhaustive visitor!");
                                //}
                            }, _variant);
                    }

                private:
                    Variant _variant;
                };

                template<ShapeType S>
                class DummyAccessEnumerator
                {
                public:
                    using ShapeType = OriginType<S>;
                    using VectorType = typename ShapeType::VectorType;
                    static constexpr const auto dim = ShapeType::dim;

                public:
                    constexpr DummyAccessEnumerator(const ShapeType& shape, const std::span<DummyIndex, dim> dummy_vector)
                        : _has_next(true), _shape(shape), _dummy_vector(dummy_vector), _next(shape.zero())
                    {
                        _enumerators.reserve(shape.dimension());
                        for (auto i{ 0_uz }; i != _shape.dimension(); ++i)
                        {
                            _enumerators.push_back(dummy_vector[i].iter(shape, i));
                        }
                        for (auto i{ 0_uz }; i != _shape.dimension(). ++i)
                        {
                            assert((*_enumerators[i]).has_value());
                            _next[i] = **_enumerators[i];
                            ++_enumerators[i];
                        }
                    }

                public:
                    constexpr DummyAccessEnumerator(const DummyAccessEnumerator& ano) = default;
                    constexpr DummyAccessEnumerator(DummyAccessEnumerator&& ano) noexcept = default;
                    constexpr DummyAccessEnumerator& operator=(const DummyAccessEnumerator& rhs) = default;
                    constexpr DummyAccessEnumerator& operator=(DummyAccessEnumerator&& rhs) noexcept = default;
                    constexpr ~DummyAccessEnumerator(void) noexcept = default;

                public:
                    inline constexpr operator const bool(void) const noexcept
                    {
                        return _has_next;
                    }

                public:
                    inline constexpr std::optional<Ref<VectorType>> operator*(void) const noexcept
                    {
                        if (_curr == _end)
                        {
                            return std::nullopt;
                        }
                        else
                        {
                            return Ref<VectorType>{ _next };
                        }
                    }

                public:
                    inline constexpr DummyAccessEnumerator& operator++(void) noexcept
                    {
                        next();
                        return *this;
                    }

                    inline constexpr DummyAccessEnumerator operator++(int) noexcept
                    {
                        auto ret = *this;
                        next();
                        return ret;
                    }

                public:
                    inline constexpr void next(void) noexcept
                    {
                        assert(_has_next);

                        for (auto i{ _shape.dimension() - 1 }; i != npos; --i)
                        {
                            auto index = *_enumerators[i];
                            if (index.has_value())
                            {
                                _next[i] = *index;
                                return;
                            }
                            else
                            {
                                _enumerators[i] = _dummy_vector[i].iter(*_shape, i);
                                assert((*_enumerators[i]).has_value());
                                _next[i] = **_enumerators[i];
                            }
                            ++_enumerators[i];
                        }
                        _has_next = false;
                    }

                private:
                    bool _has_next;
                    Ref<ShapeType> _shape;
                    std::span<DummyIndex, dim> _dummy_vector;
                    std::vector<DummyIndexEnumerator> _enumerators;
                    VectorType _next;
                };
            };
        };
    };
};