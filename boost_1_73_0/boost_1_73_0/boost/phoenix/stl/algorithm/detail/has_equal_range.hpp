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
85P90gQ5YM04/s1+DN8s6EML8tCMX755q+4g6Jn4bp6/2fv9oLSvHjKz9oYnZ8O9k1FpZmHYzH77+9FIBDOjt3uXr8380gOzYv/Dyf4IEDrfO/9QWrPyyKbYmjXrV1RPr5x78RrGSzPNWAHmCrjiDJ00wwRVLNEP1UUYCJ/8SMomdVoOqck+qD3O1HoMc7GcMeOR7FVKraaOJEtrtYJNwq6mCZmjN9hzQokRdaeANRZpzsLNZlTnwAv5iC9R3bvsPW+EITUgUCgV4PUY9UeB483RNGGXDj2i9aLTBlYs4jQN0ObD+UVthycJ2Aw4fepOORj7zOvW6BgDzBq8pd/E+0G0pZgAjfh8zH2f+yMqoVJhRVy5mQtXK5BAGmFC4EMkKp/28GLOUT5YJZXqag7sLVA4gChZ0gFCHoz06Q5RdhyZnG7TzgenPOIJ3pfLeWQAwR569HguwSW8YyZiHUQCQgZilof3/uQAqOWikJUpBNLE62GpeDTLp3zGw0XX0+eBs/qYGCL6og9HnxnyAKQ48KpDeajXIRJiu4YIRyrpu83UhabeH5/0jo4vO8dgJkVF5UFVTzc0ye0V1I3Qs/p8vpz+1DlQxYEvx5jfZQkEzLiDdbf9ZejjPyPSK8hEDQlU/YmqGUW0IrpbLqOB
*/