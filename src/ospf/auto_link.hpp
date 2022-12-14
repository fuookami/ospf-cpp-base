#include <boost/config.hpp>

#ifdef BOOST_MSVC
#ifdef OPF_DYN_LINK
#define OPF_LIB_PREFIX ""
#else
#define OPF_LIB_PREFIX "lib"
#endif

#ifdef _DEBUG
#define OPF_LIB_SUFFIX "d"
#else
#define OPF_LIB_SUFFIX ""
#endif

#ifndef BOOST_EMBTC_WIN64
#define OPF_LIB_EXTENSION ".lib"
#else
#define OPF_LIB_EXTENSION ".a"
#endif

#ifdef OPF_LIB_EXTENSION
#if defined(OPF_LIB_NAME) && defined(OPF_LIB_PREFIX) && defined(OPF_LIB_SUFFIX) && defined(OPF_LIB_EXTENSION)
#pragma comment(lib, OPF_LIB_PREFIX OPF_LIB_NAME OPF_LIB_SUFFIX OPF_LIB_EXTENSION)
#endif
#endif

#undef OPF_LIB_PREFIX
#undef OPF_LIB_SUFFIX
#undef OPF_LIB_EXTENSION
#endif

#undef OPF_LIB_NAME
