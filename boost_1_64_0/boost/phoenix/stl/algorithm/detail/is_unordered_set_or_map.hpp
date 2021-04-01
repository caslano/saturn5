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
daXJxcSUdYxEjBfilYNtirbt4zg+riBXgKM5kViCXCAT42ERHidHZVRJJLrnobRtAlChKTk241qB7zdu52TPL5oe0/CBkEGh2bl73K44KAHUlrt3gPvN0DBi+eFTGzuUao55sjz2WZwPu/EAO8xSm5a2c2ADoMQjzJkTPQ6SzCmWywTBX3/OgOeqoHBt+RQ9Rzq1EaTH+PmHA5e2CAthrDObTRgcra9ZOgxSv8xLUD+4bSPDjPDGcnhZX2gi+JcfDz+RdPi+eZ8y+6pK/QmgmrUac7K8S1IFZXcYHzdOMwrBXDskLVIjvMw9+K6jEgv6tSBUqjvBY9KRbJ3KJk8huY7lhq8ImR6kKxpQnrkLI+OfnBP7NeVGr7HHlMtfKu7OwfcLuFAeJ/bLsI9ASP8ttYMgLZDqfXuLsrkQlnnxyHtE3m3qg/aPAqC3eJ4h8gZwVyKDNBwwnBuuAUBSjzYtlBVP01W6/9RBNUC3SWT06no/ZuYNO03Kn2Pi258zphyOzMlKETB/29DECuXC3V1IFZeYJfLxtaMQ/gLiUGvMwHcWyW0KMjImsLDZsw==
*/