
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
t5vl89vLOnpbraOFv3phLmqtdKwSuviHewr6snf5pY38+uP8BVBLAwQKAAAACAAtZ0pSO+6NyZsCAAAWBgAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE3MDBVVAUAAbZIJGCtVdtO20AQfR/J/zAK4gV12dik0KzcVIhya4FExKA+IKTFHscWzm5kbwL5++7aDgHRG22jyNezs+fMnJOEhioTy4oGEOYq1fZ0T8sHXSbVAE6iaFQf8Pgwqi94ACFfA0LerIEN2MAxlQsqWZUnBGFJs2JpAYk0EpWOM4rvP3aWVHWastzf9jHodnH4FT5LQwKjOb3Dbh8v9MK+8Lvo90SvLyzk+DyCprhAR5dV9Q1P5T3BmbQPznWSpzklbRV/B7/MlStvqwTC766qHEZyIrAT+N3gPUviPbbT7+0Gvf6HDuzHMc0Mu5RqQpXAu6XdCQ60MqQMOyM1MZnAXfdEUWxyrQTGha7oCRMtZ+T4PRqemWkBR3OlliwjaVlZ3fYLwFKtme2a60rbHP/v+vEvzIBNpVzR8N0U22nVYzwocreoGWNc31hI0/IBZMbM6kPthNVTDJWcUqskcG7Bh9xkeDWblDIhYQG8QWAY6+lUqqQpJTjfPBmOo9OR2HSLg9HwMuL+
*/