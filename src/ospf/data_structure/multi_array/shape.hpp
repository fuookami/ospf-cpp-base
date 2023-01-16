#pragma once

#include <ospf/basic_definition.hpp>
#include <ospf/concepts/base.hpp>
#include <ospf/literal_constant.hpp>
#include <ospf/meta_programming/crtp.hpp>
#include <ospf/type_family.hpp>
#include <span>

namespace ospf
{
    inline namespace data_structure
    {
        static constexpr const auto dynamic_dimension = std::dynamic_extent;

        template<typename S>
        concept ShapeType = requires (const S& shape)
        {
            { shape.zero() } -> DecaySameAs<typename S::VectorType>;
            { shape.size() } -> DecaySameAs<usize>;
            { shape.dimension() } -> DecaySameAs<usize>;
        };

        template<
            usize dim,
            typename V,
            typename Self
        >
            requires requires (const V& vector) { { vector[std::declval<usize>()] } -> DecaySameAs<usize>; }
        class ShapeImpl
        {
            OSPF_CRTP_IMPL

        public:
            using VectorType = OriginType<V>;

        private:
            struct Trait : public Self
            {
                inline static constexpr const usize size(const Self& self) noexcept
                {
                    static const auto size_impl = &Self::OSPF_CRTP_FUNCTION(get_size);
                    return (self.*size_impl)();
                }

                inline static constexpr const usize dimension(const Self& self) noexcept
                {
                    static const auto dimension_impl = &Self::OSPF_CRTP_FUNCTION(get_dimension);
                    return (self.*dimension_impl)();
                }

                inline static constexpr std::span<usize, dim> shape(const Self& self) noexcept
                {

                }

                inline static constexpr RetType<VectorType> zero(const Self& self) noexcept
                {
                    static const auto zero_impl = &Self::OSPF_CRTP_FUNCTION(get_zero);
                    return (self.*zero_impl)();
                }
            };
        };

        template<usize dim>
        class Shape
            : public ShapeImpl<dim, std::array<usize, dim>, Shape<dim>>
        {
            using Impl = ShapeImpl<dim, std::array<usize, dim>, Shape<dim>>;

        public:
            using VectorType = typename Impl::VectorType;

        OSPF_CRTP_PERMISSION:
            inline static const usize get_dimension(void) noexcept
            {
                return dim;
            }

            inline static RetType<VectorType> get_zero(void) noexcept
            {
                VectorType ret{ 0_uz };
                ret.fill(0_uz);
                return ret;
            }

        private:
            VectorType _shape;
            VectorType _offset;
            usize _size;
        };

        template<>
        class Shape<2_uz>
            : public ShapeImpl<2_uz, std::array<usize, 2_uz>, Shape<2_uz>>
        {
            using Impl = ShapeImpl<2_uz, std::array<usize, 2_uz>, Shape<2_uz>>;

        public:
            using VectorType = typename Impl::VectorType;

        public:
            constexpr Shape(ArgCLRefType<VectorType> shape)
                : _shape(move<VectorType>(shape)) {}

        OSPF_CRTP_PERMISSION:
            inline static const usize get_dimension(void) noexcept
            {
                return 2_uz;
            }

            inline static RetType<VectorType> get_zero(void) noexcept
            {
                return VectorType{ 0_uz, 0_uz };
            }

        private:
            VectorType _shape;
            usize _size;
        };

        template<>
        class Shape<1_uz>
            : public ShapeImpl<1_uz, std::array<usize, 1_uz>, Shape<1_uz>>
        {
            using Impl = ShapeImpl<1_uz, std::array<usize, 1_uz>, Shape<1_uz>>;

        public:
            using VectorType = typename Impl::VectorType;

        public:
            constexpr Shape<1_uz>(ArgCLRefType<VectorType> shape)
                : _shape(move<VectorType>(shape)) {}

        OSPF_CRTP_PERMISSION:
            inline static const usize get_dimension(void) noexcept
            {
                return 1_uz;
            }

            inline static RetType<VectorType> get_zero(void) noexcept
            {
                return VectorType{ 0_uz };
            }

        private:
            VectorType _shape;
        };

        template<>
        class Shape<0_uz>
            : public Shape<1_uz>
        {
        public:
            constexpr Shape(void)
                : Shape<1_uz>({ 1_uz }) {}
        };

        template<>
        class Shape<dynamic_dimension>
            : public ShapeImpl<dynamic_dimension, std::vector<usize>, Shape<dynamic_dimension>>
        {
            using Impl = ShapeImpl<dynamic_dimension, std::vector<usize>, Shape<dynamic_dimension>>;

        public:
            using VectorType = typename Impl::VectorType;

        OSPF_CRTP_PERMISSION:
            inline const usize get_dimension(void) const noexcept
            {
                return _shape.size();
            }

            inline RetType<VectorType> get_zero(void) const noexcept
            {
                return VectorType{ _shape.size(), 0_uz };
            }

        private:
            VectorType _shape;
            VectorType _offset;
            usize _size;
        };
    };
};
