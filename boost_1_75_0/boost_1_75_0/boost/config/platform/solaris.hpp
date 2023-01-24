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
95zymfIHBljKMQoZ2Xnnc0ge6eUh4KdZFmDK7MJqhPgWIwX2d+YOwJ62s/0gDD4osbpIBasDQHX1waA6fMTr3tY61VtgIv41cJ0OF2RmO+6YEwDuG/mAOmUhL/HdlMz/Adl3s5CRBYpAk5hNxpvNzVYE4GSGib04PuB1J0RVN0G8vWkI78+c2+rdy5hM+lhSRquuwNtqBGKzwygCBmFye60YWuvxGndZl95xFopinDMBqhkBRkLQ0W+H9m8Bi0D8HLAIQJuiRUPUCrvBmcyzYyrY3I46ZdADSAzAQH4J4GruAmxoZJ54XXk1AhRnMYnZfYVT1t34cQx4NI4m++nez/3aSw6461cA+rHIHDfmeoYPimxjKLXeA9TQZ0JQeseHXVMxPMzNcDAP8cpqknZaG12uW8uLBZgOuNU4FJG/oEBdDBgE5k3cLst/i3JvAAbvZHgNzJQDHzkgJQHAN7w4LRMQ9ifTNxQAmy6RzoaJ8d/FjeEYW/DV5myYZOKy7I6Z3vXAV0/rTzK4XZqy5J4Xm1bzqc5PXso5F/QVxwik6iWS8/c1HUIZJZTc8fbZcB+zsuErVPWVccz7/ebfdM34fYdtXOl9CC9m0b3TY/taZIgxmnF6SaejjrjlPw+/Q90z387XxcUztEYFQabUw2OC87Tap/AFC+2k3LctmWt0LaoOif44J1hJXdhD++p5OYUCB4RKARtabVFzVK5g
*/