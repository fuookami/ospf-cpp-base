#pragma once

#include <boost/config.hpp>

#ifdef BOOST_MSVC

#if !(defined(OSPF_DYN_LINK) & (defined(USE_OSPF_BASE_LIB) || defined(USE_OSPF_LIB)))
#ifdef _DEBUG
#pragma comment(lib, "cryptoppd.lib")
#else
#pragma comment(lib, "cryptopp.lib")
#endif
#endif

#endif
