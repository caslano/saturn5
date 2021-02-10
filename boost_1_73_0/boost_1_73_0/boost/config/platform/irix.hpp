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
yT5ibDnDweKCr7CFEGyZ+yVXy3zWnRl1ScqMluuunToTB9YOR5BvNZGq8QAbaL3GHsYUdk67lnVVEOwnlMyo0K8WjDHnjPFrkjn3pDGpI0la7EyiXJJlps2x9oWxFZJ2tGk9XeYQ+JaILSXX3XjFSJ6S5m1fh4bZw4ys9ShAFszmQRQMg0loeXpI4c7oL+9iNhlZbplbpkVOHvCPllT1kEA07+nNPvxjwUOmYKm6oD92J0ZREoX9ZJQavgazKMYFpxaa0bI4LB5B4RzMudg0OFoAMbXiKA7O4eREyzfwT1W7gO/Rnu2OXx94bFBewgGMDzsk79kRVusD7NnGeDwO5hdeFJv7YDzGaWC7e4fvWGY7DzOCfwOODs3lWI/e1z3Gy3W/91B0rxPtt159t5rvAF9t7Dq5lZAykpR1BfuDR5lut7u8fbfcnJrCel88f+J99id+tLA8QypkSzMAjQCm53I+hS/e5HJkzYnCV4yEXSpoQ/9mKmpeyrqquFCawLoXG8HL6fk0uJrGgRksWgk7qqGaHY5G4E3CACfq5/nTcoGNDHXAfsKa3cGzlTQStvUvUEsDBAoAAAAIAC1nSlJ9ALIjwAQAACQKAAAzAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMv
*/