#pragma once

#include <ospf/data_structure/multi_array/impl.hpp>

namespace ospf
{
    inline namespace data_structure
    {
        namespace multi_array
        {
            template<
                typename T,
                usize dim
            >
                requires (dim != dynamic_dimension)
            class MultiArrayMapView
                : public MultiArrayImpl<DynRefArray<OriginType<T>>, std::vector<DynRefArray<OriginType<T>>>, Shape<dim>, MultiArrayMapView<dim, T>>
            {
                using Impl = MultiArrayImpl<DynRefArray<OriginType<T>>, std::vector<DynRefArray<OriginType<T>>>, Shape<dim>, MultiArrayMapView<dim, T>>;

                template<
                    typename T,
                    usize dim
                >
                friend class MultiArray;

                template<
                    typename T,
                    usize dim
                >
                friend class MultiArrayView;

            public:
                using ValueType = typename Impl::ValueType;
                using ContainerType = typename Impl::ContainerType;
                using ShapeType = typename Impl::ShapeType;
                using VectorType = typename Impl::VectorType;
                using VectorViewType = typename Impl::VectorViewType;
                using DummyVectorType = typename Impl::DummyVectorType;
                using DummyVectorViewType = typename Impl::DummyVectorViewType;

                template<usize to_dim>
                using MapVectorType = map_index::MapVector<dim, to_dim>;

            private:
                constexpr MultiArrayMapView(ArgRRefType<ShapeType> shape, VectorType container)
                    : _shape(move<ShapeType>(shape)), _container(std::move(container)) {}

            public:
                constexpr MultiArrayMapView(const MultiArrayMapView& ano) = default;
                constexpr MultiArrayMapView(MultiArrayMapView&& ano) noexcept = default;
                constexpr MultiArrayMapView& operator=(const MultiArrayMapView& rhs) = default;
                constexpr MultiArrayMapView& operator=(MultiArrayMapView&& rhs) noexcept = default;
                constexpr ~MultiArrayMapView(void) noexcept = default;

            public:
                using Impl::get;

                template<usize to_dim>
                    requires (to_dim < dim) && (to_dim != 0_uz)
                inline constexpr decltype(auto) get(const MapVectorType<to_dim>& vector) const
                {
                    auto [shape, container] = this->map<DynRefArray<DynRefArray<OriginType<T>>>>(vector);
                    return MultiArrayMapView<T, to_dim>{ std::move(shape), std::move(container) };
                }

            public:
                using Impl::operator();

                // todo: use operator[...] to replace operator(...) in C++23

                template<typename... Args>
                    requires is_map_vector<Args...> && !is_dummy_vector<Args...> && !is_normal_vector<Args...>\
                inline constexpr decltype(auto) operator()(Args&&... args) const
                {
                    return get(map_vector(std::forward<Args>(args)...));
                }

            public:
                using Impl::operator[];

                template<usize to_dim>
                    requires (to_dim < dim) && (to_dim != 0_uz)
                inline constexpr decltype(auto) operator[](const MapVectorType<to_dim>& vector) const
                {
                    return get(vector);
                }

            OSPF_CRTP_PERMISSION:
                inline constexpr CLRefType<ShapeType> OSPF_CRTP_FUNCTION(get_shape)(void) const noexcept
                {
                    return _shape;
                }

                inline constexpr LRefType<ContainerType> OSPF_CRTP_FUNCTION(get_container)(void) noexcept
                {
                    return _container;
                }

                inline constexpr CLRefType<ContainerType> OSPF_CRTP_FUNCTION(get_const_container)(void) const noexcept
                {
                    return _container;
                }

                inline static constexpr LRefType<ValueType> OSPF_CRTP_FUNCTION(get_value)(LRefType<ContainerType>& array, const usize i) noexcept
                {
                    return array[i];
                }

                inline static constexpr CLRefType<ValueType> OSPF_CRTP_FUNCTION(get_const_value)(CLRefType<ContainerType>& array, const usize i) noexcept
                {
                    return array[i];
                }

            private:
                ShapeType _shape;
                ContainerType _container;
            };
        };
    };
};
