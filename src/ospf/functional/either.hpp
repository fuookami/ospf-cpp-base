#pragma once

#include <ospf/basic_definition.hpp>
#include <ospf/concepts.hpp>
#include <ospf/literal_constant.hpp>
#include <ospf/memory/reference.hpp>
#include <ospf/type_family.hpp>
#include <optional>
#include <variant>

namespace ospf
{
    inline namespace functional
    {
        template<typename T, typename U>
            requires NotSameAs<OriginType<T>, void> || NotSameAs<OriginType<U>, void>
        class Either
        {
        public:
            using LeftType = OriginType<T>;
            using RightType = OriginType<U>;

            static_assert(NotSameAs<LeftType, RightType>, "Either<T, U> requires T is not same as U.");

        public:
            constexpr Either(CLRefType<LeftType> left_value)
                : _variant(left_value) {}

            template<typename = void>
                requires ReferenceFaster<LeftType> && std::movable<LeftType>
            Either(RRefType<LeftType> left_value)
                : _variant(move<LeftType>(left_value)) {}

            constexpr Either(CLRefType<RightType> right_value)
                : _variant(right_value) {}

            template<typename = void>
                requires ReferenceFaster<LeftType> && std::movable<LeftType>
            Either(RRefType<RightType> right_value)
                : _variant(move<RightType>(right_value)) {}

            constexpr Either(const Either& ano) = default;
            constexpr Either(Either&& ano) noexcept = default;

        public:
            constexpr Either& operator=(const Either& rhs) = default;
            constexpr Either& operator=(Either&& rhs) noexcept = default;

            constexpr Either& operator=(CLRefType<LeftType> left_value) noexcept
            {
                _variant.template emplace<0_uz>(left_value);
                return *this;
            }

            template<typename = void>
                requires ReferenceFaster<LeftType> && std::movable<LeftType>
            Either& operator=(RRefType<LeftType> left_value) noexcept
            {
                _variant.template emplace<0_uz>(move<LeftType>(left_value));
                return *this;
            }

            constexpr Either& operator=(CLRefType<RightType> right_value) noexcept
            {
                _variant.template emplace<1_uz>(right_value);
                return *this;
            }

            template<typename = void>
                requires ReferenceFaster<RightType> && std::movable<RightType>
            Either& operator=(RRefType<RightType> right_value) noexcept
            {
                _variant.template emplace<1_uz>(move<RightType>(right_value));
                return *this;
            }

        public:
            constexpr ~Either(void) noexcept = default;

        public:
            inline constexpr operator std::variant<LeftType, RightType>& (void) noexcept
            {
                return _variant;
            }

            inline constexpr operator const std::variant<LeftType, RightType>& (void) const noexcept
            {
                return _variant;
            }

        public:
            inline constexpr const bool is_left(void) const noexcept
            {
                return _variant.index() == 0_uz;
            }

            inline constexpr const bool is_right(void) const noexcept
            {
                return _variant.index() == 1_uz;
            }

        public:
            inline constexpr LeftType& left(void) &
            {
                return std::get<0_uz>(_variant);
            }

            inline constexpr const LeftType& left(void) const &
            {
                return std::get<0_uz>(_variant);
            }

            inline RetType<LeftType> left(void) &&
            {
                return move<LeftType>(std::get<0_uz>(_variant));
            }

            inline constexpr std::optional<Ref<LeftType>> left_if_is(void) & noexcept
            {
                if (!is_left())
                {
                    return std::nullopt;
                }
                else
                {
                    return Ref<LeftType>{ std::get<0_uz>(_variant) };
                }
            }

            inline constexpr std::optional<const Ref<LeftType>> left_if_is(void) const & noexcept
            {
                if (!is_left())
                {
                    return std::nullopt;
                }
                else
                {
                    return Ref<LeftType>{ std::get<0_uz>(_variant) };
                }
            }

            inline std::optional<LeftType> left_if_is(void) && noexcept
            {
                if (!is_left())
                {
                    return std::nullopt;
                }
                else
                {
                    return move<LeftType>(std::get<0_uz>(_variant));
                }
            }

            template<typename Func>
            inline constexpr decltype(auto) left_then(Func&& func) const & noexcept
            {
                using RetType = Either<OriginType<std::invoke_result_t<Func, LeftType>>, RightType>;

                if (is_left())
                {
                    return RetType{ std::forward<Func>(func)(std::get<0_uz>(_variant)) };
                }
                else
                {
                    return RetType{ std::get<1_uz>(_variant) };
                }
            }

            template<typename Func>
            inline decltype(auto) left_then(Func&& func) && noexcept
            {
                using RetType = Either<OriginType<std::invoke_result_t<Func, LeftType>>, RightType>;

                if (is_left())
                {
                    return RetType{ std::forward<Func>(func)(move<LeftType>(std::get<0_uz>(_variant))) };
                }
                else
                {
                    return RetType{ move<RightType>(std::get<1_uz>(_variant)) };
                }
            }

            inline constexpr RetType<LeftType> left_or(CLRefType<LeftType> other) const & noexcept
            {
                if (is_left())
                {
                    return std::get<0_uz>(_variant);
                }
                else
                {
                    return other;
                }
            }

            template<typename = void>
                requires ReferenceFaster<LeftType> && std::movable<LeftType>
            inline RetType<LeftType> left_or(CLRefType<LeftType> other) && noexcept
            {
                if (is_left())
                {
                    return move<LeftType>(std::get<0_uz>(_variant));
                }
                else
                {
                    return other;
                }
            }

            template<typename = void>
                requires ReferenceFaster<LeftType> && std::movable<LeftType>
            inline RetType<LeftType> left_or(RRefType<LeftType> other) const & noexcept
            {
                if (is_left())
                {
                    return std::get<0_uz>(_variant);
                }
                else
                {
                    return move<LeftType>(other);
                }
            }

            template<typename = void>
                requires ReferenceFaster<LeftType> && std::movable<LeftType>
            inline RetType<LeftType> left_or(RRefType<LeftType> other) && noexcept
            {
                if (is_left())
                {
                    return move<LeftType>(std::get<0_uz>(_variant));
                }
                else
                {
                    return move<LeftType>(other);
                }
            }

            template<typename = void>
                requires WithDefault<LeftType>
            inline constexpr RetType<LeftType> left_or_default(void) const & noexcept
            {
                if (is_left())
                {
                    return std::get<0_uz>(_variant);
                }
                else
                {
                    return DefaultValue<LeftType>::value;
                }
            }

            template<typename = void>
                requires WithDefault<LeftType> && ReferenceFaster<LeftType> && std::movable<LeftType>
            inline RetType<LeftType> left_or_default(void) && noexcept
            {
                if (is_left())
                {
                    return move<LeftType>(std::get<0_uz>(_variant));
                }
                else
                {
                    return DefaultValue<LeftType>::value;
                }
            }

            template<typename Func>
                requires DecaySameAs<std::invoke_result_t<Func, RightType>, LeftType>
            inline constexpr RetType<LeftType> left_or_else(Func&& func) const & noexcept
            {
                if (is_left())
                {
                    return std::get<0_uz>(_variant);
                }
                else
                {
                    return std::forward<Func>(func)(std::get<1_uz>(_variant));
                }
            }

            template<typename Func>
                requires DecaySameAs<std::invoke_result_t<Func, RightType>, LeftType>
            inline RetType<LeftType> left_or_else(Func&& func) && noexcept
            {
                if (is_left())
                {
                    return move<LeftType>(std::get<0_uz>(_variant));
                }
                else
                {
                    return std::forward<Func>(func)(move<RightType>(std::get<1_uz>(_variant)));
                }
            }

        public:
            inline constexpr RightType& right(void) &
            {
                return std::get<1_uz>(_variant);
            }

            inline constexpr const RightType& right(void) const &
            {
                return std::get<1_uz>(_variant);
            }

            inline RetType<RightType> right(void) &&
            {
                return move<RightType>(std::get<1_uz>(_variant));
            }

            inline constexpr std::optional<Ref<RightType>> right_if_is(void) & noexcept
            {
                if (!is_right())
                {
                    return std::nullopt;
                }
                else
                {
                    return Ref<RightType>{ std::get<1_uz>(_variant) };
                }
            }

            inline constexpr std::optional<const Ref<RightType>> right_if_is(void) const & noexcept
            {
                if (!is_right())
                {
                    return std::nullopt;
                }
                else
                {
                    return Ref<RightType>{ std::get<1_uz>(_variant) };
                }
            }

            inline std::optional<RightType> right_if_is(void) && noexcept
            {
                if (!is_right())
                {
                    return std::nullopt;
                }
                else
                {
                    return move<RightType>(std::get<1_uz>(_variant));
                }
            }

            template<typename Func>
            inline constexpr decltype(auto) right_then(Func&& func) const & noexcept
            {
                using RetType = Either<LeftType, OriginType<std::invoke_result_t<Func, RightType>>>;

                if (is_right())
                {
                    return RetType{ std::forward<Func>(func)(std::get<1_uz>(_variant)) };
                }
                else
                {
                    return RetType{ std::get<0_uz>(_variant) };
                }
            }

            template<typename Func>
            inline decltype(auto) right_then(Func&& func) && noexcept
            {
                using RetType = Either<LeftType, OriginType<std::invoke_result_t<Func, RightType>>>;

                if (is_right())
                {
                    return RetType{ std::forward<Func>(func)(move<RightType>(std::get<1_uz>(_variant))) };
                }
                else
                {
                    return RetType{ move<LeftType>(std::get<0_uz>(_variant)) };
                }
            }

            inline constexpr RetType<RightType> right_or(CLRefType<RightType> other) const & noexcept
            {
                if (is_right())
                {
                    return std::get<1_uz>(_variant);
                }
                else
                {
                    return other;
                }
            }

            template<typename = void>
                requires ReferenceFaster<RightType> && std::movable<RightType>
            inline RetType<RightType> right_or(CLRefType<RightType> other) && noexcept
            {
                if (is_right())
                {
                    return move<RightType>(std::get<1_uz>(_variant));
                }
                else
                {
                    return other;
                }
            }

            template<typename = void>
                requires ReferenceFaster<RightType> && std::movable<RightType>
            inline RetType<RightType> right_or(RRefType<RightType> other) const & noexcept
            {
                if (is_right())
                {
                    return std::get<1_uz>(_variant);
                }
                else
                {
                    return move<RightType>(other);
                }
            }

            template<typename = void>
                requires ReferenceFaster<RightType> && std::movable<RightType>
            inline RetType<RightType> right_or(RRefType<RightType> other) && noexcept
            {
                if (is_right())
                {
                    return move<RightType>(std::get<1_uz>(_variant));
                }
                else
                {
                    return move<RightType>(other);
                }
            }

            template<typename = void>
                requires WithDefault<RightType>
            inline constexpr RetType<RightType> right_or_default(void) const & noexcept
            {
                if (is_right())
                {
                    return std::get<1_uz>(_variant);
                }
                else
                {
                    return DefaultValue<RightType>::value;
                }
            }

            template<typename = void>
                requires WithDefault<RightType> && ReferenceFaster<RightType> && std::movable<RightType>
            inline constexpr RetType<RightType> right_or_default(void) && noexcept
            {
                if (is_right())
                {
                    return move<RightType>(std::get<1_uz>(_variant));
                }
                else
                {
                    return DefaultValue<RightType>::value;
                }
            }

            template<typename Func>
                requires DecaySameAs<std::invoke_result_t<Func, LeftType>, RightType>
            inline constexpr RetType<RightType> right_or_else(Func&& func) const & noexcept
            {
                if (is_right())
                {
                    return std::get<1_uz>(_variant);
                }
                else
                {
                    return std::forward<Func>(func)(std::get<0_uz>(_variant));
                }
            }

            template<typename Func>
                requires DecaySameAs<std::invoke_result_t<Func, LeftType>, RightType>
            inline RetType<RightType> right_or_else(Func&& func) && noexcept
            {
                if (is_right())
                {
                    return move<RightType>(std::get<1_uz>(_variant));
                }
                else
                {
                    return std::forward<Func>(func)(move<LeftType>(std::get<0_uz>(_variant)));
                }
            }

        public:
            template<typename Func>
            inline constexpr decltype(auto) visit(Func&& func) noexcept
            {
                return std::visit(std::forward<Func>(func), _variant);
            }

            template<typename Func>
            inline constexpr decltype(auto) visit(Func&& func) const noexcept
            {
                return std::visit(std::forward<Func>(func), _variant);
            }

        public:
            inline constexpr void reset(CLRefType<LeftType> left_value) noexcept
            {
                _variant.template emplace<0_uz>(left_value);
            }

            template<typename = void>
                requires ReferenceFaster<LeftType>&& std::movable<LeftType>
            inline void reset(RRefType<LeftType> left_value) noexcept
            {
                _variant.template emplace<0_uz>(move<LeftType>(left_value));
            }

            inline constexpr void reset(CLRefType<RightType> right_value) noexcept
            {
                _variant.template emplace<1_uz>(right_value);
            }

            template<typename = void>
                requires ReferenceFaster<RightType>&& std::movable<RightType>
            inline void reset(RRefType<RightType> right_value) noexcept
            {
                _variant.template emplace<1_uz>(move<RightType>(right_value));
            }

            template<typename... Args>
                requires std::is_constructible_v<LeftType, Args...> && !std::is_constructible_v<RightType, Args...>
            inline constexpr LeftType& emplace(Args&&... args) noexcept
            {
                return _variant.template emplace<0_uz>(LeftType{ std::forward<Args>(args)... });
            }

            template<typename... Args>
                requires std::is_constructible_v<RightType, Args...> && !std::is_constructible_v<LeftType, Args...>
            inline constexpr RightType& emplace(Args&&... args) noexcept
            {
                return _variant.template emplace<1_uz>(RightType{ std::forward<Args>(args)... });
            }

            inline void swap(const Either<T, U>& other) noexcept
            {
                std::swap(_variant, other._variant);
            }

        public:
            inline constexpr const bool operator==(const Either<T, U>& rhs) const noexcept
            {
                return _variant == rhs._variant;
            }

            inline constexpr const bool operator!=(const Either<T, U>& rhs) const noexcept
            {
                return _variant != rhs._variant;
            }

            inline constexpr const bool operator<(const Either<T, U>& rhs) const noexcept
            {
                return _variant < rhs._variant;
            }

            inline constexpr const bool operator<=(const Either<T, U>& rhs) const noexcept
            {
                return _variant <= rhs._variant;
            }

            inline constexpr const bool operator>(const Either<T, U>& rhs) const noexcept
            {
                return _variant > rhs._variant;
            }

            inline constexpr const bool operator>=(const Either<T, U>& rhs) const noexcept
            {
                return _variant >= rhs._variant;
            }

            inline constexpr decltype(auto) operator<=>(const Either<T, U>& rhs) const noexcept
            {
                return _variant <=> rhs._variant;
            }

        private:
            std::variant<LeftType, RightType> _variant;
        };
    };
};

