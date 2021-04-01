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
gqUI/a4Xo2+WEFDocWd3IYZA/Bbjr+EgKCVVtOM+WJ7qnyXR8AJ0UxcEmP5OlxwfrKZw9JxEd/hZ+H5ud10ux8/5W17lxf0e68mJT+riDSN4IuoLk2s2L49LswFFQhtaXbUhH6qjT/ix/+T6h8Id7f6uUnas66eUo5cISGYVHtfx3y78l1g+75l/yVMPiE9ATpUQh8yC7PBDZcfTcA6McU58o8cHis9CCYyqtHOYIxrXKgJce6fPO1OYZib4G30c04mOqmjpYVbUHnt5aWi0kGEv6sb2p7sgRoTLvKVAWsTJe7RRtbeB/0826k8mlWNIvYcxIZFkNcd/25SBv5F7gS/rC467tOtsqZfj2WzwJR1VPq7JmvpzyBMIGcXmopB3x/xo1ZRQkZpSgxQIj6WE98XTRN7+FWg/rjrxVymwzPie8D2CCzcp0kIA55YAczIWl/NE5SNnPWmlzuThXBYg02DNrTLsfXZW7NnjDJQtnHzeWh0UMvv4WI36ReH2wFNpMK5DGsRhPp5P+eu1b7mkDBKsLNgnfosUSXibRMU9j3PSL5XfY+7M1sy7sw==
*/