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
0X7q8iuGk4B7udqOjqz65BhirimHNp1DNVzcmD5xVNv+psWJB7ZPjieoSRIvvjDf9DDWPmJb6GnF8w+Ax8C1Vtr0mqIcj632C+vmLIveHsG9e479gP5y2IS3ER003z1sO1QFWj5aAKyobMvxKIifwm9mvZYjF2xvAnweAmb1jl0bGOrV+3RYxiGOz45XClsG/50fzP2zYB6kK8cviv5b+tg7feLdtwKLWbpchPDOny9nzsLmy9xESAymPPbDjZrJdE2jNHZ2//XpBZfh2zB6H2aRHSCkJFXbc2WUzGbgz5MIB+PZ4nBYwQiph8U+oMT+wqodpDGOFumN6s3tPJr6cxqze93/AVBLAwQKAAAACAAtZ0pS/zLq3csDAAAsCAAANQAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxJTkZPX1BSSU1BUllfUE9SVC4zVVQFAAG2SCRgrVRtb5tIEP7Or5jjdCc7ojhJe8q1SasjjntBcQABac6SJYRhCVvBLmKXvOjS/36zuzi5NJGaD8Wyd1nPPM/MMzPrrm3Y+WmP5So4+OGT6W+GD65bp6jnX0khX3bIsnswH3Rc4/oKqhk8et1nU3iV1z1MtFc2ch2pfZa9gm6tglQ/M+W8ztQWT4zn
*/