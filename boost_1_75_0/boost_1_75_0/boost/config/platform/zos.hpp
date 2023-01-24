//  Copyright (c) 2017 Dynatrace
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

//  See http://www.boost.org for most recent version.

//  Platform setup for IBM z/OS.

#define BOOST_PLATFORM "IBM z/OS"

#include <features.h> // For __UU, __C99, __TR1, ...

#if defined(__UU)
#  define BOOST_HAS_GETTIMEOFDAY
#endif

#if defined(_OPEN_THREADS) || defined(__SUSV3_THR)
#  define BOOST_HAS_PTHREADS
#  define BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE
#  define BOOST_HAS_THREADS
#endif

#if defined(__SUSV3) || defined(__SUSV3_THR)
#  define BOOST_HAS_SCHED_YIELD
#endif

#define BOOST_HAS_SIGACTION
#define BOOST_HAS_UNISTD_H
#define BOOST_HAS_DIRENT_H
#define BOOST_HAS_NL_TYPES_H

/* zos.hpp
/GGCkfzeoiuqmDfQi0orVgiYxXXBrQRrjtTiiRhhfUBJS2/N6/in1j2PFKOSeuX0MTZHmKgkyxHS2nGwbkAxYOc1aXNa62W9jfsRKjfHdkWEl/oa7nVeK8Eo/ln0bkIt4IfJybjfjxchPwYWTR0Qve5PEmMNGgsn5OpJrsBMqLdQDLz6WGlGQsypITDnrPf3sy8CEUTf3G/JJxBSqwzS3FDcScmYNkvJx0ePEN94tZ7ZLovEDdgFCV2cWKU65yS7gx+Tu6c61Sf+gj7+W0+oidigSngaPZGV4Kny6WlszQHRXm5qJMxIoK+a8PSc6hBYJT9IKIKsont4ji61bOd8x0doFo4AYBNDChIZwLjVK7kfElolDoEWUivdJMHbAd66gDnMs+2bJwI4MgKHT4ijtwM9ZFfA8eUq3ZoJrRCCC9w2MFXKGVALXWOQpqrUFqaPqzh7CwWTWkErbsHcqcVv8RXRMM/ky33Y/dduB4uqcn/Qd1I7YfPVlMmZleNqx2u5LJdhmWK7f3yc9xnWR/YMlQXRGjzzPxAy2yH/ZaAYuBz3GtVOkStmhkrqj6SiJOI/AbQapjrlJv5ySxBcbDS14fcDvon+i9HmNflXFukFMeunvd6/VhPNpJv5CrdrrPnmEp6xUV8Hzr87vvYcWq25+nzO2cfW84k001rt0xqM73fcD7nDB43mxAw1c3gDGvIAbJaX9ueY6+2D7/Y/
*/