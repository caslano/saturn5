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
// has_sort.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_HAS_SORT_EN_14_12_2004
#define BOOST_PHOENIX_HAS_SORT_EN_14_12_2004

#include "./is_std_list.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_sort
        : is_std_list<T>
    {
    };
}

#endif

/* has_sort.hpp
6N9W4kr8bN0g7MpC7pE3QHfmVXcUtqMUczrLfSN0q3tSuOPjlD8NOYWs15eYpWgLZGUAf+chv8uPnAz8TwP0sXxj7rF5NykQO98uHP3aTC6U+pZK6JeCea9BP8tD7xj+7j8BP/MeMkjc6IONDBuqTia4A4zj5P0h/pv5fYx+TsRehM5FngKYN+8rNsQWdClPvtqnnDZtYK3YHT9ivuGs158cjx9GYvPxaYXh96o7+El4sucO
*/