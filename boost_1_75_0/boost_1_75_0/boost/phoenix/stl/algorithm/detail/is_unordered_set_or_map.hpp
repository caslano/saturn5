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
uVOaS3u+D7nW4zZ/DLc/9uK7vFbkvYr1Rzd5gx2ktznWsP5OReL/GwXDmLfcyM+T0ae39r3ZoYh7/301GZtGfY94eNRUrx3mVFXlGXv09/IMOC1SbG3O6T5W9uflPYu33des2QFuXvvHcUiePM1OdFBfcAowtKBhcRWk5zWIPC2fYgO1tAUNHf2kLAGxACePXJ+380HYT+Cn5TKD0D5owkhuOVDs92n5L61+hP8M10HQ0c8yQW/rIs02E+wUYdEeMrH1Rp+uBWpf9A3uzgF9QseKTesECEyLQRC5fwZY9E2JIT/FOwL3ZnBIC7OejxQk9EN31VQMJUiaSDG62N0wv7ztA2Ya3qQoKZq5ztiZhzP6M6buott/bd/avvmCvp0BRA9ikIrio1dh97kJZfeh3aZeoHKnXmBsZfbVKC7wpXPSWTa9ZxDdNX1kW63UsvtrQ/gqhyj9ZJR56IZJ27QnF5qk1r1WcD4XOCW9/GBjtgK77ZimneO5Ewb2vHyMRqVqM1Mgc51W0RwvAAT4pW5QHZ/bjLEZY8ukwFBkUTZrBGm1eo6KsvRhzRzr/RE6wHhkITls3gEE++NkfYPWOpZe2j7oriBj5JJ0gseiFud5h4PgJBxrdmnZ/mV3drOa4K91uKy+g0n5zXcjpWuTPRZVFc/tO+58DFodaz3AQmh4x16UkhiAIh0FY0aq9KEU+GQqyDqtkE6dcu2e3A7/
*/