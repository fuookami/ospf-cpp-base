#pragma once

#include <ospf/basic_definition.hpp>
#include <ospf/concepts/base.hpp>
#include <ospf/functional/result.hpp>
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
            { S::dimension_of(std::declval<typename S::VectorViewType>()) } -> DecaySameAs<usize>;
            { shape.shape() } -> DecaySameAs<typename S::VectorViewType>;
            { shape.offset() } -> DecaySameAs<typename S::VectorViewType>;
            { shape.size_of_dimension(std::declval<usize>()) } -> DecaySameAs<Result<usize>>;
            { shape.offset_of_dimension(std::declval<usize>()) } -> DecaySameAs<Result<usize>>;
            { shape.index(std::declval<typename S::VectorViewType>()) } -> DecaySameAs<Result<usize>>;
            { shape.vector(std::declval<usize>()) } -> DecaySameAs<typename S::VectorType>;
            { shape.next_vector(std::declval<typename S::VectorViewType>()) } -> DecaySameAs<bool>;
            { shape.actual_index(std::declval<usize>(), std::declval<isize>()) } -> DecaySameAs<std::optional<usize>>;
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
            using VectorViewType = std::span<const usize, dim>;

        protected:
            constexpr ShapeImpl(void) = default;
        public:
            constexpr ShapeImpl(const ShapeImpl& ano) = default;
            constexpr ShapeImpl(ShapeImpl&& ano) noexcept = default;
            constexpr ShapeImpl& operator=(const ShapeImpl& rhs) = default;
            constexpr ShapeImpl& operator=(ShapeImpl&& rhs) noexcept = default;
            constexpr ~ShapeImpl(void) = default;
            
        public:
            inline constexpr RetType<VectorType> zero(void) const noexcept
            {
                return Trait::zero(self());
            }

            inline constexpr const usize size(void) const noexcept
            {
                return Trait::size(self());
            }

            inline constexpr const usize dimension(void) const noexcept
            {
                return Trait::dimension(self());
            }

            inline constexpr static const usize dimension_of(ArgCLRefType<VectorViewType> vector) noexcept
            {
                return Trait::dimension_of(vector);
            }

            inline constexpr RetType<VectorViewType> shape(void) const noexcept
            {
                return Trait::shape(self());
            }

            inline constexpr RetType<VectorViewType> offset(void) const noexcept
            {
                return Trait::offset(self());
            }

            inline constexpr Result<usize> size_of_dimension(const usize dimension) const noexcept
            {
                if (dimension > this->dimension())
                {
                    return OSPFError{ OSPFErrCode::ApplicationFail, std::format("dimension should be {}, not {}", this->dimension(), dimension) };
                }
                else
                {
                    return this->shape()[dimension];
                }
            }

            inline constexpr Result<usize> offset_of_dimension(const usize dimension) const noexcept
            {
                if (dimension > this->dimension())
                {
                    return OSPFError{ OSPFErrCode::ApplicationFail, std::format("dimension should be {}, not {}", this->dimension(), dimension) };
                }
                else
                {
                    return this->offset()[dimension];
                }
            }

            inline constexpr Result<usize> index(ArgCLRefType<VectorViewType> vector) const noexcept
            {
                if (dimension_of(vector) > dimension())
                {
                    return OSPFError{ OSPFErrCode::ApplicationFail, std::format("dimension should be {}, not {}", this->dimension(), dimension_of(vector)) };
                }
                else
                {
                    usize index{ 0_uz };
                    for (usize i{ 0_uz }, j{ this->dimension() }; i != j; ++i)
                    {
                        if (vector[i] > this->shape()[i])
                        {
                            return OSPFError{ OSPFErrCode::ApplicationFail, std::format("length of dimension {} is {}, but it get {}", i, this->shape()[i], vector[i]) };
                        }
                        index += vector[i] * this->offset()[i];
                    }
                    return index;
                }
            }

            inline constexpr RetType<VectorType> vector(usize index) const noexcept
            {
                auto vector = this->zero();
                for (usize i{ 0_uz }, j{ this->dimension() }; i != j; ++i)
                {
                    const auto offset = this->offset()[i];
                    vector[i] = index / offset;
                    index = index % offset;
                }
                return vector;
            }

            inline constexpr const bool next_vector(LRefType<VectorType> vector) const noexcept
            {
                bool carry{ false };
                vector[this->dimension() - 1_uz] += 1_uz;

                for (usize i{ this->dimension() - 1_uz }; i != npos; --i)
                {
                    if (carry)
                    {
                        vector[i] += 1_uz;
                        carry = false
                    }
                    if (vector[i] == this->shape()[i])
                    {
                        vector[i] = 0_uz;
                        carry = true;
                    }
                }
                return !carry;
            }

            inline constexpr const std::optional<usize> actual_index(const usize dimension, const isize index) const noexcept
            {
                const auto size = static_cast<isize>(this->shape()[dimension]);
                if (index >= size || index < -size)
                {
                    return std::nullopt;
                }
                //tex:$index \in [0, size)$
                else if (index >= 0_iz)
                {
                    return static_cast<usize>(index);
                }
                //tex:$index \in [-size, 0)$
                else
                {
                    return static_cast<usize>(index + size);
                }
            }

        private:
            struct Trait : public Self
            {
                inline static constexpr RetType<VectorType> zero(const Self& self) noexcept
                {
                    static const auto zero_impl = &Self::OSPF_CRTP_FUNCTION(get_zero);
                    return (self.*zero_impl)();
                }

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

                inline static constexpr const usize dimension_of(ArgCLRefType<VectorViewType> vector) noexcept
                {
                    static const auto dimension_impl = &Self::OSPF_CRTP_FUNCTION(get_dimension_of);
                    return (*dimension_impl)(vector);
                }

                inline static constexpr RetType<VectorViewType> shape(const Self& self) noexcept
                {
                    static const auto shape_impl = &Self::OSPF_CRTP_FUNCTION(get_shape);
                    return (self.*shape_impl)();
                }

                inline static constexpr RetType<VectorViewType> offset(const Self& self) noexcept
                {
                    static const auto offset_impl = &Self::OSPF_CRTP_FUNCTION(get_offset);
                    return (self.*offset_impl)();
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
            using VectorViewType = typename Impl::VectorViewType;

        public:
            constexpr Shape<1_uz>(ArgCLRefType<VectorType> shape)
                : _shape(move<VectorType>(shape)), _offset(0_uz), _size(0_uz)
            {
                std::tie(_offset, _size) = offset(_shape)
            }

            constexpr Shape<1_uz>(std::initializer_list<usize> shape)
                : Shape(VectorType{ std::move(shape) }) {}

        public:
            constexpr Shape(const Shape& ano) = default;
            constexpr Shape(Shape&& ano) noexcept = default;
            constexpr Shape& operator=(const Shape& rhs) = default;
            constexpr Shape& operator=(Shape&& rhs) noexcept = default;
            constexpr ~Shape(void) noexcept = default;

        private:
            inline static constexpr std::pair<VectorType, usize> offset(ArgCLRefType<VectorType> shape) noexcept
            {
                VectorType offset{ 0_uz };
                offset.fill(0_uz);
                offset.back() = 1_uz;
                usize size{ 1_uz };
                for (auto i{ shape.size() - 2_uz }; i != npos; --i)
                {
                    offset[i] = offset[i + 1_uz] * shape[i + 1_uz];
                    size *= shape[i + 1];
                }
                size *= shape[0_uz];
                return std::pair(move<VectorType>(offset), size);
            }

        OSPF_CRTP_PERMISSION:
            inline constexpr RetType<VectorType> OSPF_CRTP_FUNCTION(get_zero)(void) const noexcept
            {
                VectorType ret{ 0_uz };
                ret.fill(0_uz);
                return ret;
            }

            inline constexpr const usize OSPF_CRTP_FUNCTION(get_size)(void) const noexcept
            {
                return _size;
            }

            inline constexpr const usize OSPF_CRTP_FUNCTION(get_dimension)(void) const noexcept
            {
                return dim;
            }

            inline constexpr const usize OSPF_CRTP_FUNCTION(get_dimension_of)(ArgCLRefType<VectorViewType> vector) const noexcept
            {
                return dim;
            }

            inline constexpr RetType<VectorViewType> OSPF_CRTP_FUNCTION(get_shape)(void) const noexcept
            {
                return VectorViewType{ _shape };
            }

            inline constexpr RetType<VectorViewType> OSPF_CRTP_FUNCTION(get_offset)(void) const noexcept
            {
                return VectorViewType{ _offset };
            }

        private:
            VectorType _shape;
            VectorType _offset;
            usize _size;
        };

        template<>
        class Shape<1_uz>
            : public ShapeImpl<1_uz, std::array<usize, 1_uz>, Shape<1_uz>>
        {
            using Impl = ShapeImpl<1_uz, std::array<usize, 1_uz>, Shape<1_uz>>;

        public:
            using VectorType = typename Impl::VectorType;
            using VectorViewType = typename Impl::VectorViewType;

        public:
            constexpr Shape<1_uz>(ArgCLRefType<VectorType> shape)
                : _shape(move<VectorType>(shape)) {}
            
            constexpr Shape<1_uz>(const usize shape = 1_uz)
                : _shape(VectorType{ shape }) {}

        public:
            constexpr Shape(const Shape& ano) = default;
            constexpr Shape(Shape&& ano) noexcept = default;
            constexpr Shape& operator=(const Shape& rhs) = default;
            constexpr Shape& operator=(Shape&& rhs) noexcept = default;
            constexpr ~Shape(void) noexcept = default;

        OSPF_CRTP_PERMISSION:
            inline constexpr RetType<VectorType> OSPF_CRTP_FUNCTION(get_zero)(void) const noexcept
            {
                return VectorType{ 0_uz };
            }

            inline constexpr const usize OSPF_CRTP_FUNCTION(get_size)(void) const noexcept
            {
                return _shape[0_uz];
            }

            inline constexpr const usize OSPF_CRTP_FUNCTION(get_dimension)(void) const noexcept
            {
                return 1_uz;
            }

            inline constexpr const usize OSPF_CRTP_FUNCTION(get_dimension_of)(ArgCLRefType<VectorViewType> vector) const noexcept
            {
                return 1_uz;
            }

            inline constexpr RetType<VectorViewType> OSPF_CRTP_FUNCTION(get_shape)(void) const noexcept
            {
                return VectorViewType{ _shape };
            }

            inline constexpr RetType<VectorViewType> OSPF_CRTP_FUNCTION(get_offset)(void) const noexcept
            {
                const auto zero = get_zero();
                return VectorViewType{ zero };
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

        public:
            constexpr Shape(const Shape& ano) = default;
            constexpr Shape(Shape&& ano) noexcept = default;
            constexpr Shape& operator=(const Shape& rhs) = default;
            constexpr Shape& operator=(Shape&& rhs) noexcept = default;
            constexpr ~Shape(void) noexcept = default;
        };

        template<>
        class Shape<dynamic_dimension>
            : public ShapeImpl<dynamic_dimension, std::vector<usize>, Shape<dynamic_dimension>>
        {
            using Impl = ShapeImpl<dynamic_dimension, std::vector<usize>, Shape<dynamic_dimension>>;

        public:
            using VectorType = typename Impl::VectorType;
            using VectorViewType = typename Impl::VectorViewType;

        public:
            constexpr Shape(ArgRRefType<VectorType> vector)
                : _shape(move<VectorType>(vector)), _offset(0_uz, 0_uz), _size(0_uz)
            {
                std::tie(_offset, _size) = offset(_shape);
            }

            template<std::input_iterator It>
                requires requires (const It it) { { *it } -> DecaySameAs<usize>; }
            constexpr Shape(It&& first, It&& last)
                : Shape(VectorType{ std::forward<It>(first), std::forward<It>(last) }) {}

            constexpr Shape(std::initializer_list<usize> vector)
                : Shape(VectorType{ std::move(vector) }) {}

        public:
            constexpr Shape(const Shape& ano) = default;
            constexpr Shape(Shape&& ano) noexcept = default;
            constexpr Shape& operator=(const Shape& rhs) = default;
            constexpr Shape& operator=(Shape&& rhs) noexcept = default;
            constexpr ~Shape(void) = default;

        private:
            inline static constexpr std::pair<VectorType, usize> offset(ArgCLRefType<VectorType> shape) noexcept
            {
                VectorType offset{ shape.size(), 0_uz };
                offset.back() = 1_uz;
                usize size{ 1_uz };
                for (auto i{ shape.size() - 2_uz }; i != npos; --i)
                {
                    offset[i] = offset[i + 1_uz] * shape[i + 1_uz];
                    size *= shape[i + 1];
                }
                size *= shape[0_uz];
                return std::pair(move<VectorType>(offset), size);
            }

        OSPF_CRTP_PERMISSION:
            inline constexpr RetType<VectorType> OSPF_CRTP_FUNCTION(get_zero)(void) const noexcept
            {
                return VectorType{ get_dimension(), 0_uz };
            }

            inline constexpr const usize OSPF_CRTP_FUNCTION(get_size)(void) const noexcept
            {
                return _size;
            }

            inline constexpr const usize OSPF_CRTP_FUNCTION(get_dimension)(void) const noexcept
            {
                return _shape.size();
            }

            inline constexpr const usize OSPF_CRTP_FUNCTION(get_dimension_of)(ArgCLRefType<VectorViewType> vector) const noexcept
            {
                return vector.size();
            }

            inline constexpr RetType<VectorViewType> OSPF_CRTP_FUNCTION(get_shape)(void) const noexcept
            {
                return VectorViewType{ _shape };
            }

            inline constexpr RetType<VectorViewType> OSPF_CRTP_FUNCTION(get_offset)(void) const noexcept
            {
                return VectorViewType{ _offset };
            }

        private:
            VectorType _shape;
            VectorType _offset;
            usize _size;
        };

        using Shape1 = Shape<1_uz>;
        using Shape2 = Shape<2_uz>;
        using Shape3 = Shape<3_uz>;
        using Shape4 = Shape<4_uz>;
        using DynShape = Shape<dynamic_dimension>;

        extern template class Shape<1_uz>;
        extern template class Shape<2_uz>;
        extern template class Shape<3_uz>;
        extern template class Shape<4_uz>;
        extern template class Shape<dynamic_dimension>;
    };
};
