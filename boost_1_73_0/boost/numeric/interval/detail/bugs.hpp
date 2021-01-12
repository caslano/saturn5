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
EH48W99cEKD+uZzwvxL/fO7CAP6lu/xzav+9WPqfCWxQ+K+FO+cXrgzgBMv+drgrfuwqnv/Y1TJ/Mf+Y8EsIj2cCaPB5++9y10r9kvTRjQG8AW//neXcOJX415LX8/wXhd/J/I+bAriJpI99KYDZZP2dFv5T3bv+kzcFqH8vL5z592I3y/yvEf/kLQF6fi3/9QCus++/iVS5/yZ+bwDLNGf9UBl/kAvgSnL+Jf7NAIph4EFl
*/