
#ifndef BOOST_MPL_BASE_HPP_INCLUDED
#define BOOST_MPL_BASE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct base
{
    typedef typename T::base type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,base,(T))
};

BOOST_MPL_AUX_NA_SPEC(1, base)

}}

#endif // BOOST_MPL_BASE_HPP_INCLUDED

/* base.hpp
EoFAKqsERmIowgbdziPgWTwnNqiQgeg97n1ZULWaUE4MwSvKPX9LX2y1VTJ0bK8R9shJoHS08VwAsdBsLceT/sGu/dt7ET57qboish56TOQ4HKfPh1yWXgS4pSgeL6fJjI7hzEg+oi0xhlNp3BIy7utN2tTXYQUKu7KXDOi0gR16h9QPNifCYJM1jJXEgS985+1Q2U6edJ2VlKKmBvz9YF/JwMqWAJ4mKaXzLnIE5SZ/nSp/trSB9MizI77I/6W+x0JNVewtQ0yWPiSz0rFsIAWgmWsHfWPi/fhmWao11EQ41zcsNVzq0Ju1T2kygUylbWlzueF52OBCClflFuXybv0+TeMi1szsCz6JmByJWf4zf1bLlcs3jplIsc36yKEDvYKQ1vzHM+LezO/cRTYamkCWBd/lgxGD0hInirSf+6RkUN25junrsll2Opp6o7PmhcqfaJlqkYQMR+Qx5XTnQw0/CtKSNiOG929DDXaNHMy0X6S24Bvte2UArQJhgHU5ojdhKTxq9s14ue2mjWs0bCXYa5YKQ5VlnojTiKFm39O+89Ocu7sJTA683w==
*/