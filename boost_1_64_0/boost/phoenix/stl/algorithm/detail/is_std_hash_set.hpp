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
// is_std_hash_set.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_IS_STD_HASH_SET_EN_16_12_2004
#define BOOST_PHOENIX_IS_STD_HASH_SET_EN_16_12_2004

#include <boost/phoenix/config.hpp>
#include <boost/mpl/bool.hpp>

#ifdef BOOST_PHOENIX_HAS_HASH
#include BOOST_PHOENIX_HASH_SET_HEADER
#endif

namespace boost
{
    template<class T>
    struct is_std_hash_set
        : boost::mpl::false_
    {};

    template<class T>
    struct is_std_hash_multiset
        : boost::mpl::false_
    {};

#ifdef BOOST_PHOENIX_HAS_HASH

    template<class Kty,BOOST_PHOENIX_HASH_template_rest_param>
    struct is_std_hash_set< ::BOOST_PHOENIX_HASH_NAMESPACE::hash_set<Kty,BOOST_PHOENIX_HASH_type_rest_param> >
        : boost::mpl::true_
    {};

    template<class Kty,BOOST_PHOENIX_HASH_template_rest_param>
    struct is_std_hash_multiset< ::BOOST_PHOENIX_HASH_NAMESPACE::hash_multiset<Kty,BOOST_PHOENIX_HASH_type_rest_param> >
        : boost::mpl::true_
    {};

#endif

}

#endif

/* is_std_hash_set.hpp
3LJrZi1l8zcsSoEFixXxPmpPpY71myUT5h82y0y8J0kpOr4OhxYgRrf5T5x1qGW4hnnzIi6/9oL5m4TxhCs0OUbMmL4p9E7eDzSiEHsT9PYfulAPcbJoly2GorvHXLpm92HyuTqR3uB7M0BXJYsXXVoKjMhxLoIq9lpiPybfrkMeNy7WOd5a2bbcBCauQkJg1CPQ7/FHvt514B/XFEMrECT+A/eGVioeTCDgcrx2LL1S8HeXyB1Z3RKvCI3/SggaG5KHY3HJXgrJ/lGkoqT+EHC9wuWV6qSBHvFNqLoQ776PG6C0nChlZ21ISIwWbv4pdWBEcocbO59kD7uAJsGchDHd32llPMcASE+OGyRlm0B/DjtoF+oujazwXZq7Tw0Br9fWwxXWq1m8lm0GQ0cFIisqzkcwzmi8umK0hXAvtkm5GM9xUHFxRLyTjMj4Qq+dGJ2aKcHbSdHgbI5IhCrBEQSUq1kA/EOcaqRe9b0GrmOLJ2A6dX7AK4oOOh3I2MpQ65ZNbYw0B805aNHQsrvWJAwwXcu9OS2rZRO3Vruo3ILHd9mjERFCFyMJ1g==
*/