namespace std
{
    template<typename T, typename U>
    struct hash<ospf::Either<T, U>>
    {
        inline const ospf::usize operator()(const ospf::Either<T, U>& either) const noexcept
        {
            return either.visit([](const auto& ele)
                {
                    static constexpr const auto hasher = std::hash<ospf::OriginType<decltype(ele)>>{ };
                    return hasher(ele);
                });
        }
    };

    template<typename T, typename U, typename CharT>
    struct formatter<ospf::Either<T, U>, CharT> : formatter<string_view, CharT>
    {
        template<typename FormatContext>
        inline static decltype(auto) format(const ospf::Either<T, U>& either, FormatContext& fc)
        {
            return either.visit([](const auto& ele)
                {
                    return formatter<ospf::OriginType<decltype(ele)>, CharT>::format(ele, fc);
                });
        }
    };

    template<typename T, typename U>
    inline void swap(ospf::Either<T, U>& lhs, ospf::Either<T, U>& rhs) noexcept
    {
        lhs.swap(rhs);
    }
};

namespace ospf
{
    template<typename T, typename U>
        requires WithTag<T> && WithTag<U> 
            && std::is_same_v<typename TagValue<T>::Type, typename TagValue<U>::Type>
    struct TagValue<Either<T, U>>
    {
        using Type = typename TagValue<T>::Type;

        inline RetType<Type> operator()(const Either<T, U>& either) const noexcept
        {
            return either.visit([](const auto& ele)
                {
                    static constexpr const auto extractor = TagValue<OriginType<decltype(ele)>>{ };
                    return extractor(ele);
                });
        }
    };
};
