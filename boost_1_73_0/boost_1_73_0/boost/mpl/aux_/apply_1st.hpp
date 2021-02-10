
#ifndef BOOST_MPL_AUX_APPLY_1ST_HPP_INCLUDED
#define BOOST_MPL_AUX_APPLY_1ST_HPP_INCLUDED

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

namespace boost { namespace mpl { namespace aux {

struct apply_1st
{
    template< typename Pair, typename T > struct apply
        : apply2<
              typename Pair::first
            , typename Pair::second
            , T
            >
    {
    };
};

}}}

#endif // BOOST_MPL_AUX_APPLY_1ST_HPP_INCLUDED

/* apply_1st.hpp
SqVx7xW3O7RRPhiem6p02EUjZevlKCg2IqC1kA7zMqU8YrBjaGAqeM6UNTKgx6huAtCIzOTCgJWIZNhqOtAKUoUaCvN2QAwGxOlzRAFJ3sgtqKwHr9E0tcSU0RXQSZ6UBaUx4EytyIOYncrvu9NB5d6VXHo5Ziw3ZscyO4qS4rSriI+HEElR4eyx6CBTZal+Yko8Q1ds83j11EjF+MTwWJMQ8R4sSlRVCZmC2lk1Tl2pvEImZZOi28cTcn5web2OF8vwwF69vF7FnOrCloYP2VOHi6fnAdhEyKFUiShzpc2BjenH8us5mTbc1qJ1PTQPBswzrHgEG9GmRMYQLgVukcEmceo+h6LIqTqs4neiZnbQ0loqGhG3X1pdRvo7YW6xLrIWrGggMoM1mBy7ZoFcaLhDlODqXBmXRfedL0GMXT1jVo89K2OHOuyScg7hfwQ67IZk9c42FAB1QFOX/OB2vlovrj+PXRTCS/7SVvrNer4CIZVsK9VQ7dN/Zm15f4cPotqVeEickPXrOfXmcn3rsPjbcg4L6vjF9zmMSjisK4/9Vu0SlVKn+cSKnVVi0DCji/9oM2F35bZfvvYDZooKVUMhHXeVaVkPYS/Ll5sFZRTxPR2RNil9MBva9C/68PcC/kELjlFE/FEyvv+p
*/