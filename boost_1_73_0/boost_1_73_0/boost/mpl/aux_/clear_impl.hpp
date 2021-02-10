
#ifndef BOOST_MPL_AUX_CLEAR_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_CLEAR_IMPL_HPP_INCLUDED

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

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/eti.hpp>

namespace boost { namespace mpl {

// no default implementation; the definition is needed to make MSVC happy

template< typename Tag >
struct clear_impl
{
    template< typename Sequence > struct apply;
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1, clear_impl)

}}

#endif // BOOST_MPL_AUX_CLEAR_IMPL_HPP_INCLUDED

/* clear_impl.hpp
kRO2Ej62/r/8T1BLAwQKAAAACAAtZ0pSi64xoywFAACyCwAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDIwMDdVVAUAAbZIJGDlVm1P3EYQ/m6J/zBxSgIRvvW9Ebj4LoqAJKRQEFzSSlEa7dnr8wp71/KuOe5Lf3tn1vca0lRtP1ZC4J2dfebZZ2ZniKwwNuZGjLxIqlTjnzsxn+kqMSPvUlieS3XnvR+Pr90veHc29oIP3tvzizMvYmvXiDWnvafeU7gV1b2oAiMT4UWVKPM5OiTcclA6zkR8N/TnwvgjB8narTZ0whCufvZOuRUDGGf1AXTa8KFWuNHuQLs36IeDsAPvLsdeAz4AIh4Yt2ApvxPeiVZWKBtcCDW12QB6HTIpEVup1QDiXJu103heCsJ4sCyzRb6yn0pTaiObI6nMheKFGNIvpPjyFcQZr4yww7RWav4KdEmeQ2MrrqbCe0vWIBM8GQDeEH8871YXwmZSTSERuUS2IoG00gVwBU7SShhdVzFKxUgj0nKhmRPzJJdErBEzdosRmseZNHgU1wa0ApsJxJ/UU0gFt3UlwGrgea5nUBv6RtKQyArV0NXcGfBD0DkEC66QTQLBB9C1LWsLUh3gOSJNwCcfby6+js9ux6fnN3DP
*/