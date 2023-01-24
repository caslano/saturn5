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
9FH9CQ0IGH/dSUVcnntSZvfkTqpc9e6DYFoC9/PAQHhyI2kYHjEZ7PMgOqbSwYKX8xfkBl5HYrbRxhpYVfDZi2RAeXJd5YO7uFkZTyJXlAtNZqiDUCY14yB3IzDvfIDSekIP+Z7cQDfqdvv3WFzF8Fb8a4bh9gDjNP7Vl+NffXxGrE8FeJgrkRunQ3ZQVAkn3dexCH2s35sbo5Uphl36QQrape3ovrlrlO5FTFkXuV1MGUiK4y1mDCvDaXVQcJmHqRhE5gONF+PL2BGMLDt9SNmhe/WQsrn3dRZSdkPyaUPK/vktBjmfOaRMwyOt7Jqn344LKavXQ8oC94qQsitHxYeU1dBJLL9ePPx/xZN90IXiyeRP9HUpvHQ5yKE23U7L92J9s9iCKxTX7e7fTHpIWbtd4le76LvEjz0YDSkr7BIfUubs0i6kDFdsfEzZc/dw6ZdKDfJQKlglEtsubaCgsvWdB5Xt5EFltRRUZo0NKquduRNuZVDUGBL2FZRndDoGljUHMqLhWvdcJ8K1rN/gzk69Rik/8SImyIxHnfFd+CwJd+E7BJslmzsEmw34iq5jItX41/Kzpws38ycZYWYA/GtJIt7s02sFjHd+zVMl2Mp3kOtZR+I9/YXhxgvVhLdmK/1bot69Jy8r+UzUMSMxJtrQ9iQTIVqrpxBdLDpdEMG6XwVbvxOsohBthmY9wAPb8G+UDyy8Pzawrak7
*/