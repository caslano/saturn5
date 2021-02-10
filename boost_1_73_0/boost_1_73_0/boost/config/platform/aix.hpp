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
UEsDBAoAAAAIAC1nSlL7snxzZwQAAJQJAAA1AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTElORk9fTlVNX0NPTk5FQ1RTLjNVVAUAAbZIJGCtVWFvm0gQ/c6vGPl0JzuiuEl6yvWSVkcd54LigGVwc5EsIQxD2CveRewSx7r0v9/sYuK6idR8KFEM7O68eTPzZnAWPTj4aZflaDj44RWb/5guundG01r8i6l62SCOH6H9I8MF3V/hagg7q8d4AK+yeoS+sYq3vs70cxy/wt1Ck9Q/Q228iPUjrbSWW/uRqDY1uysU9EcDOHz//g94A0dvD09sOE84wxJChXyJ9Z0NZ5lZ+atIHh4ciR9tQAVJ6ewBRgWTIEWu1kmNQM8lS5FLzCCRkKFMa7akF8ZBFQg5KxFGwfTW8/+2YV2wtNjibEQDshBNmUGR3CPUmCK7b2GqpFYgckIg/IxJRZiNYoI75B5BYb2SWxhNIimlgOQ+YWWyJHeJgkKpSv45HKZNXVIkw0ykcph2qXAKtfouqltis0o2ICoFSkAj0QZ93oaVyFiu75QiWqyaZclkYe9okUOeDUUNEstyC0emDGUbAkK4zZatT0JF7JnSNym41N7WhVjtHaS0boHypubkjtJC5zJB
*/