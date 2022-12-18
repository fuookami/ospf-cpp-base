#pragma once

#include <boost/config.hpp>

#ifndef OSPF_CRTP_PERMISSION
#ifdef BOOST_MSVC
#define OSPF_CRTP_PERMISSION protected
#else
#define OSPF_CRTP_PERMISSION public
#endif
#endif

#ifndef OSPF_CRTP_FUNCTION
#ifdef BOOST_MSVC
#define OSPF_CRTP_FUNCTION(F_) F_
#else
#define OSPF_CRTP_FUNCTION(F_) _##F_
#endif
#endif
