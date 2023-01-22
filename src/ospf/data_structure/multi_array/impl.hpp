#pragma once

#include <ospf/data_structure/multi_array/shape.hpp>
#include <ospf/data_structure/multi_array/dummy_index.hpp>
#include <ospf/data_structure/multi_array/map_index.hpp>
#include <ospf/data_structure/reference_array.hpp>

namespace ospf
{
    inline namespace data_structure
    {
        template<typename A>
        concept MultiArrayType = requires (A& array)
        {
            { std::declval<typename A::ValueType>() } -> DecayNotSameAs<void>;
            { std::declval<typename A::ShapeType>() } -> multi_array::ShapeType;
            { A::dim } -> DecaySameAs<usize>;
            { array.shape() } -> multi_array::ShapeType;
            { array.get(std::declval<typename A::VectorType>()) } -> DecaySameAs<typename A::ValueType>;
            { array.get(std::declval<typename A::VectorViewType>()) } -> DecaySameAs<typename A::ValueType>;
            { array.get(std::declval<std::span<multi_array::dummy_index::DummyIndex>>()) } -> DecaySameAs<typename A::ValueType>;
            // todo
        };

        namespace multi_array
        {
            using RangeFull = range_bounds::RangeFull;
            using DummyIndex = dummy_index::DummyIndex;
            using MapPlaceHolder = map_index::MapPlaceHolder;
            using MapIndex = map_index::MapIndex;

            template<typename... Args>
            struct IsNormalVector
            {
                static constexpr const bool value = false;
            };

            template<typename T>
            struct IsNormalVector<T>
            {
                static constexpr const bool value = DecaySameAs<T, usize> || std::convertible_to<T, usize>;
            };

            template<typename T, typename... Args>
            struct IsNormalVector<T, Args...>
            {
                static constexpr const bool value = IsNormalVector<T>::value && IsNormalVector<Args...>::value;
            };

            template<typename... Args>
            static constexpr const bool is_normal_vector = IsNormalVector<Args...>::value;

            template<typename... Args>
            struct IsDummyVector
            {
                static constexpr const bool value = false;
            };

            template<typename T>
            struct IsDummyVector<T>
            {
                static constexpr const bool value = DummyIndex::Types::template contains<T>;
            };

            template<typename T, typename... Args>
            struct IsDummyVector<T, Args...>
            {
                static constexpr const bool value = IsDummyVector<T>::value && IsDummyVector<Args...>::value;
            };

            template<typename... Args>
            static constexpr const bool is_dummy_vector = IsDummyVector<Args...>::value;

            template<typename... Args>
            struct IsMapVector
            {
                static constexpr const bool value = false;
            };

            template<typename T>
            struct IsMapVector<T>
            {
                static constexpr const bool value = DummyIndex::Types::template contains<T> || DecaySameAs<T, MapPlaceHolder>;
            };

            template<typename T, typename... Args>
            struct IsMapVector<T, Args...>
            {
                static constexpr const bool value = IsMapVector<T>::value && IsMapVector<Args...>::value;
            };

            template<typename... Args>
            static constexpr const bool is_map_vector = IsMapVector<Args...>::value;

            template<typename T, typename C, ShapeType S, typename Self>
            class MultiArrayImpl
            {
                OSPF_CRTP_IMPL

            public:
                using ValueType = OriginType<T>;
                using ContainerType = OriginType<C>;
                using ShapeType = OriginType<S>;
                using VectorType = typename ShapeType::VectorType;
                using VectorViewType = typename ShapeType::VectorViewType;
                static constexpr const auto dim = ShapeType::dim;

                using DummyVectorType = std::conditional_t<dim == dynamic_dimension, std::vector<DummyIndex>, std::array<DummyIndex, dim>>;
                using DummyVectorViewType = std::span<DummyIndex, dim>;

            protected:
                constexpr MultiArrayImpl(void) = default;
            public:
                constexpr MultiArrayImpl(const MultiArrayImpl& ano) = default;
                constexpr MultiArrayImpl(MultiArrayImpl&& ano) noexcept = default;
                constexpr MultiArrayImpl& operator=(const MultiArrayImpl& rhs) = default;
                constexpr MultiArrayImpl& operator=(MultiArrayImpl&& rhs) noexcept = default;
                constexpr ~MultiArrayImpl(void) noexcept = default;

            public:
                inline LRefType<ContainerType> raw(void) noexcept
                {
                    return Trait::get_container(self());
                }

                inline CLRefType<ContainerType> raw(void) const noexcept
                {
                    return Trait::get_const_container(self());
                }

                template<typename = void>
                    requires requires (ContainerType& container) { { container.data() } -> DecaySameAs<PtrType<ValueType>>; }
                inline constexpr const PtrType<ValueType> data(void) noexcept
                {
                    return raw().data();
                }

                template<typename = void>
                    requires requires (const ContainerType& container) { { container.data() } -> DecaySameAs<CPtrType<ValueType>>; }
                inline constexpr const CPtrType<ValueType> data(void) const noexcept
                {
                    return raw().data();
                }

            public:
                inline LRefType<ValueType> get(const usize index)
                {
                    return Trait::get_value(raw(), index);
                }

                inline CLRefType<ValueType> get(const usize index) const
                {
                    return Trait::get_const_value(raw(), index);
                }

                inline LRefType<ValueType> get(const VectorViewType vector)
                {
                    return get(shape().index(vector));
                }

                inline CLRefType<ValueType> get(const VectorViewType vector) const
                {
                    return get(shape().index(vector));
                }

                inline DynRefArray<ValueType> get(const RangeFull _) const
                {
                    DynRefArray<ValueType> ret;
                    ret.reserve(raw().size());
                    for (const auto& val : raw())
                    {
                        ret.push_back(val);
                    }
                    return ret;
                }

                inline DynRefArray<ValueType> get(const DummyVectorViewType dummy_vector) const
                {
                    dummy_index::DummyAccessEnumerator<ShapeType> iter{ shape(), dummy_vector};
                    DynRefArray<ValueType> ret;
                    ret.reserve(iter.size());
                    while (iter)
                    {
                        const auto vector = *iter;
                        ret.push_back(get(vector));
                        ++iter;
                    }
                    return ret;
                }

            public:
                template<typename... Args>
                    requires is_normal_vector<Args...> && !is_dummy_vector<Args...> && !is_map_vector<Args...>
                inline LRefType<ValueType> operator()(Args&&... args) noexcept
                {
                    return get(VectorType{ static_cast<usize>(std::forward<Args>(args))... });
                }

                template<typename... Args>
                    requires is_dummy_vector<Args...> && !is_map_vector<Args...>
                inline DynRefArray<ValueType> operator()(Args&&... args) noexcept
                {
                    return get(DummyVectorType{ DummyIndex{ std::forward<Args>(args) }... });
                }

            public:
                inline LRefType<ValueType> operator[](const VectorViewType vector)
                {
                    return get(vector);
                }

                inline CLRefType<ValueType> operator[](const VectorViewType vector) const
                {
                    return get(vector);
                }

                inline LRefType<ValueType> operator[](std::initializer_list<usize> vector)
                {
                    return get(VectorType{ std::move(vector) });
                }

                inline CLRefType<ValueType> operator[](std::initializer_list<usize> vector) const
                {
                    return get(VectorType{ std::move(vector) });
                }

                inline DynRefArray<ValueType> operator[](const DummyVectorViewType vector) const
                {
                    return get(vector);
                }

                inline DynRefArray<ValueType> operator[](std::initializer_list<DummyIndex> vector) const
                {
                    return get(DummyVectorType{ vector });
                }

            public:
                inline constexpr decltype(auto) begin(void) noexcept
                {
                    return raw().begin();
                }

                inline constexpr decltype(auto) begin(void) const noexcept
                {
                    return raw().begin();
                }

                inline constexpr decltype(auto) cbegin(void) const noexcept
                {
                    return raw().cbegin();
                }

                inline constexpr decltype(auto) end(void) noexcept
                {
                    return raw().end();
                }

                inline constexpr decltype(auto) end(void) const noexcept
                {
                    return raw().end();
                }

                inline constexpr decltype(auto) cend(void) const noexcept
                {
                    return raw().cend();
                }

                inline constexpr decltype(auto) rbegin(void) noexcept
                {
                    return raw().rbegin();
                }

                inline constexpr decltype(auto) rbegin(void) const noexcept
                {
                    return raw().rbegin();
                }

                inline constexpr decltype(auto) crbegin(void) const noexcept
                {
                    return raw().crbegin();
                }

                inline constexpr decltype(auto) rend(void) noexcept
                {
                    return raw().rend();
                }

                inline constexpr decltype(auto) rend(void) const noexcept
                {
                    return raw().rend();
                }

                inline constexpr decltype(auto) crend(void) const noexcept
                {
                    return raw().crend();
                }

            public:
                inline constexpr CLRefType<ShapeType> shape(void) const noexcept
                {
                    return Trait::get_shape(self());
                }

                inline constexpr const usize dimension(void) const noexcept
                {
                    return shape().dimension();
                }

                inline constexpr const usize size(void) const noexcept
                {
                    return shape().size();
                }

                inline constexpr const usize max_size(void) const noexcept
                {
                    return raw().max_size();
                }

                template<typename = void>
                    requires requires (ContainerType& container) { container.reserve(std::declval<usize>()); }
                inline constexpr void reserve(const usize new_capacity)
                {
                    raw().reserve(new_capacity);
                }

                template<typename = void>
                    requires requires (const ContainerType& container) { { container.capacity() } -> DecaySameAs<usize>; }
                inline constexpr const usize capacity(void) const noexcept
                {
                    return raw().capacity();
                }

                template<typename = void>
                    requires requires (ContainerType& container) { container.shrink_to_fit(); }
                inline void shrink_to_fit(void)
                {
                    raw().shrink_to_fit();
                }

            private:
                struct Trait : public Self
                {
                    inline static constexpr const ShapeType& get_shape(const Self& self) noexcept
                    {
                        static const auto get_impl = &Self::OSPF_CRTP_FUNCTION(get_shape);
                        return (self.*get_impl)();
                    }

                    inline static constexpr ContainerType& get_container(Self& self) noexcept
                    {
                        static const auto get_impl = &Self::OSPF_CRTP_FUNCTION(get_container);
                        return (self.*get_impl)();
                    }

                    inline static constexpr const ContainerType& get_const_container(const Self& self) noexcept
                    {
                        static const auto get_impl = &Self::OSPF_CRTP_FUNCTION(get_const_container);
                        return (self.*get_impl)();
                    }

                    inline static constexpr ValueType& get_value(ContainerType& array, const usize i)
                    {
                        static const auto get_impl = &Self::OSPF_CRTP_FUNCTION(get_value);
                        return (*get_impl)(array, i);
                    }

                    inline static constexpr const ValueType& get_const_value(const ContainerType& array, const usize i)
                    {
                        static const auto get_impl = &Self::OSPF_CRTP_FUNCTION(get_const_value);
                        return (*get_impl)(array, i);
                    }
                };
            };
        };
    };
};
