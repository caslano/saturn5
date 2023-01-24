
#ifndef BOOST_MPL_PUSH_FRONT_HPP_INCLUDED
#define BOOST_MPL_PUSH_FRONT_HPP_INCLUDED

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

#include <boost/mpl/push_front_fwd.hpp>
#include <boost/mpl/aux_/push_front_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct push_front
    : push_front_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,T >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,push_front,(Sequence,T))
};


template< 
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct has_push_front
    : has_push_front_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,has_push_front,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(2, push_front)
BOOST_MPL_AUX_NA_SPEC(1, has_push_front)

}}

#endif // BOOST_MPL_PUSH_FRONT_HPP_INCLUDED

/* push_front.hpp
pPWZQSmUigSoxa85lUj4YFM6VOZ+mlWs1LVtKPZ+k9ppmsRpIjjn4zEjIt5OIZmvXB/Hvc9H6HA4LBtJ5KYnxYbiFsak65Apy5i1qm8Bvjs5oV5DiJY8dtjQViMxugH3XMoPZBeEchcqDpIsRPM7swJBxKK9YKwZioXm3o+0N9RXc5vKWDP0/BhYV6K52BYejEMQZqL+mJsHErtbIUAKUFmkxxf6SXCrEOGlK8SrYqbjOsjgU26UkRrLUKmuy43soSkF/vRgaZA6eIahLsUBT/0+C2ta/ikLKxe8Ow3HmtyTq56EPeWhS0+E9Db2jYJoIPqgzyi5J83vKQorgDoftb5VxZsvvdD3C/5Eg35vWZ/GjeFTgQu1MJci6CA4KW+8LE/0dbF6tLpTz7Xm9LuvXPZ3uRYjkn014K0LyfLTp0Cp2wQIYxG4E9kL8boES+R+V1r4bSXc0/eJJfSrZMjn2uEFAR39+d9gT/m+VQz4XnM/MRaIa0QT1elX4rVE6A3amzasUDZHdQzoTmw8CG2lqtUgP+D1XBQMDnN/wK6ZPRtold2g8IiwP/7gFqTkYdo/YDGih2qIK/4NLuCjezyqs0K1uXz1iuWBnHnFlgwMjPZ5/+i8T/X0MPqZZ4tPeOP6ZJzLbflI5Jkot4WL7rKNPBfFP2uDo5d2RAjR99dGwwDrT5+cJyGX6U+ZIT6prfKtoEjV3RyqtT4h+QHx
*/