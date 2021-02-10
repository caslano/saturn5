
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
e3yUhUPrCmkxY6JRlabHL+yP2pQ2Y4s8X51ucHebh5fO6NeedWhsYx0qB4VWCgvXaMUEv3wqeOjGPsEGzQFNbJsSmTDYtT2VS+lkIODJOIEvkwksHyL2XTpMId/jZ5jcwJM+UCWZQDJNpzcpYe5+5BGba+Wp40dUW1enMI1YxHZaE2loK/hAQ+zztvHYwF6cAgLYk6aM1c51BH8LQSi5w+w8M7ijhuf1owVNdZBgG7VtMbgAx8bV8L4VIHjoBKLQu51UZeBKOS9Ruto6acZSaVejGW9lK197nnz7CgNGDrlxRTB/yaMMgDgO3ANwtFhu8vtVOvKKV8t1TsOcCUVFVHuDtI6wNsEvGcINZpBJL2iaqgfvHsjK0agkDPzRgFpa+Imo4MrW2l0xcThhqQH1dLrQbca8U/8y3du6I7bQ1qXwEThiz7SReLYlfSkUe9Py0cvtenO/fIrYrCiwo/Q1v47Yys8Vz8/Gp/CA2MWztjmgPxV/KPvY079lvYv8f5oEvzhHwdlPfvkVfwNQSwMECgAAAAgALWdKUibLG6IOAgAAIQUAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxODRVVAUAAbZIJGDFVE1v2zAMvQvwfyAy5FLMlt3l0BpGgKArmiJZ
*/