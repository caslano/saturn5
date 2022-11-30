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
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
*/