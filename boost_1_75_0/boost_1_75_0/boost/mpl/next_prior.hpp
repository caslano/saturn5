
#ifndef BOOST_MPL_NEXT_PRIOR_HPP_INCLUDED
#define BOOST_MPL_NEXT_PRIOR_HPP_INCLUDED

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

#include <boost/mpl/aux_/common_name_wknd.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

BOOST_MPL_AUX_COMMON_NAME_WKND(next)
BOOST_MPL_AUX_COMMON_NAME_WKND(prior)

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct next
{
    typedef typename T::next type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,next,(T))
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct prior
{
    typedef typename T::prior type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,prior,(T))
};

BOOST_MPL_AUX_NA_SPEC(1, next)
BOOST_MPL_AUX_NA_SPEC(1, prior)

}}

#endif // BOOST_MPL_NEXT_PRIOR_HPP_INCLUDED

/* next_prior.hpp
Wclv1Oq/UgvgON0+z5JYSa2WBBQU5b/qu70KNUgB+mvF5CDBdQJqhp2C91AWiLVcFfcnODbMP91fbH27jyFFaWbxS+wZzMcAuVURvR1/iR+8aHXH/tgU9ReIW86Cs8T8829rBTR2FjcO+QeUSnSPVIN03JSopC5YR2S0qbBgWYv1i2sqcE/KQSCwsPJ0ztBovS6uui6IoQGZ3A1P2L/ccugF9JPRUXd9uqHSmKfpBVTUk4d8s6ZwVfkhN7c8vVbARyofS3azaQUqJHTjWdYsnFV4fEh858dvOdxcdoNNXqgHSUhcQLp9kimQNayrFKlUyBKc8bbhrZ72rPUXKXVFy6agF1MU6Ks4oDz9mRYsXLbPkajIk6w3iv9lU41mg9fStrL9Tw++ija1o8Hy5zRnSq7amZ9SDDa8hNM/rxlivPgLf3Gozito3RLvSbxDJmgoGsaLBQWADY18wTaDhNdk1UjbPX/LDwBb9C8Z1RR2qxw58i36ZCNOiegcjbh+ANTbVr2qd9lZJT8ovdaqhODXbao3G7pZHTkGp/4tqUJMKUIrZWN8g5bjV81yu8XB/eTbZmHrKH+Wea72qD37Fj6tTZdyWu0Q35wb4yaD/Tr72Nk+PoGwqG+X/WBOQHw7wRfEmsKXv5Ha23fV8dbUEz8JOlRDjr623L1JQ5aY/arIajVVxFZpwH5WPT4G/g/WaPa2DYDa+aDmJVZYvG/V
*/