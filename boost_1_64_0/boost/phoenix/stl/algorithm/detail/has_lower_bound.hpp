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
m1PthUBNPxlJWukuRMfNX3xrlPXogI9GxdpBjbhvDFVkRDfo7g6KvVnsZQkbqOtGcKmvRdsPh5mpf/xHJPdLBtZIeKJ2IcjzN2IcKvRhPFdYsphI/7AjSYYNBJL+lMYoqbv377i2hM/uwNzC3yMeRYXwdTgDyb/LihucyCXqCQDjNW7Oy3ZLpKzj5zQz0sfOCg/SaqxYs1ifZCeJ/nHegcouGxHz4q5z/PqbTwGRRPTrmQRC6sGI8YXfSAd65MoUBaoZ6a+djnlvuKRPqFxC9BWg19jXwfYxiJU+DBQkN4T491DEJ9DBlAdRkJji+7JAKVtsDzwHv2z/UFtEjsfiJCKXRz2Li7zbg+cHPyxxyxTM86OX9egUlCZooD+a1p1KDYZnb/SqynreuIy6gZ3VFdhhi3H7gb6m3ohJDHqOflytWC5FkkTWkyDAjZFOW2+5955tPKkOAC4WNCekX3OGMaFLvRkCG+lCj7tFtfGA8Nx9OsDnvBUNL+Sjo++IHdTHIcpSqflUf99hMXkxkJ+1OACadFdnq5PAtzVp3cg1eQlrJPVjfy3qNVdE3w==
*/