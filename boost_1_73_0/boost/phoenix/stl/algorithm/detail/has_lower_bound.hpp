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
7v/oOTjsUVP87FvocbOezIM7iSyzOBPhPY0YbENkSXLXmNO6vcghdAhk/uWqoSPw7hI6sL8lvHvKPCYik9e5d+rG3AZyGupPHj45GNMvm/Iud0RT8AXD0Zeo9ujqWdrjV5r+jM9diQyhmytucHeJ/fLqxZ3vZWQT/9ujN/4wPfpPfl9oTezoHfIxuAvM9Q05hjuQ64LIJpujGHx0uu+x0X8kPoBu78LjXoxfZxD5fi2hSyts
*/