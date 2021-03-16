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
// is_std_set.hpp
//
/////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
# pragma once
#endif

#ifndef BOOST_PHOENIX_IS_STD_SET_EN_16_12_2004
#define BOOST_PHOENIX_IS_STD_SET_EN_16_12_2004

#include <boost/mpl/bool.hpp>
#include <set>

namespace boost
{
    template<class T>
    struct is_std_set
        : boost::mpl::false_
    {};

    template<
        class Kty
      , class Pr
      , class Alloc
    >
    struct is_std_set< ::std::set<Kty,Pr,Alloc> >
        : boost::mpl::true_
    {};

    template<class T>
    struct is_std_multiset
        : boost::mpl::false_
    {};

    template<
        class Kty
      , class Pr
      , class Alloc
    >
    struct is_std_multiset< ::std::multiset<Kty,Pr,Alloc> >
        : boost::mpl::true_
    {};
}

#endif

/* is_std_set.hpp
0zpxxhdrp0reCT+c/i9OUzD7/zvbtyZidNNdCf/b2TOMx/dojyd1gHdoZ1fyE8DbW3BtMV9cWq+Omc+HcbTzgF8Mw9MD2RV+G29Y4Km0GDsL0GCuEZz3iXeUM1nY5rovrdrwgdKgPNqyeHZzx6wjorMWtEfnLPRpv0a26coyw8VWoE74+SlyLH+6htPgpCXdP5FvIDO43sEJg9+EqIwhb4Zx/HXGbxUYF0TR53OsPR4tTgZijqm9b8Sza2RdMxc=
*/