
#ifndef BOOST_MPL_ITER_APPLY_HPP_INCLUDED
#define BOOST_MPL_ITER_APPLY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/apply.hpp>
#include <boost/mpl/deref.hpp>

namespace boost { namespace mpl { namespace aux {

template<
      typename F
    , typename Iterator
    >
struct iter_apply1
    : apply1< F,typename deref<Iterator>::type >
{
};

template<
      typename F
    , typename Iterator1
    , typename Iterator2
    >
struct iter_apply2
    : apply2<
          F
        , typename deref<Iterator1>::type
        , typename deref<Iterator2>::type
        >
{
};

}}}

#endif // BOOST_MPL_ITER_APPLY_HPP_INCLUDED

/* iter_apply.hpp
QeY1Cnx58FkAeF+kKBcJCRVm0lFB6+8pnyhRF7slFF0bnQUc3hianuUoqE0NZU6i8hutGkRgYW/AU5ol/EFruQYnGy8hRj5GBLfw9T5TxUYj1WZrlAuec9FiTuCnccZmS5kKoKV0Is1Fu5tUNNRYeXZ0oHoc+epWIiZD4CACGJ1pjs6x+QsJMyCVldt0LQqkAaghU9zJMPCA2KSDmL/EUsdRK5CTRTNa+yJKoFQhujmr6lrs4RXhN+rRjM0xGbpfeK08diciks5eEo+Uh5lp/0JFSnVpBAuQpQve1HfC8iTnJIZlTPxmii4t8V7r5MZg2wGW/60exoC1jrCpEoohhowFiW7myPBAkibYB0BA0mlZx9QV5lg7GdwqQVLBzY/GFQTE0sv8QZ7dlXdLr+cKyoxytqDL5Gg8lbxGKl59ZUjFNvTL0988uYlG26ExRPKiMpz7xNwf3Jp43+/HSwLKV80tYfRUuBxPBLGC2OSy6CJ4IsX/qGwFW4rbREkz5schw/fOGIYRlzh87Y9vRwx62CjSOMZIIjaor4ET1wkuQWKYJNzUb0vq84ZKUw==
*/