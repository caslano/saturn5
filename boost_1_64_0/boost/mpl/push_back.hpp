
#ifndef BOOST_MPL_PUSH_BACK_HPP_INCLUDED
#define BOOST_MPL_PUSH_BACK_HPP_INCLUDED

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

#include <boost/mpl/push_back_fwd.hpp>
#include <boost/mpl/aux_/push_back_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct push_back
    : push_back_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,T >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,push_back,(Sequence,T))
};


template< 
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct has_push_back
    : has_push_back_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,has_push_back,(Sequence))
};


BOOST_MPL_AUX_NA_SPEC(2, push_back)
BOOST_MPL_AUX_NA_SPEC(1, has_push_back)

}}

#endif // BOOST_MPL_PUSH_BACK_HPP_INCLUDED

/* push_back.hpp
fvCD6U5+EF2ckx339gUh9taEKVGRtP7MofSehCiDAXQg4jCu3aEbm1iag9b96qiOzo2g6gQDvxWVwU10Ab8o1sH74wZcQUy/wzmpAKwsCLAP6PqNdD6aP8htAVz+uOC//3XvhN/v35zV7M+yrB6ry78eoES4rf8m/uDmsYQRCw1sycQ4BEKdnWfO4Z/8MGobCrb9cui1BBf26S8PQCnS9I5q27/m3Ogt9Tv/KEiC5bDWeNofPqkZS4Bd3UYa242ybqhuzM9d3pXEMlSoyAhnNjVaH8sZwiPp2X0EqmMXT++Py+hMQS6j4LosHsK1a/mwb1bwct2sEFxGGzkKdIBvsvMqlVSaPS6vt+0lC1l3XK8AR6cKmdIvldQWcuw/7btgVUfcP3WKGgin2jXsLC4ikc3OtHPJqKJqoQqSXGkMuFQvPnHbGSKX9kMp3nT2Hu+WvVm9o6JvRerUfiZXgxHmApZ+y+L4K9512gVgDD1Iu8Vp/FiAFfj+wME4xwJNxQwziiFY4TYCpdotSmAyvSmcPhGYNYEVg50jr19xEyOTEvuIdN9xRNKTIZYDHw==
*/