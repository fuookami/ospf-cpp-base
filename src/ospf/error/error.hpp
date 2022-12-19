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
        template<typename C>
            requires std::is_enum_v<C>
        class Error
        {
        public:
            template<typename T = void>
                requires WithDefault<C>
            constexpr Error()
                : Error(DefaultValue<C>::value) {}
            constexpr Error(C code)
                : _code(code), _msg(magic_enum::enum_name<C>(code)) {}
            constexpr explicit Error(C code, std::string&& msg)
                : _code(code), _msg(std::forward<std::string>(msg)) {}
            constexpr Error(const Error& ano) = default;
            constexpr Error(Error&& ano) noexcept = default;
            constexpr Error& operator=(const Error& rhs) = default;
            constexpr Error& operator=(Error&& rhs) noexcept = default;
            constexpr ~Error(void) noexcept = default;

        public:
            inline constexpr const auto code(void) const noexcept
            {
                return _code;
            }

            inline constexpr const std::string_view message(void) const noexcept
            {
                return _msg;
            }

        private:
            C _code;
            std::string _msg;
        };

        template<typename C, typename T>
            requires std::is_enum_v<C>
        class ExError
            : public Error<C>
        {
        public:
            constexpr ExError()
                : Error<C>(), _arg(std::nullopt) {}
            constexpr ExError(C code)
                : Error<C>(code), _arg(std::nullopt) {}
            constexpr explicit ExError(C code, std::string&& msg)
                : Error<C>(code, std::forward<std::string>(msg)), _arg(std::nullopt) {}
            constexpr explicit ExError(C code, std::string&& msg, RRefType<T> arg)
                : Error<C>(code, std::forward<std::string>(msg)), _arg(move(arg)) {}
            constexpr ExError(const ExError& ano) = default;
            constexpr ExError(ExError&& ano) noexcept = default;
            constexpr ExError& operator=(const ExError& rhs) = default;
            constexpr ExError& operator=(ExError&& rhs) noexcept = default;
            constexpr ~ExError(void) noexcept = default;

        public:


        private:
            std::optional<T> _arg;
        };

        extern template class Error<OSPFErrCode>;
    };
};
