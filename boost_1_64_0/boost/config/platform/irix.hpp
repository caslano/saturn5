//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Jens Maurer 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


//  See http://www.boost.org for most recent version.

//  SGI Irix specific config options:

#define BOOST_PLATFORM "SGI Irix"

#define BOOST_NO_SWPRINTF 
//
// these are not auto detected by POSIX feature tests:
//
#define BOOST_HAS_GETTIMEOFDAY
#define BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE

#ifdef __GNUC__
   // GNU C on IRIX does not support threads (checked up to gcc 3.3)
#  define BOOST_DISABLE_THREADS
#endif

// boilerplate code:
#define BOOST_HAS_UNISTD_H
#include <boost/config/detail/posix_features.hpp>




/* irix.hpp
BPXKI6JgMwyNpqnK0HLQYO+1NAlRAnIoCBHFZEDYOKKQfeaYrrxUOem9Dw+GbSgZ4/0xXmfYzy5sohCo88RX/1HMG85cuj/rS3xfJYfXPOdizWE2t560LQs03LiYObpCTKvst/9ul2eCj8ryJMeHgm49pFFcOP6YgPgfQc6hLiYIfJch5I/w1LW82Tqzidw8pv8GEGV9Dyzmn+6CD6heZv6Jx2xMQOe1fKUFC86SXfe/2GZxDR52BfnneNPZ7bZbiVtNNCm+24q2T9hqjjwL0+B55EvVapOCtpNtiho6mB/Fb5LJwb8BNzvAwon256aycQseyn6gglqH2DpBn79izbJiqQVmMxZK/cP9obEb59sDEuyU1Xmrp28uiUbeFYrflozd3JpbIUGgVepY+V5EX4Qf/o23KFdoPOJGRiVtamgbnXpg9FdyuljdL4itNxksgGtxIqFRzaRHDIsnXNcpuPFLtR5Nw7j4jH30HpH77nTSrTT7Rw8QulJ3WuThcXRtlnDRRUHetenhWAogN8FRSp/CqMUQpgJiOCDp54fp2nSoymp8I8jGuElxHA==
*/