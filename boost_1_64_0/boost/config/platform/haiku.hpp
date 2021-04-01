//  (C) Copyright Jessica Hamilton 2014.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Haiku specific config options:

#define BOOST_PLATFORM "Haiku"

#define BOOST_HAS_UNISTD_H
#define BOOST_HAS_STDINT_H

#ifndef BOOST_DISABLE_THREADS
#  define BOOST_HAS_THREADS
#endif

#define BOOST_NO_CXX11_HDR_TYPE_TRAITS
#define BOOST_NO_CXX11_ATOMIC_SMART_PTR
#define BOOST_NO_CXX11_STATIC_ASSERT
#define BOOST_NO_CXX11_VARIADIC_MACROS

//
// thread API's not auto detected:
//
#define BOOST_HAS_SCHED_YIELD
#define BOOST_HAS_GETTIMEOFDAY

// boilerplate code:
#include <boost/config/detail/posix_features.hpp>

/* haiku.hpp
l8GZhAKwH7QoIHhdMzJxh+gK9vTwVzLOAf2X94QWumh6iLyra9MvTLfjPeHxRL1+WNKwkfDa5bl3sPXoiAWSBZ2S30FswOfoFQTxyMb4lWgzlS1oD2S5jD2VAp9TZpf8h0lt08KV3wUIWTcNlY6vuJs1eprBVQC7yv9zwWFgpIX66YqAZuG+RUw4YJ/4gMwm2SJ5dD+LIRTvYeZdObfm7unbR7EveDo5LunYxR6xaQ2Y1/I/s8sBDq47slMiViU0lRZoHjoVtQB68ze/rHp3qTxRx5F8pIhj6OybbFyIVy5gABzIdbhwNVsJy3bPfLKWuSnhubu5c3jsSpPsXTAewNs6bERNoKSQHTr0OicUkfQ1G7RkK4D98smSlcrRWbZrMklR685m/s8YTZUubonm692/NvV/vD1Bbv/OBb6VaQwJ0nHYq/xRVjVLd11ot+ABU+y25PEv1JR6QDffJRQO4zor9Yea7t9QlxAUsBuKJ2q1EKE4wOrrcbbknyo8WPlvl2lEQtJoNFYueY5yqibtHyWXqVvX5KYaqrs7GngUov9mC2yUUVytGhTjjQ==
*/