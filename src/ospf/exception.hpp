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


        public:
            inline const E& error(void) const noexcept
            {
                return Trait::error(self());
            }

            inline decltype(auto) code(void) const noexcept
            {
                return error().code();
            }

            inline decltype(auto) message(void) const noexcept
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
                    static const auto impl = OSPF_CRTP_FUNCTION(get_error);
                    return (self.*impl)();
                }
            };
        };
    };

    template<ErrorType E>
    class Exception
        : public exception::Exception<E, Exception<E>>
    {


    private:
        E _error;
    };

    template<ExErrorType E>
    class ExException
        : public exception::Exception<E, ExException<E>>
    {
    public:

    public:
        inline decltype(auto) arg(void) const noexcept
        {
            return _error.arg();
        }

    private:
        E _error;
    };

    extern template class Exception<OSPFError>;

    using OSPFException = Exception<OSPFError>;

    template<typename T>
    using ExOSPFException = ExException<OSPFError, T>;
};
