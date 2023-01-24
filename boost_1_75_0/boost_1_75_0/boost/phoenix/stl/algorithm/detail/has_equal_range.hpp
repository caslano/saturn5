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
iD/RDqBT9a88q+Q4QY1/+oq0jCwiQ1iOi9rORHsOROnBYcmExeMOUcEmxkmaBrcLflpX/mtzIVf+LGj9K//Ok0sy4oLx+XLTUxT+31/TPvMa5pQFy/X2evx7wnTAEI/d7OSHQiZL69DkmnZIbex+0Wggg9Zjh/EPtER/6Kez5UzyYh5yQoSPSBxvuD2Rzo6cW5qQkAq5IVfkMr7aWv8c3+S5yoUqFV5wyyWQ7LdLrgeoi7lN8gW47H2ThdmLTqT14YJ5KWGzOWSvW5jK/6dxxY+PNQGEIZvu0mz1nGmOSl9n3ko6Q37r0SnJNqeaBC0ELPX3VHWmNSTglI4NCft8HNe6ZMgY0ZTmogvrVRdNzxLvcUrjMNjnpgRK7KZQokWo9gQpgX0fmIevJAjl2YBIqbfyr+jsF9/hAzwcLoYK/TWYpQVcWLugoEcY3Z4BacJWL7KBumZuJRaPFsRWtPyzi3wyHAFGaB5OrMUvEpY+6l6RTb73X6jx63NMo7WG0D/kopcp6i8MmJtjXhUwa3r77L5jhEA32T8T4Nf/8BDFq3ddXB2Ge+31hAY9neKNMVu3/gF30Ib24i9hPnzGZ6ttCHvYMkd9RUUUpjeET0iOc2jaEYehnr4ceRfp00G52iCjTb155dHxdVu1bTqKIMI1jbfkUkDmpTnT0MtPe7GdXc2nhsG8xNm6EeZrcayoVA+l1GvRZfiA+2TAGcOs
*/