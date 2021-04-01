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
YNmLQn6QNW2jOU1FGzkoe8y3kh9eK7kUe5pgbKo+vCzxbFNp8DkWt28JquCSjztVYkJ7TTvv6I44hy2jdQ1Ei+LTryw1wtuaegGKbY+A7yTYhDd9NU1AJ3eMAL0eVmd5XDBc+8eiUMqNNMwl2S00kHuwbiB4C1quzpYB5XeS1LPZmyyRWZaUiQv1F0hnjm3CHfzdM4oWCOM//4nGo+Cp8EOU4jD18jncBnk83wFdCzmlAcj64FD5kGAZkWEEh6yX0uOoj7sy+XE1MikplWLxKyrWJg7o/AV0av/3xtYnixB/t+jjXy7rwRtiibTMvkMazkicoEhVrOh1g8EAE/tBwOSVic66TKp8MapPOaDcVJ1hTxhlD3cVPL48sAre1CULJK3pRp6ob4uVKM5Yosk5SBscarkYJhkPtSBlhFTPprIaa0q/5dfoPCN0TPoHuzABpQwLLe+7poIUP2CIoGDU65XmRZSkiHHCHslYTonUpDwoa+jSULy1pvEXlJg9aQ2gaf2nktq1BjwsQGaX8RBqOGzz+955Qqnw+Q3PFYdKy3UZuP/AhYNit6oW5g==
*/