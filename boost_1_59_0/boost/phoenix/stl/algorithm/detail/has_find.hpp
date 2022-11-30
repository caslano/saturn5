///////////////////////////////////////////////////////////////////////////////
// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
// Copyright 2015 John Fletcher
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// has_find.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_HAS_FIND_EN_14_12_2004
#define BOOST_PHOENIX_HAS_FIND_EN_14_12_2004

#include <boost/mpl/or.hpp>
#include "./is_std_map.hpp"
#include "./is_std_set.hpp"
#include "./is_std_hash_map.hpp"
#include "./is_std_hash_set.hpp"
#include "./is_unordered_set_or_map.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_find
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
          , boost::mpl::or_<
                is_std_unordered_map<T>
              , is_std_unordered_multimap<T>
              , is_std_unordered_set<T>
              , is_std_unordered_multiset<T>
            >
        >
    {
    };
}

#endif

/* has_find.hpp
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
*/