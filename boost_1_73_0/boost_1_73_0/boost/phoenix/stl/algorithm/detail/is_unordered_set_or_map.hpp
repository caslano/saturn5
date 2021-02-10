///////////////////////////////////////////////////////////////////////////////
// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
// Copyright 2015 John Fletcher
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// This is based on is_std_hash_map.hpp which was
// modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// is_unordered_set_or_map.hpp
//
/////////////////////////////////////////////////////////////////////////////

// Definitions of overloads for the use of find with unordered types.

#ifndef BOOST_PHOENIX_IS_STD_UNORDERED_SET_OR_MAP
#define BOOST_PHOENIX_IS_STD_UNORDERED_SET_OR_MAP

#include <boost/phoenix/config.hpp>
#include <boost/mpl/bool.hpp>

#ifdef BOOST_PHOENIX_HAS_UNORDERED_SET_AND_MAP
#include BOOST_PHOENIX_UNORDERED_SET_HEADER
#include BOOST_PHOENIX_UNORDERED_MAP_HEADER
#endif

namespace boost
{
    template<class T>
    struct is_std_unordered_set
        : boost::mpl::false_
    {};

    template<class T>
    struct is_std_unordered_multiset
        : boost::mpl::false_
    {};

    template<class T>
    struct is_std_unordered_map
        : boost::mpl::false_
    {};

    template<class T>
    struct is_std_unordered_multimap
        : boost::mpl::false_
    {};

#ifdef BOOST_PHOENIX_HAS_UNORDERED_SET_AND_MAP

    template<
        class Kty
      , class Hash
      , class Cmp
      , class Alloc
    >
    struct is_std_unordered_set< std::unordered_set<Kty,Hash,Cmp,Alloc> >
        : boost::mpl::true_
    {};

    template<
        class Kty
      , class Hash
      , class Cmp
      , class Alloc
    >
    struct is_std_unordered_multiset< std::unordered_multiset<Kty,Hash,Cmp,Alloc> >
        : boost::mpl::true_
    {};

    template<
        class Kty
      , class Ty
      , class Hash
      , class Cmp
      , class Alloc
    >
    struct is_std_unordered_map< std::unordered_map<Kty,Ty,Hash,Cmp,Alloc> >
        : boost::mpl::true_
    {};

    template<
        class Kty
      , class Ty
      , class Hash
      , class Cmp
      , class Alloc
    >
    struct is_std_unordered_multimap< std::unordered_multimap<Kty,Ty,Hash,Cmp,Alloc> >
        : boost::mpl::true_
    {};

#endif
} // namespace boost

#endif

/* is_unordered_set_or_map.hpp
WJSQL9Eb2bGQJfKqUuRZC0NzKHmxkohQwcNU5hA+hSINFxgmLCEpy7X8q92OqiLFzNtxHsl2pJfeSsrVdhX3mMEqfIV8XUKZQyV5E9S8JqzyWCzVHbcCB9fVIhUyae5TwUBZ3M4LkDxNEYVugstNyhxm251pqlmwxmxFqW4yz6SK9Jzkq58m4hYiZFkVGYbBLcA5cY4b3IQqi3lRz60XrSNsd7PeWktJ9rnGkGeYCXwYzGA0+wCLUArZhB+j+dfp3Rx+DG5vB5P5PUyvYTC5R9a30eQS6y0wUgH8ZV1wiZELEKt1KnhcB/x9VwMjYiS5OSiyrmolN8eHP/HiFaTIHrG2VYbbWHKJe1nkj0W4ajTuJqP59Wh8NYPPoOodJTz6r5XAQwNarXYqFmp6W70Zg0tR4GjUqPdORd+cptQMI+swN7fTLyqM+trrdjra8LTha6OrjXNtEG30VBJbu68NtjX87v7bruYzDWEawqg2etro7x0Z29lUJ0l1klQnSXWSVCdJdZK0Q7XRO0D1tbHNlnoa7mm45+/n+/pb39sPEj1ItAvR+RCdD9H5ELJ3pJ1GQ+97MJve3Q6vDkvRiuDj6e4onO2nDm9urseDumwfTwffd5/PdjjPxHkWnOeA802cb8H5DriuietacF0H
*/