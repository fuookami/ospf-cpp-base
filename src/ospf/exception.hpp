#pragma once

#include <ospf/error.hpp>
#include <ospf/meta_programming/crtp.hpp>

namespace ospf
{
    namespace exception
    {
        template<ErrorType E, typename Self>
        class Exception
            : public std::exception
        {
            OSPF_CRTP_IMPL

        public:
            constexpr Exception(void) noexcept = default;

        public:
            inline const E& error(void) const & noexcept
            {
                return Trait::error(self());
            }

            inline E error(void) && noexcept
            {
                return Trait::error(self());
            }

            inline decltype(auto) code(void) const & noexcept
            {
                return error().code();
            }

            inline const std::string_view message(void) const & noexcept
            {
                return error().message();
            }

            OSPF_BASE_API char const* what() const override
            {
                return message().data();
            }

        private:
            struct Trait : public Self
            {
                inline static const E& error(const Self& self) noexcept
                {
                    static const auto impl = &Self::OSPF_CRTP_FUNCTION(get_error);
                    return (self.*impl)();
                }

                inline static E error(Self&& self) noexcept
                {
                    static const auto impl = &Self::OSPF_CRTP_FUNCTION(get_moved_error);
                    return (self.*impl)();
                }
            };
        };
    };

    template<ErrorType E>
    class Exception
        : public exception::Exception<E, Exception<E>>
    {
    public:
        template<typename T = void>
            requires WithDefault<E>
        constexpr Exception(void)
            : Exception(DefaultValue<E>::value) {}

        constexpr Exception(E error)
            : _error(move<E>(error)) {}

        template<typename... Args>
            requires std::is_constructible_v<E, Args...>
        constexpr Exception(Args&&... args)
            : _error(std::forward<Args>(args)...) {}

    public:
        constexpr Exception(const Exception& ano) = default;
        constexpr Exception(Exception&& ano) noexcept = default;
        constexpr Exception& operator=(const Exception& rhs) = default;
        constexpr Exception& operator=(Exception&& rhs) noexcept = default;
        constexpr ~Exception(void) noexcept = default;

    OSPF_CRTP_PERMISSION:
        inline const E& OSPF_CRTP_FUNCTION(get_error)(void) const & noexcept
        {
            return _error;
        }

        inline E OSPF_CRTP_FUNCTION(get_moved_error)(void) && noexcept
        {
            return std::move(_error);
        }

    private:
        E _error;
    };

    template<ExErrorType E>
    class ExException
        : public exception::Exception<E, ExException<E>>
    {
    public:
        template<typename T = void>
            requires WithDefault<E>
        constexpr ExException(void)
            : ExException(DefaultValue<E>::value) {}

        constexpr ExException(E error)
            : _error(move<E>(error)) {}

        template<typename... Args>
            requires std::is_constructible_v<E, Args...>
        constexpr ExException(Args&&... args)
            : _error(std::forward<Args>(args)...) {}

    public:
        constexpr ExException(const ExException& ano) = default;
        constexpr ExException(ExException&& ano) noexcept = default;
        constexpr ExException& operator=(const ExException& rhs) = default;
        constexpr ExException& operator=(ExException&& rhs) noexcept = default;
        constexpr ~ExException(void) noexcept = default;

    public:
        inline decltype(auto) arg(void) const & noexcept
        {
            return _error.arg();
        }

        inline decltype(auto) arg(void) && noexcept
        {
            return _error.arg();
        }

    OSPF_CRTP_PERMISSION:
        inline const E& OSPF_CRTP_FUNCTION(get_error)(void) const & noexcept
        {
            return _error;
        }

        inline E OSPF_CRTP_FUNCTION(get_moved_error)(void) && noexcept
        {
            return std::move(_error);
        }

    private:
        E _error;
    };

    extern template class Exception<OSPFError>;

    using OSPFException = Exception<OSPFError>;

    template<typename T>
    using ExOSPFException = ExException<ExOSPFError<T>>;
};

template<ospf::ErrorType E>
    requires ospf::WithDefault<E>
struct ospf::DefaultValue<ospf::Exception<E>>
{
    static constexpr const Exception<E> value = Exception<E>{};
};

template<ospf::ExErrorType E>
    requires ospf::WithDefault<E>
struct ospf::DefaultValue<ospf::Exception<E>>
{
    static constexpr const ExException<E> value = ExException<E>{};
};
