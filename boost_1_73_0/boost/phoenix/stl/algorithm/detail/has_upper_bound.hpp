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
// has_upper_bound.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_HAS_UPPER_BOUND_EN_14_12_2004
#define BOOST_PHOENIX_HAS_UPPER_BOUND_EN_14_12_2004

#include <boost/mpl/or.hpp>
#include "./is_std_map.hpp"
#include "./is_std_set.hpp"
#include "./is_std_hash_map.hpp"
#include "./is_std_hash_set.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_upper_bound
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

/* has_upper_bound.hpp
hQ2sQn5Gq3jiz1Eqh49Y4hQ0JGf0e2TbryBxewnyjBsio/XIeUO2WsbT/8f40dfoV1fySgcTxyJ3v5DbOGo/sRB1OlbFBqzFZhB7li2I/avEmnzx0/A1JfpdfR37lgjeXTyIHalMntQG7vt3E/vBy4aDkSFkKiU6HoqfalADWvchdmFPNWQpeRL9ibm/h27Idp33uRO+QO4I4+Qjt0b9nnSwyhknJyjuGj4aOtwPwnc1Ipdg
*/