#pragma once

#include <ospf/error.hpp>
#include <ospf/functional/either.hpp>

namespace ospf
{
    inline namespace functional
    {
        struct Succeed 
        {
        public:
            inline constexpr const bool operator==(const Succeed _) const noexcept
            {
                return true;
            }

            inline constexpr const bool operator!=(const Succeed _) const noexcept
            {
                return false;
            }

        public:
            inline constexpr const std::strong_ordering operator<=>(const Succeed _) const noexcept
            {
                return std::strong_ordering::equal;
            }
        };
        static constexpr const auto succeed = Succeed{};

        template<typename T = Succeed, ErrorType E = OSPFError>
        class Result
        {
        public:
            using RetType = OriginType<T>;
            using ErrType = OriginType<E>;
            using EitherType = Either<RetType, ErrType>;

        public:
            // todo: succeeded, failed

        public:
            constexpr Result(CLRefType<RetType> ret_value)
                : _either(ret_value) {}

            template<typename = void>
                requires ReferenceFaster<RetType> && std::movable<RetType>
            Result(RRefType<RetType> ret_value)
                : _either(move<RetType>(ret_value)) {}

            constexpr Result(CLRefType<ErrType> err_value)
                : _either(err_value) {}

            template<typename = void>
                requires ReferenceFaster<ErrType> && std::movable<ErrType>
            Result(RRefType<ErrType> err_value)
                : _either(move<ErrType>(err_value)) {}

            constexpr Result(const Result<T, E>& ano) = default;
            constexpr Result(Result<T, E>&& ano) noexcept = default;

        public:
            constexpr Result& operator=(const Result<T, E>& rhs) = default;
            constexpr Result& operator=(Result<T, E>&& rhs) noexcept = default;

            constexpr Result& operator=(CLRefType<RetType> ret_value) noexcept
            {
                _either.reset(ret_value);
                return *this;
            }

            template<typename = void>
                requires ReferenceFaster<RetType> && std::movable<RetType>
            Result& operator=(RRefType<RetType> ret_value) noexcept
            {
                _either.reset(move<RetType>(ret_value));
                return *this;
            }

            constexpr Result& operator=(CLRefType<ErrType> err_value) noexcept
            {
                _either.reset(err_value);
                return *this;
            }

            template<typename = void>
                requires ReferenceFaster<ErrType> && std::movable<ErrType>
            Result& operator=(RRefType<ErrType> err_value) noexcept
            {
                _either.reset(move<ErrType>(err_value));
                return *this;
            }

        public:
            constexpr ~Result(void) noexcept = default;

        public:
            inline constexpr operator Either<RetType, ErrType>& (void) noexcept
            {
                return _either;
            }

            inline constexpr operator const Either<RetType, ErrType>& (void) const noexcept
            {
                return _either;
            }

            inline constexpr operator std::variant<RetType, ErrType>& (void) noexcept
            {
                return static_cast<std::variant<RetType, ErrType>&>(_either);
            }

            inline constexpr operator const std::variant<RetType, ErrType>& (void) const noexcept
            {
                return static_cast<const std::variant<RetType, ErrType>&>(_either);
            }

        public:
            inline constexpr const bool is_succeeded(void) const noexcept
            {
                return _either.is_left();
            }

            inline constexpr const bool is_failed(void) const noexcept
            {
                return _either.is_right();
            }

        public:
            inline constexpr RetType& unwrap(void) &
            {
                return _either.left();
            }

            inline constexpr const RetType& unwrap(void) const &
            {
                return _either.left();
            }

            inline ospf::RetType<RetType> unwrap(void) &&
            {
                return static_cast<EitherType&&>(_either).left();
            }

            inline constexpr std::optional<Ref<RetType>> unwrap_if_succeeded(void) & noexcept
            {
                return _either.left_if_is();
            }

            inline constexpr std::optional<const Ref<RetType>> unwrap_if_succeeded(void) const & noexcept
            {
                return _either.left_if_is();
            }

            inline std::optional<RetType> unwrap_if_succeeded(void) && noexcept
            {
                return static_cast<EitherType&&>(_either).left_if_is();
            }

            template<typename Func>
            inline constexpr decltype(auto) succeeded_then(Func&& func) const & noexcept
            {
                return _either.left_then(std::forward<Func>(func));
            }

            template<typename Func>
            inline decltype(auto) succeeded_then(Func&& func) && noexcept
            {
                return static_cast<EitherType&&>(_either).left_then(std::forward<Func>(func));
            }

            inline constexpr ospf::RetType<RetType> unwrap_or(CLRefType<RetType> other) const & noexcept
            {
                return _either.left_or(other);
            }

            template<typename = void>
                requires ReferenceFaster<RetType> && std::movable<RetType>
            inline ospf::RetType<RetType> unwrap_or(CLRefType<RetType> other) && noexcept
            {
                return static_cast<EitherType&&>(_either).left_or(other);
            }

            template<typename = void>
                requires ReferenceFaster<RetType> && std::movable<RetType>
            inline ospf::RetType<RetType> unwrap_or(RRefType<RetType> other) const & noexcept
            {
                return _either.left_or(move<RetType>(other));
            }

            template<typename = void>
                requires ReferenceFaster<RetType> && std::movable<RetType>
            inline ospf::RetType<RetType> unwrap_or(RRefType<RetType> other) && noexcept
            {
                return static_cast<EitherType&&>(_either).left_or(move<RetType>(other));
            }

            template<typename = void>
                requires WithDefault<RetType>
            inline ospf::RetType<RetType> unwrap_or_default(void) const & noexcept
            {
                return _either.left_or_default();
            }

            template<typename = void>
                requires WithDefault<RetType> && ReferenceFaster<RetType> && std::movable<RetType>
            inline ospf::RetType<RetType> unwrap_or_default(void) && noexcept
            {
                return static_cast<EitherType&&>(_either).left_or_default();
            }

            template<typename Func>
                requires DecaySameAs<std::invoke_result_t<Func, ErrType>, RetType>
            inline ospf::RetType<RetType> unwrap_or_else(Func&& func) const & noexcept
            {
                return _either.left_or_else(std::forward<Func>(func));
            }

            template<typename Func>
                requires DecaySameAs<std::invoke_result_t<Func, ErrType>, RetType>
            inline ospf::RetType<RetType> unwrap_or_else(Func&& func) && noexcept
            {
                return static_cast<EitherType&&>(_either).left_or_else(std::forward<Func>(func));
            }

        public:
            inline constexpr ErrType& err(void) &
            {
                return _either.right();
            }

            inline constexpr const ErrType& err(void) const &
            {
                return _either.right();
            }

            inline ospf::RetType<ErrType> err(void) &&
            {
                return static_cast<EitherType&&>(_either).right();
            }

            inline constexpr std::optional<Ref<ErrType>> err_if_is(void) & noexcept
            {
                return _either.right_if_is();
            }

            inline constexpr std::optional<const Ref<ErrType>> err_if_is(void) const & noexcept
            {
                return _either.right_if_is();
            }

            inline std::optional<ErrType> err_if_is(void) && noexcept
            {
                return static_cast<EitherType&&>(_either).right_if_is();
            }

            template<typename Func>
            inline constexpr decltype(auto) err_then(Func&& func) const & noexcept
            {
                return _either.right_then(std::forward<Func>(func));
            }

            template<typename Func>
            inline decltype(auto) err_then(Func&& func) && noexcept
            {
                return static_cast<EitherType&&>(_either).right_then(std::forward<Func>(func));
            }

        public:
            template<typename Func>
            inline constexpr decltype(auto) visit(Func&& func) noexcept
            {
                return _either.visit(std::forward<Func>(func));
            }

            template<typename Func>
            inline constexpr decltype(auto) visit(Func&& func) const noexcept
            {
                return _either.visit(std::forward<Func>(func));
            }

        public:
            inline constexpr void reset(CLRefType<RetType> ret_value) noexcept
            {
                _either.reset(ret_value);
            }

            template<typename = void>
                requires ReferenceFaster<RetType>&& std::movable<RetType>
            inline void reset(RRefType<RetType> ret_value) noexcept
            {
                _either.reset(move<RetType>(ret_value));
            }

            inline constexpr void reset(CLRefType<ErrType> err_value) noexcept
            {
                _either.reset(err_value);
            }

            template<typename = void>
                requires ReferenceFaster<ErrType>&& std::movable<ErrType>
            inline void reset(RRefType<ErrType> err_value) noexcept
            {
                _either.reset(move<ErrType>(err_value));
                return *this;
            }

            template<typename... Args>
            inline constexpr decltype(auto) emplace(Args&&... args) noexcept
            {
                return _either.emplace(std::forward<Args>(args)...);
            }

            inline void swap(Result& other) noexcept
            {
                std::swap(_either, other._either);
            }

         public:
            inline constexpr const bool operator==(const Result& rhs) const noexcept
            {
                return unwrap_if_succeeded() == rhs.unwrap_if_succeeded();
            }

            inline constexpr const bool operator!=(const Result& rhs) const noexcept
            {
                return unwrap_if_succeeded() != rhs.unwrap_if_succeeded();
            }

        public:
            inline constexpr const bool operator<(const Result& rhs) const noexcept
            {
                return unwrap_if_succeeded() < rhs.unwrap_if_succeeded();
            }

            inline constexpr const bool operator<=(const Result& rhs) const noexcept
            {
                return unwrap_if_succeeded() <= rhs.unwrap_if_succeeded();
            }

            inline constexpr const bool operator>(const Result& rhs) const noexcept
            {
                return unwrap_if_succeeded() > rhs.unwrap_if_succeeded();
            }

            inline constexpr const bool operator>=(const Result& rhs) const noexcept
            {
                return unwrap_if_succeeded() >= rhs.unwrap_if_succeeded();
            }

        public:
            inline constexpr decltype(auto) operator<=>(const Result& rhs) const noexcept
            {
                return const_cast<Result&>(*this).unwrap_if_succeeded() <=> const_cast<Result&>(rhs).unwrap_if_succeeded();
            }

        private:
            EitherType _either;
        };

        template<ErrorType E = OSPFError>
        using Try = Result<Succeed, E>;

        extern template class Result<Succeed, OSPFError>;
    };
};

namespace std
{
    template<typename T, ospf::ErrorType E>
    inline void swap(ospf::Result<T, E>& lhs, ospf::Result<T, E>& rhs) noexcept
    {
        lhs.swap(rhs);
    }
};
