#pragma once

#include <ospf/data_structure/multi_array/shape.hpp>
#include <ospf/data_structure/multi_array/dummy_index.hpp>
#include <ospf/data_structure/multi_array/map_index.hpp>
#include <ospf/data_structure/reference_array.hpp>

namespace ospf
{
    inline namespace data_structure
    {
        namespace multi_array
        {
            using DummyIndex = dummy_index::DummyIndex;
            using MapIndex = map_index::MapIndex;

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

            protected:
                constexpr MultiArrayImpl(void) = default;
            public:
                constexpr MultiArrayImpl(const MultiArrayImpl& ano) = default;
                constexpr MultiArrayImpl(MultiArrayImpl&& ano) noexcept = default;
                constexpr MultiArrayImpl& operator=(const MultiArrayImpl& rhs) = default;
                constexpr MultiArrayImpl& operator=(MultiArrayImpl&& rhs) noexcept = default;
                constexpr ~MultiArrayImpl(void) noexcept = default;

            public:
                inline LRefType<ValueType> get(const usize index)
                {
                    return Trait::get_value(Trait::get_container(self()), index);
                }

                inline CLRefType<ValueType> get(const usize index) const
                {
                    return Trait::get_const_value(Trait::get_const_container(self()), index);
                }

                inline LRefType<ValueType> get(const VectorType& vector)
                {
                    return Trait::get_value(Trait::get_container(self()), Trait::get_shape(self()).index(vector));
                }

                inline CLRefType<ValueType> get(const VectorType& vector) const
                {
                    return Trait::get_const_value(Trait::get_const_container(self()), Trait::get_shape(self()).index(vector));
                }

                inline LRefType<ValueType> get(const VectorViewType vector)
                {
                    return Trait::get_value(Trait::get_container(self()), Trait::get_shape(self()).index(vector));
                }

                inline CLRefType<ValueType> get(const VectorViewType vector) const
                {
                    return Trait::get_const_value(Trait::get_const_container(self()), Trait::get_shape(self()).index(vector));
                }

                template<typename = void>
                    requires requires (ContainerType& array) { array.reserve(std::declval<usize>()); }
                inline DynRefArray<ValueType> get(const std::span<DummyIndex, dim> dummy_vector)
                {
                    dummy_index::DummyAccessEnumerator<ShapeType> iter{ Trait::get_shape(self()), dummy_vector };
                    DynRefArray<ValueType> ret;
                    ret.reserve(iter.size());
                    while (iter)
                    {
                        const auto vector = *iter;
                        ret.push_back(get(vector));
                        ++iter;
                    }
                }

                // todo

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
