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
// is_std_map.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_IS_STD_MAP_EN_16_12_2004
#define BOOST_PHOENIX_IS_STD_MAP_EN_16_12_2004

#include <boost/mpl/bool.hpp>
#include <map>

namespace boost
{
    template<class T>
    struct is_std_map
        : boost::mpl::false_
    {};

    template<
        class Kty
      , class Ty
      , class Pr
      , class Alloc
    >
    struct is_std_map< ::std::map<Kty,Ty,Pr,Alloc> >
        : boost::mpl::true_
    {};

    template<class T>
    struct is_std_multimap
        : boost::mpl::false_
    {};

    template<
        class Kty
      , class Ty
      , class Pr
      , class Alloc
    >
    struct is_std_multimap< ::std::multimap<Kty,Ty,Pr,Alloc> >
        : boost::mpl::true_
    {};
}

#endif

/* is_std_map.hpp
xGE/VH7diJf4Z2xk5BPGXI6tRe+G4dsrw5tjzOcoY50CTgLngDPAReACcBW4DNwErgN3gdvAYeAgcEPxgfzSgkAhoDBQHGgGtAE6AdHAVGAVsAaYCeTIyP4UWAycAs4CeTPRDxAMtARaA+2BzsBEYCFwDrgOHAbOAl7E3rmAIUehfS5iytbkv9Yg7qxNrj2+qDbvnQh2JKaFnSf8NvveHNTPBxQFmgMtgZ5AByAC6AZEAx8A
*/