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