
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
fM+cBZmv0mavH/WK9jy6JrvYQ2211WvLqAaPzgPda154OIKuG6govnd0ENyZmBD8QIlOOGTxsDNUS1N292O+jlXsRGaEqcf46K/kUcJ6tLXxZpgynNefL1ivsVLLWHUhSwpL+xOTZ6MyxPz4uBjlzg3L4fozQug4PDNKKzS01Mtcwrhc0QcDQ2/4yINx0o7lQ9HlGu1+mtmDL30REe+wIL+RYT6w6YoNaPNy38Ed0/Yy9naHoYrRbYKMP9fAo8FDKiTBpN1k24l6y86n3QIy2U0zFKXbqH7f1+yUjiR9mKpkkZFN8Mlqs2jC+R+h3F8feBU3dgc5M+UA/6nJqFVaR3/8tzpfSyY4P30qhLt0ear88YFOZPljzSk8bSE1jMuHogY5Nb4Y3JX05nwfv24qVumljqh2coveC5Z91fGp511vc/+yM/S4CNFG97ZkhvtYydtqaIZKIy2Fec89hs0kQYKttwWIECzdxEpfegB2uaK4seAM2DLWxHyrZlE5vlOq3qFa04HxJzHNeoScYcxk91rvjH5eFO1c1jyem1AYmSIzcjH3gyue2cvbeA==
*/