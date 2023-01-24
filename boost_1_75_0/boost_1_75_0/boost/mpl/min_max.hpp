
#ifndef BOOST_MPL_MIN_MAX_HPP_INCLUDED
#define BOOST_MPL_MIN_MAX_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/less.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct min
    : if_< less<N1,N2>,N1,N2 >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct max
    : if_< less<N1,N2>,N2,N1 >
{
};

BOOST_MPL_AUX_NA_SPEC(2, min)
BOOST_MPL_AUX_NA_SPEC(2, max)

}}

#endif // BOOST_MPL_MIN_MAX_HPP_INCLUDED

/* min_max.hpp
E3NSlb+cyM8jWFyoHtbUaBoiL353Xgk37fnH+D5w0Go8kJ93rkUtUPtR5zaTQCzjZxM+/ekvlVhKIKIoUlB/9AZPaobmgZLBEAp9HX4tpkI4TF5ICNFQBUTqfGa7jzSXzNi5CpH7pBkZOFjQZPMJji8sT5ALopya280EESWybSY3Hr0r97p/ps3CeyEmJaEoIasIt/v1e+gIzR1GkUXaPlUVv6EsEZM+iulH94xmnEfynDcuhmX6mHGUUZiQVaglTmkPQ7WF2U/dLh6z2jaFBaJbzUPofX8B01rJ4NxiLPaB7ND10EDxF+uBVCyztxC0Z67O75S0jU7wAI3nj057dRb1FPk3kRD5KV39epNDMc0XTWM5UzngmsliflWR5w9X745mIURCSNJngdENlSDpd/kQvn7x882Zw6PLo1sIBtwPjjnXMCthzt+yb3ilo1qtsNylYJr3LmxIB479zx2dZ0NgDpzNYQa/XDv/nOzK56WmxEckqjEo/AO/VXur20HBh2NFXy5vLkvNQVm+NNQ/mEVmsbx/1f2BeJvhLI5cFvqpyMrN5UrxWJhqGdTMucmo1tyT4phSeUToNJKaXTqoeB8wLbw+/MRvc+9Xv+FsoQnvmuTc2EzvgsDUSicbuwS/av3EEs1ZnBuR5E15rz8bpUJJXW3pDnIciU1tJL7pMSgFuzPjZW+nUR2mYSakEwOvJcu4mMZYiFkrz2Ve
*/