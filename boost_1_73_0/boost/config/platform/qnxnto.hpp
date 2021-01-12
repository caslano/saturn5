//  (C) Copyright Jim Douglas 2005. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  QNX specific config options:

#define BOOST_PLATFORM "QNX"

#define BOOST_HAS_UNISTD_H
#include <boost/config/detail/posix_features.hpp>

// QNX claims XOpen version 5 compatibility, but doesn't have an nl_types.h
// or log1p and expm1:
#undef  BOOST_HAS_NL_TYPES_H
#undef  BOOST_HAS_LOG1P
#undef  BOOST_HAS_EXPM1

#define BOOST_HAS_PTHREADS
#define BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE

#define BOOST_HAS_GETTIMEOFDAY
#define BOOST_HAS_CLOCK_GETTIME
#define BOOST_HAS_NANOSLEEP






/* qnxnto.hpp
WoDaitqNsl61raaoIahC1CrUVtRO1AFU/G6+xKGGoApQy3fbP2u/5OKm1C9h7EDtRfn2ED9qAGo8agFqPWo76iXUQVTyn8g7ahiqAHUpClkb/1Q5G//IeTMbZhqZGnruDGYMgMJnz2CGfhO/dw23f9YZNIXwUnhkuP2TzqLJKsVdy+OTd/GPnkuzyakP1OuoI3+qlmlRff3jl+9fvP8/v6w4b2rJP0/+f4eI8/926PyE806R
*/