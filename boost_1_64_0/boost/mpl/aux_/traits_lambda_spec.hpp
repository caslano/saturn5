
#ifndef BOOST_MPL_AUX_TRAITS_LAMBDA_SPEC_HPP_INCLUDED
#define BOOST_MPL_AUX_TRAITS_LAMBDA_SPEC_HPP_INCLUDED

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

#include <boost/mpl/sequence_tag_fwd.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/preprocessor/params.hpp>
#include <boost/mpl/aux_/config/lambda.hpp>

#if !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)

#   define BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC_IMPL(i, trait) /**/

#elif !defined(BOOST_MPL_CFG_MSVC_ETI_BUG)

#   define BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC_IMPL(i, trait) \
template<> struct trait<void_> \
{ \
    template< BOOST_MPL_PP_PARAMS(i, typename T) > struct apply \
    { \
    }; \
}; \
/**/

#else

#   define BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC_IMPL(i, trait) \
template<> struct trait<void_> \
{ \
    template< BOOST_MPL_PP_PARAMS(i, typename T) > struct apply \
    { \
    }; \
}; \
template<> struct trait<int> \
{ \
    template< BOOST_MPL_PP_PARAMS(i, typename T) > struct apply \
    { \
        typedef int type; \
    }; \
}; \
/**/

#endif // BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT


#define BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(i, trait) \
    BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC_IMPL(i, trait) \
    template<> struct trait<non_sequence_tag> {}; \
/**/

#endif // BOOST_MPL_AUX_TRAITS_LAMBDA_SPEC_HPP_INCLUDED

/* traits_lambda_spec.hpp
2sGUVFIyqduTTt+XFvApiIq1T6NJxYVPng5+IS/65e7l7RrDR3tZt2OJN7pBrtaOvv67frKwGWxOFLboRBCnKb1fk4y4x6ps5ZtPWpk4YDQhOrzLTujHCx80aOiv5KWvA/k+QqSDgejonyCVMVC6Rujwik1kGDuiey1s7tfjoIX+zz2EloRhCWc+inb40RHXZh2CYeFCkCSYfVs86Zt5TXsRVBvpIbq/awguuWQrA0QZLS0Fyhd1HhCd3UTmeropwACQtbnxwK3EnR6KCElKZCVVE3qGbLmJ3jWowsUrEx1+Snnx9TaYXv90/5tDjPbJHdehLqZQ6QUtEkB2j16XDkfC2RyQH9SzAvyIwMtTaZ2HZis6EzMsXgKret+sxYJSb+UEdhnV3nosH6QaPGBymMbyiHOyC793GTdH32ZNfuVeuJoRsIG+bg5CT3TWVYW8FdtzW6sty7TN7Wsor7LJngNH8OxWVm2yp4u61M1EzPLEvT3pSdk5g3ZwjL7sJJcVmW4BD3wgbSmmItbuqFs9vnn0hgL15+3x2e8jOieyvfW4Og1PeUo3V3dm9A==
*/