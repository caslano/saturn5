#ifndef BOOST_METAPARSE_CONFIG_HPP
#define BOOST_METAPARSE_CONFIG_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

/*
 * Compiler workarounds
 */

// BOOST_NO_CXX11_CONSTEXPR is not defined in gcc 4.6
#if \
  defined BOOST_NO_CXX11_CONSTEXPR || defined BOOST_NO_CONSTEXPR || ( \
    !defined __clang__ && defined __GNUC__ \
    && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 7)) \
  )

#  define BOOST_NO_CONSTEXPR_C_STR

#endif

/*
 * C++ standard to use
 */

// Allow overriding this
#ifndef BOOST_METAPARSE_STD

// special-case MSCV >= 1900 as its constexpr support is good enough for
// Metaparse
#  if \
    !defined BOOST_NO_CXX11_VARIADIC_TEMPLATES \
    && !defined BOOST_NO_VARIADIC_TEMPLATES \
    && ( \
      (!defined BOOST_NO_CONSTEXPR && !defined BOOST_NO_CXX11_CONSTEXPR) \
      || (defined _MSC_VER && _MSC_VER >= 1900) \
    ) \
    && (!defined BOOST_GCC || BOOST_GCC >= 40700)

#    if !defined BOOST_NO_CXX14_CONSTEXPR

#      define BOOST_METAPARSE_STD 2014

#    else

#      define BOOST_METAPARSE_STD 2011

#    endif

#  else

#    define BOOST_METAPARSE_STD 1998

#  endif

#endif

/*
 * Metaparse config
 */

#if BOOST_METAPARSE_STD >= 2011
#  define BOOST_METAPARSE_VARIADIC_STRING
#endif

#endif


/* config.hpp
CuXqcrRFMxpAePwxhvMogtl8N9hnQZhA3uMHiC5gph/hLIojiM+T84vEun79lrMBJAGXRGj8gpdiheza8kNF4Q2qB6oSuNhb8m2L7sCGeEXrhrEvV9Obu+U4tvQdPUvf04x/ZTae5pPx8l/TOnuhFbuywhNCbxDMqm6BNKxtTKAKPRAMQKDQzR2Kwm+VfdNAK7aNtgZdljaKMxstV0ggVAG1MuS8O6S+U363Q9NqZZEEgVYSgaVDdLkuMubgvQwst1fmlL+02ff/uqldXkP/pV9k1mxPwQZONicsLesGQYk1Xo4a/cDdMo4/xVYS3//+sGwdYLZLLGMVUbtPKGOQOmrZXv6AXv4/qR+eaqpAOH1Yfz4cgFTq9doVVrdUa3U5UjrUPbU92dTCHF4nCw414fx4Mr/Np4vk2MEt5suc+90/8o6iyIn4Bd31Y1d235B77OpyC/4KipKsRvbKqYSBH4gKRqbSNGLpo/d1xaHCUn9Hl/S93MldYdK206SlbjLmRDK0bUcyYBNt7Iv5pl8Bu7MUwqsHC5OA7LuGH9+Pl7fT+SxgV1Jia82n/DR4w852OfjtSxyw4MDASeG/sUj5oSYp30uJH/40z1BLAwQKAAAACAAtZ0pSmZCWvcIAAAAyAQAAHwAJAGN1cmwt
*/