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
xHH84vn1IXxdFN2UFjZNbPdi0EuNrIjzIQrTVoNsEbXTvYrpI5Qi51sBwolI+Fo+bBe+h69Mv7WwAfKiKh1QfW28idp602J6iH0lciuYXyEEqHVb/7ijpyPG3K2jf9YRhnQ9oZ4AgUPzkBHpGhRJlnF2yrOcBmRAquhaeB0c9FLZftW1G2VRq87R2Lk6OgaiKTqYGPY6I9Qr5Rkh7hZ9hW6u9ygrS0F/pgcl9EKQL0nQVsBkAQ3AZPfp72g7Xrw+LUVi2GQVPIj+AvMGiIcRNSlaXdY9ACB/uqhwQYLvDzszlSaHq5QpkdFqqyRH5amMkZ+IWbwkBR5suouB3BGVUCfyuXm/4nRNrS5klWYxVYG/QWS0jBLHwKNIH+YpjP3aUMDzM8MzJ69+MkSyBGa2Xi24ug3qsaFTcjo2KhMpw/XXrLC+tQ7Nbp++zxFf7FD/nCBWcJjxeGMO2h5dpwX01qF178x0YJZEu7Id1xCU1sF+H62xxCFmR71c7waAWRw4SF+bf4DO9LP/xtx7ES7aRFLsMkar3/hxkP0IfDXLMpkb45HUdvfBLhMz3A==
*/