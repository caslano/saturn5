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
// has_remove.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_HAS_REMOVE_EN_14_12_2004
#define BOOST_PHOENIX_HAS_REMOVE_EN_14_12_2004

#include "./is_std_list.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_remove
        : is_std_list<T>
    {
    };
}

#endif

/* has_remove.hpp
JPeWqebiA/zIa16GzeuJrS7ADlHleitDzp3YZGh4BL0YRL9jWce0N/ixZ9yLkAdX5VvsC3fVJbsJek8+4mH0sCh2tyn3PAa5q7xD9RK+jBnO/WUZYhHmKX+y3/3Yiqxn4J60bhDrhe63rqm8X/KPsEeF8MUrwJ9Gthe8C71jyB0Ppgxebv+We6V65IlAsyvI+vI73EX1x/fhmwO/ZJ9aHFtN35tLc5/TlTwD5OMV/v32dGiB
*/