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
// has_equal_range.hpp
//
/////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef BOOST_PHOENIX_HAS_EQUAL_RANGE_EN_14_12_2004
#define BOOST_PHOENIX_HAS_EQUAL_RANGE_EN_14_12_2004

#include <boost/mpl/or.hpp>
#include "./is_std_map.hpp"
#include "./is_std_set.hpp"
#include "./is_std_hash_map.hpp"
#include "./is_std_hash_set.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_equal_range
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

/* has_equal_range.hpp
eN0lH2EKcw0hn4ENSnQousS58bHsvH/CfV5QNWweut+IXO3+R9itkQdTKSvynIL1+2LfJnCXsJX7bc7Xz/mg90M4VycPuiP3jeoebU0j9mp4l14nsH/toTXjHYZ/TzYjIxzRtKjMPcLbzL82+nZIOCfn/icPuVLo8C8cvcSTL+c9HplqDk+5M8kZwRk4c4wnr6BAfWy2H3fZdeDJHGQlhJyZcEtyk1P4lJyiPMhZQAi8uIhs
*/