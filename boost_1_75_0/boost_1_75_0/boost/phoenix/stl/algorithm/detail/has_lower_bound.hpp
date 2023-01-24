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
/diQl/KTs0Pi7RZFY6JTCf2uu136nGd/x75+aIsY/p/DsIf2H+cHKZSeCAy+7ux5E3/cFkk8b2yAX10YHVQ76A+kue+nb+2KsHA5euJpKpLoLQr4EpXp3r7mWX30MAO1uoByu9I2bF4tpwyq3Lq9KQFyidTNH+ZbtQgHtm8JItLWdg3WHt8mNJMuXECjeKpDazO8RgJBMDuxncrUwchOqKHN0C9QDuiX9mFKaKXrLRYEWUCrtt5nLyl/35HBb3U3qk36kU7LS3dQVx4qdabk7837kto9v37Q7dCthmK2Uz01fzicv1VA2GuEp96DZu8m6WWD+kAzrI7d3O0kzMVabY3pR5yXYITLg5drKnaSOYvibwKMWwJmZidH5/S8wvgFW5oFhTH7w8NFZ0xU7J4v4KG/fyU23H1eofIWjR7uWjwu6WVisb15PT+tK++pOfVpc9iJZf1wLMtiNajXQUAnlBoGXKDKCMhSdjRYLhk+Ga7ydVM1pElSoYFXN3ZSySDRRNjxKujZyVkVgCiSWiX61GzW6rnR7/D1CNcqnIbIm3LrgHWgTUfeFDj2JVZCYX8WFZYnw84Znnoiq74/nR5RrHtfUI4ySF8zKYvk08VQlDOxYFrSQeoIAd0f67CHWOuidTrUDSDjzipzClDBea+FyilGtbthO/OnJA0wd3FamDvrEotVJYSOP6tSUIXxdNI0ApZ7gfiRfucR5Ttw
*/