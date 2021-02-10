// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// has_lower_bound.hpp
//
/////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef BOOST_PHOENIX_HAS_LOWER_BOUND_EN_14_12_2004
#define BOOST_PHOENIX_HAS_LOWER_BOUND_EN_14_12_2004

#include <boost/mpl/or.hpp>
#include "./is_std_map.hpp"
#include "./is_std_set.hpp"
#include "./is_std_hash_map.hpp"
#include "./is_std_hash_set.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_lower_bound
        : boost::mpl::or_<
            boost::mpl::or_<
                is_std_map<T>
              , is_std_multimap<T>
              , is_std_set<T>
              , is_std_multiset<T>
            >
          , boost::mpl::or_<
                is_std_hash_map<T>
              , is_std_hash_multimap<T>
              , is_std_hash_set<T>
              , is_std_hash_multiset<T>
          >
        >
    {
    };
}

#endif

/* has_lower_bound.hpp
EvAu8QUP01R7KSEQuXKzPmoVOMGwsq/xk3rlkMkt+G0h3fTA6avCboWsPVfaUJAkMKoxFS8T1kieteAJ2auWvifkj1zQs+XvWyTwK2VQcumb5fBbJHGtLGrqFWRxjTSuyuOqRGpspexpH2qJa9Nu8ijZuww9F/AEA4FCM6ij6rvqBrp4e2ju9qUHNDG09qhCYESMUAobTUWzXxinlvMfMt71wD9yp284KaJTgiZ8FpaiUhuVILqNb3gJA6uE1e2ZRkBUA/a5VMkS9fizIyp36duGp6/U0C9Rt1Z9pNgkSk4wWhwA4Gaw6iJNVtnPjpQC2R6bTo4imuYeRPLpJA9tLpU80rolrOnncziyTG6kSxP+u1JVsbhq12dQYWQEhG2qst1Yp3TCa1N0Kt8MoCuSnl7vmNKW5s3LdVPX1udJNaxLvtVLELyrAGUYXR6/Obi43HvzFsaunWb3u9a1092q94oMJJSxjxessX0jQsDth1iE2z/4o3CXwkrr/8vSHuwGFqrX69uzbINmL9F1LTHvQWm7voxZvV8QDEMzZoBC6I33J6K9SLxlIpM2xRul9vY5rDRdVoWrdF2lHEZ1S6bE9I2rULIJngVL4xklAncB5FsVEZQMLyOrOq4g9CZxHvlKQs2i9TuWZRtsR2GI
*/