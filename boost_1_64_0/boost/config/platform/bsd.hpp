//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Darin Adler 2001. 
//  (C) Copyright Douglas Gregor 2002. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  generic BSD config options:

#if !defined(__FreeBSD__) && !defined(__NetBSD__) && !defined(__OpenBSD__) && !defined(__DragonFly__)
#error "This platform is not BSD"
#endif

#ifdef __FreeBSD__
#define BOOST_PLATFORM "FreeBSD " BOOST_STRINGIZE(__FreeBSD__)
#elif defined(__NetBSD__)
#define BOOST_PLATFORM "NetBSD " BOOST_STRINGIZE(__NetBSD__)
#elif defined(__OpenBSD__)
#define BOOST_PLATFORM "OpenBSD " BOOST_STRINGIZE(__OpenBSD__)
#elif defined(__DragonFly__)
#define BOOST_PLATFORM "DragonFly " BOOST_STRINGIZE(__DragonFly__)
#endif

//
// is this the correct version check?
// FreeBSD has <nl_types.h> but does not
// advertise the fact in <unistd.h>:
//
#if (defined(__FreeBSD__) && (__FreeBSD__ >= 3)) || defined(__DragonFly__)
#  define BOOST_HAS_NL_TYPES_H
#endif

//
// FreeBSD 3.x has pthreads support, but defines _POSIX_THREADS in <pthread.h>
// and not in <unistd.h>
//
#if (defined(__FreeBSD__) && (__FreeBSD__ <= 3))\
   || defined(__OpenBSD__) || defined(__DragonFly__) 
#  define BOOST_HAS_PTHREADS
#endif

//
// No wide character support in the BSD header files:
//
#if defined(__NetBSD__)
#define __NetBSD_GCC__ (__GNUC__         * 1000000 \
                       + __GNUC_MINOR__ *    1000 \
                       + __GNUC_PATCHLEVEL__)
// XXX - the following is required until c++config.h
//       defines _GLIBCXX_HAVE_SWPRINTF and friends
//       or the preprocessor conditionals are removed
//       from the cwchar header.
#define _GLIBCXX_HAVE_SWPRINTF 1
#endif

#if !((defined(__FreeBSD__) && (__FreeBSD__ >= 5)) \
      || (defined(__NetBSD_GCC__) && (__NetBSD_GCC__ >= 2095003)) || defined(__DragonFly__))
#  define BOOST_NO_CWCHAR
#endif
//
// The BSD <ctype.h> has macros only, no functions:
//
#if !defined(__OpenBSD__) || defined(__DragonFly__)
#  define BOOST_NO_CTYPE_FUNCTIONS
#endif

//
// thread API's not auto detected:
//
#define BOOST_HAS_SCHED_YIELD
#define BOOST_HAS_NANOSLEEP
#define BOOST_HAS_GETTIMEOFDAY
#define BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE
#define BOOST_HAS_SIGACTION

// boilerplate code:
#define BOOST_HAS_UNISTD_H
#include <boost/config/detail/posix_features.hpp>







/* bsd.hpp
z6c86HHDMjX+48OMFAnsmxqEyd51ynsKXByhuLh66deL4FVE9QfjDEkTPkOi1dasogzErZ+4PZMexN7ZUXExfWtgle5V1/Nk2HmShddFVOI81SBMxzs6k8ZhXRypuCiacuEO3XsuJSK/xDjBu2nzMGu72qcCGOY8vT+T/sCa6KR4ePrRk+v1TM+h49YgdvxsEf87M0abXtsMxH0f25tJR2NNHKW4mJz+ck/Mln7qBf/1ttJrIlwhwIUDws8Qb5Y5QzorLuZ9NQQ+7GfRgEy8H6mye0WhxBkCEGYbDmaZuC8nw2O/oWejnuSZNPJo/VvQJ8tFZYG9KjYMxH0POTjL3EOOcfaL1Rd01b1n0HGQOVcIy5zVEusCIMzH6JAsyob8fazioviHjX7cQGhmEuLgZPJNmGFGwmWl1rkACJO/D88ydUaPU1zs3jICvafT9QnQWwivi+iwsP13BCAsL80RWcb37HjHl3n+Stg/TqOr+sEetr/gOZJfYC+DlwvBnKW9suhxcODUrv7964Y6PctTaUkyfJkFbUB1zSX87PnUMBB33PBpWUa/eSLTb/aivrEIuXRBGcu6PcwgxO8e/eMcZDMOTqGOWA+7E0RqR2KESsdmL/GlGyO+T16cReXgoYua7+K9k5F342Tq3A22oHTJvcG+JAEInpMmlEXDwEOO4mHzrW9+rXtPot6HwDYoaRPLD9cMsphgnoG47x3h+LvRlb0buRRqE8sJK6i7sq+4MgjmHhqJc9CNcdCTtmVBf5ciuR6s24oB4ZKjhmcZfVV3xUPfNmke3duDvLh3NaZIrgXnUSBARAHPrXBbFvWFPNlD8VD64jTcLrrTXen6tzFy66G2a164UHmRFxSWWN0sGQ6Tp0Znmdj6no5PTerONtglqQkM7EmU5iNUELW6NBgMPz/uyaKTwUeu4mOoN3Cq7u1Ki1MQ35EkzYdFp22OwmWre9XawLtykuLi+wvHI6d4DjVCtkqRiZ1sMcqKAqtOFf8QdyfwNV1pAMC/d997EXuoxE7sqfXZd419J/YgJJG8RMjyJLFTsZW2aOwZVNOiWrQyiqJF7GuJFqW2VKtVS2WobVDzPfe73z3nzeSazs9785vfDNN/zz3nO/fcc88999zz9Fzk+8i8YlCA6qKZc932xGKP1WjrwqQi1H96ARTxaF3EJ0R6otugbKR57oXFoDbVR3Osj5q9vqA1iTaIrEf14ZnvoISCJifaPVEfnA3o7eNTfZzRQhpn1IGwRFqbWMGT9TGmfmh4ZKRbF1jIuehzvL8Wgyyqi5bO33JyzKNrpTY8pbtLoEf7UGcp3TwIl3PR28VtfdzVShp31YIAC63d9cy313Ip3X1/5Wxc5nmxPpZQv/EG1seVUktpdV5NOE1z3rc8t06PChrr1nlezsT1vam3L/cZgVKfUQOC6W/+fp5uG0nu+yRGzkVeq1dHr4vWUl1Uh+S8tBLHo2MNLOUw3FLDrW/UpWzkcWh9X9hL10kb53zOrV/o93Zfh+H0DmCF5+Y5qaAxye77FMQlG9f7ayNf8KP20Rbro0Wrium0Og1S6W3qz57uN9y5p4uci/zbT1184W1qG+2wLj5Jv3JfjbYabGim/u10UY/N+1IpHQnu+ybfJRvXsajdF36n+miP9TF+0vPLqlaFmk3om4iiHu47cKLaA/0o56LvPewLyXSddHDue9Q3gH7/qAoEKLT62ezh68QeP9qtiw3kXPR2MVm/p3SU7imVoUUh+irf0+NQnLof6dblrVI28hzgVL0+Okn1UQnm+NGbo7werg/8CS+3vi2Rc9HHobN8YRnVRWesi7jpq2lfk4owzkJfGXr6/hoT3tD9VaFmIo3J39Y=
*/