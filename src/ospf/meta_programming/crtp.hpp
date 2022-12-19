#pragma once

#include <boost/config.hpp>

#ifndef OSPF_CRTP_PERMISSION
#ifdef BOOST_MSVC
#define OSPF_CRTP_PERMISSION protected
#else
#define OSPF_CRTP_PERMISSION public
#endif
#endif

#ifndef OSPF_CRTP_IMPL
#define OSPF_CRTP_IMPL private:\
    inline Self& self(void) noexcept\
    {\
        return static_cast<Self&>(*this);\
    }\
    inline const Self& self(void) const noexcept\
    {\
    return static_cast<const Self&>(*this);\
    }
#endif

#ifndef OSPF_CRTP_FUNCTION
#ifdef BOOST_MSVC
#define OSPF_CRTP_FUNCTION(F_) &Self::F_
#else
#define OSPF_CRTP_FUNCTION(F_) &Self::_##F_
#endif
#endif
