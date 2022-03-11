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