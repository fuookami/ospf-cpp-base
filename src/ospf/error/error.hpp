#pragma once

#include <ospf/concepts.hpp>
#include <ospf/type_family.hpp>
#include <ospf/error/code.hpp>
#include <magic_enum.hpp>
#include <concepts>
#include <optional>
#include <string>

namespace ospf
{
    inline namespace error
    {
        template<typename T>
        concept ErrorType = requires(const T & error)
        {
            requires EnumType<typename T::CodeType>;
            { error.code() } -> EnumType;
            { error.message() } -> DecaySameAs<std::string_view>;
        };

        template<typename T>
        concept ExErrorType = ErrorType<T> && requires(const T& error)
        {
            requires NotSameAs<typename T::ArgType, void>;
            { error.arg() } -> NotSameAs<void>;
        };

        template<typename C>
            requires std::is_enum_v<C>
        class Error
        {
        public:
            using CodeType = C;

        public:
            template<typename = void>
                requires WithDefault<C>
            constexpr Error(void)
                : Error(DefaultValue<C>::value) {}
            constexpr Error(C code)
                : _code(code), _msg(magic_enum::enum_name<C>(code)) {}
            constexpr explicit Error(C code, std::string msg)
                : _code(code), _msg(move<std::string>(msg)) {}
            constexpr Error(const Error& ano) = default;
            constexpr Error(Error&& ano) noexcept = default;
            constexpr Error& operator=(const Error& rhs) = default;
            constexpr Error& operator=(Error&& rhs) noexcept = default;
            constexpr ~Error(void) noexcept = default;

        public:
            inline constexpr const C code(void) const & noexcept
            {
                return _code;
            }

            inline constexpr const std::string_view message(void) const & noexcept
            {
                return _msg;
            }

            inline std::string message(void) && noexcept
            {
                return std::move(_msg);
            }

        private:
            C _code;
            std::string _msg;
        };

        template<typename C, typename T>
            requires std::is_enum_v<C> && NotSameAs<T, void>
        class ExError
            : public Error<C>
        {
        public:
            using typename Error<C>::CodeType;
            using ArgType = T;

        public:
            constexpr ExError(void)
                : Error<C>(), _arg(std::nullopt) {}

            constexpr ExError(C code)
                : Error<C>(code), _arg(std::nullopt) {}

            constexpr explicit ExError(C code, std::string msg)
                : Error<C>(code, move<std::string>(msg)), _arg(std::nullopt) {}

            constexpr explicit ExError(C code, std::string msg, RRefType<T> arg)
                : Error<C>(code, move<std::string>(msg)), _arg(move(arg)) {}

            constexpr explicit ExError(Error<C> error, RRefType<T> arg)
                : Error<C>(std::move(error)), _arg(move(arg)) {}

        public:
            constexpr ExError(const ExError& ano) = default;
            constexpr ExError(ExError&& ano) noexcept = default;
            constexpr ExError& operator=(const ExError& rhs) = default;
            constexpr ExError& operator=(ExError&& rhs) noexcept = default;
            constexpr ~ExError(void) noexcept = default;

        public:
            inline constexpr const std::optional<T>& arg(void) const & noexcept
            {
                return _arg;
            }

            inline std::optional<T> arg(void) && noexcept
            {
                return std::move(_arg);
            }

        private:
            std::optional<T> _arg;
        };

        extern template class Error<OSPFErrCode>;
    };
};

namespace ospf
{
    template<typename C>
        requires std::is_enum_v<C> && WithDefault<C>
    struct DefaultValue<Error<C>>
    {
        static constexpr const Error<C> value = Error<C>{};
    };

    template<typename C, typename T>
        requires std::is_enum_v<C> && NotSameAs<T, void> && WithDefault<C>
    struct DefaultValue<ExError<C, T>>
    {
        static constexpr const ExError<C, T> value = ExError<C, T>{};
    };
};
