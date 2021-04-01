/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VECTOR10_11052014_2316
#define FUSION_VECTOR10_11052014_2316

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
#   include <boost/fusion/container/vector/detail/cpp03/vector10.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/container/vector/vector.hpp>

#endif
#endif


/* vector10.hpp
Jii03b2GnBhHGftuaaMdCIqGeU5Tu/Av7jr4/ZlDBgIo3URb4IDJvLssg+waocQWPO2SN9U1tc6FJOf1Fn3NSVdKpeUCSHJsD/K42st/LPJ2K6o3kqt+gYdECUagpxtidTflZmn6K170jkMkBls8FfzjvkdjA289WFrBwOFUvVj4boK9Z1EAuidEVpQvx6dguhmgdPSNpK0NNENNeOkk6mgtalHMDnecJDHYhHx8PyuINl9S0IBOXTU25IyisrL3LRH/Q+NQzYmUdqHJsiKTuw2oElxk31z64lu6S68f6zI7BTecTI4rDJSyfp8C1PKPMd0aNE3j6L4ENL17VFXCW6y96QPacxDYaJWyALFZ2AJQjRsgnWUlQikbo+5zAyQmcVuShdWzqQXAvdqHtIiEinVqGIIWI87RhAFjnda7aXExgpMQP5glBOL4EWjrENildG5u3qIAW+S/61Dl8ePx6wUAPLu0pS3/Q52yIUFX5qvwEgMJIwRM7QxhosgWMAm5NowtJZ6K3FDhN7lWCCYRoBVYrxyCiUnnjHYPckLsLOUaXeoGfz9YUSWAcw==
*/