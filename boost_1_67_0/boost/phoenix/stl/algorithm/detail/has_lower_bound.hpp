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
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
*/