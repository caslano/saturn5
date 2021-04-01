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
wZbx+Qnl16QUXOMN5F4vZpcwJwDdqVY6P1N0pJrIRELChw/BPiAjHafo9AHFjy3tK7kKmwaarC7roAzbcDPdS3NKMy4gSEE3YH8bUwEMu6tLgT7cM4JLnljkm7/zoI2M5jI8qV3cHQok5ADxYNX2KZ4dk8R7HFEFdoYrnChQ5lqNDX1VHaNGzHiPMZ2znAhZSk6h0jHSUjyk/QaHq+4WuZbDSK+zrKosyNRlOOh+CaQw6aDtSdYC2tJ0Tj3Qtdnj/r6TwVFJVuYJP7ydl2WfISucxRnsrQrW0ZZX5px/+kg+KM8T77HbmfDc+DW/faiPP6N1equNBqPhlbbznKKXehtyGGBxM6Y/l3aB4rXgH69ZWDqswNW7WoulmCB7vxDBOn/sVDywrDQjOVso4pTnKS4VCDDdSjRaTz5/4k3hxBeCRZMhR9u7WB93g2xB3RoaeLHa82pDZn/e7/ccTG5+Z0aZhJ9T1xYPJAACPeOQmaZwLIOsBBzYRnPZkSNe9jdw6qivAbOa2+MHrw9Y/9EdF9a/yD/LqSIRWgxN3F6EI4pNFPsPb2Nd1pZAWg==
*/