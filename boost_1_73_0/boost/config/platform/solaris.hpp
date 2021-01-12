//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Jens Maurer 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  sun specific config options:

#define BOOST_PLATFORM "Sun Solaris"

#define BOOST_HAS_GETTIMEOFDAY

// boilerplate code:
#define BOOST_HAS_UNISTD_H
#include <boost/config/detail/posix_features.hpp>

//
// pthreads don't actually work with gcc unless _PTHREADS is defined:
//
#if defined(__GNUC__) && defined(_POSIX_THREADS) && !defined(_PTHREADS)
# undef BOOST_HAS_PTHREADS
#endif

#define BOOST_HAS_STDINT_H 
#define BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE 
#define BOOST_HAS_LOG1P 
#define BOOST_HAS_EXPM1



/* solaris.hpp
DgfDEWn0JTeF54LDabDC8+B8M5ie56yIdT2XDv86X2vcl11UnO8+x65uNWxdl1ZWNLGo0PUcZty7zd+XmvnPfWLfz9PRSuIbfZLr/KyG4fodFvdy3n+tiLlQvtuI+S41fyrTrNsR8/cwD68lKpxayqcTitvMT8dvcuKr76lBjHvsZJkXfkbCyDPn/LdjrjMBk1Ep5erl1PLviB+jeqP/AEaq2HP7Eys/t1++rX1ys4w3ECRa
*/