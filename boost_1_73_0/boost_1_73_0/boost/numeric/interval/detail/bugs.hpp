/* Boost interval/detail/bugs.hpp file
 *
 * Copyright 2000 Jens Maurer
 * Copyright 2002 Hervé Brönnimann, Guillaume Melquiond, Sylvain Pion
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_DETAIL_BUGS
#define BOOST_NUMERIC_INTERVAL_DETAIL_BUGS

#include <boost/config.hpp>

#if defined(__GLIBC__) && (defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED) || defined(__USE_ISOC99)) && !defined(__ICC)
#  define BOOST_HAS_INV_HYPERBOLIC
#endif

#ifdef BOOST_NO_STDC_NAMESPACE
#  define BOOST_NUMERIC_INTERVAL_using_math(a) using ::a
#  ifdef BOOST_HAS_INV_HYPERBOLIC
#    define BOOST_NUMERIC_INTERVAL_using_ahyp(a) using ::a
#  endif
#else
#  define BOOST_NUMERIC_INTERVAL_using_math(a) using std::a
#  if defined(BOOST_HAS_INV_HYPERBOLIC)
#    if defined(__GLIBCPP__) || defined(__GLIBCXX__)
#    define BOOST_NUMERIC_INTERVAL_using_ahyp(a) using ::a
#    else
#    define BOOST_NUMERIC_INTERVAL_using_ahyp(a) using std::a
#  endif
#  endif
#endif

#if defined(__COMO__) || defined(BOOST_INTEL)
#  define BOOST_NUMERIC_INTERVAL_using_max(a) using std::a
#elif defined(BOOST_NO_STDC_NAMESPACE)
#  define BOOST_NUMERIC_INTERVAL_using_max(a) using ::a
#else
#  define BOOST_NUMERIC_INTERVAL_using_max(a) using std::a
#endif

#ifndef BOOST_NUMERIC_INTERVAL_using_ahyp
#  define BOOST_NUMERIC_INTERVAL_using_ahyp(a)
#endif

#endif // BOOST_NUMERIC_INTERVAL_DETAIL_BUGS

/* bugs.hpp
aEb38rJ3fsKESXdoEbWvQog9nAHjFsiZ/rqMfLW5L9kq4cSnhFFg1suGv/SUlwjuV4rqw/3LH2+dnRHFx2y5RBBfZItyjZ093bKpIfsy39kkPE3Ct8UdldSwG8qxW8jDFE8mFclbLTpGMPYC5576ACHvHTLCzC6S3z2kJvyetMAkbgF+2lnu1auDxyf2opzL1CXSvQWSyj0lE8vz/2nIsGcme6vCGInuIP5JU/GvtJXSmI9nj/y2TTisspo2z5H9sC0bOdb6V/v+l7Wv2pPnevC/esJ/cE/4a0LLMgY/sPc45uC8f2yDJPyEb5CKPrPuzdJHfvk2+Wvsy62bXGLw+yiJxQUuE3DzRTxnAKrwdQVfYuDjA/4TVAuXrxO54fyVSPTU+MsDcVnsuUSv7vtX/RNY0cs78mW+0xolaPsEE2X9Xfmyqv4eI/At6i50nbpoT2Y2ObXI/wNQSwMECgAAAAgALWdKUjjheruYBAAAgw8AACMACQBjdXJsLW1hc3Rlci90ZXN0cy9saWJ0ZXN0L2xpYjE1NjQuY1VUBQABtkgkYO1WbW/bNhD+rl9xc9BOTjXbzbBhTbJibuKmXh07cBwYAQIQtERZXClSICk7xtL/viMl23HaIh9WLBgQBbGoR/fy3B2Puvb+97sC
*/