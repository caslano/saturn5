//  (C) Copyright John Maddock 2001 - 2002. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  IBM/Aix specific config options:

#define BOOST_PLATFORM "IBM Aix"

#define BOOST_HAS_UNISTD_H
#define BOOST_HAS_NL_TYPES_H
#define BOOST_HAS_NANOSLEEP
#define BOOST_HAS_CLOCK_GETTIME

// This needs support in "boost/cstdint.hpp" exactly like FreeBSD.
// This platform has header named <inttypes.h> which includes all
// the things needed.
#define BOOST_HAS_STDINT_H

// Threading API's:
#define BOOST_HAS_PTHREADS
#define BOOST_HAS_PTHREAD_DELAY_NP
#define BOOST_HAS_SCHED_YIELD
//#define BOOST_HAS_PTHREAD_YIELD

// boilerplate code:
#include <boost/config/detail/posix_features.hpp>





/* aix.hpp
Oi96pHY1IeFpXPWyx9BjvZboyQyl3YQiGEoDazMb7fyA+O6LjnDAc25Pc0vZ425rY9jAwMM/2h7naj3nNm3IicryRuC+jgpXO6K1hVToOlnKR170UrpGdq6KDr5oWU7KhGSn1PXZ/7vdWGfYGm76Tr7y0UPPx9xv1H7EZXyQXjofrWGr1X7N9oVXrJ9X6b6wQs0NYXttxTLJYw43Vi43S5x6/Mju9cwemGMt1vY5QREswfvKB6r4xC5/eatRasal/qOuOL6I51Wmaoom+Edtw/0rxjUBP3InGyvPkc7YHCnCiymjdBq74lzv9VSPVDot5qTLvRB9luAkgzTIG2pxM73/0DTTH/J14tn4Ty7HlDOVtpPHlftsJkanvn4/c0XV38zY1UCvN3qFu6Ymf4F/WzezWZ2dbV1hi/qqwS+/emtW5bZQo1Ldk8fP28wkbMpHHy5LBNasrkff9bHUrCKhrGa8cr/xcVm1/nWf/vZlITJINLQRprOwZ9gD/oHcG1hZ9/RNWeCcIOHvYb5Bm/RFuWuJlY64l9oW/Sgn+7d/q7g37nU1KQy+GBO5mf9pWGWYcngTWf+/rS1FBcyGZIER39fagBd9I0v56S5vOlPWvRwapnNsr51osxqqNprTdplCrhCwmN8fpVQbCkvsXzXMT09NNHJptra95e76crhevpHjWTLlk2y3PIGLPbO5+iG4s3qKKxpmWG0319oh
*/