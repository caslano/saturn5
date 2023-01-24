
#ifndef BOOST_MPL_NEGATE_HPP_INCLUDED
#define BOOST_MPL_NEGATE_HPP_INCLUDED

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

#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/aux_/msvc_eti_base.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/eti.hpp>
#include <boost/mpl/aux_/config/integral.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

namespace boost { namespace mpl {

template< typename Tag > struct negate_impl;

template< typename T > struct negate_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N)
    >
struct negate
#if !defined(BOOST_MPL_CFG_MSVC_ETI_BUG)
    : negate_impl<
          typename negate_tag<N>::type
        >::template apply<N>::type
#else
    : aux::msvc_eti_base< typename apply_wrap1<
          negate_impl< typename negate_tag<N>::type >
        , N
        >::type >::type
#endif
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, negate, (N))
};

BOOST_MPL_AUX_NA_SPEC(1, negate)


#if defined(BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC)
namespace aux {
template< typename T, T n > struct negate_wknd
{
    BOOST_STATIC_CONSTANT(T, value = -n);
    typedef integral_c<T,value> type;
};
}
#endif

template<>
struct negate_impl<integral_c_tag>
{
#if defined(BOOST_MPL_CFG_NO_NESTED_VALUE_ARITHMETIC)
    template< typename N > struct apply
        : aux::negate_wknd< typename N::value_type, N::value >
#else
    template< typename N > struct apply
        : integral_c< typename N::value_type, (-N::value) >
#endif    
    {
    };
};

}}

#endif // BOOST_MPL_NEGATE_HPP_INCLUDED

/* negate.hpp
Mokh7dxzRSKWvH554jGeUt6Ub/IAm18eVo6+K5JGuL7TH1qUrZRqtODSw1oW52AwlBFE0oln2Pz2e0wsxHOOCACAK/KQee32P9F0rf0IfuQ92Y7lX9Io7QO7u55v3H+4lDhQr15R2VWwb3vzoNk07ZIEhzhIP4aQk76Crx9/ezcijan4mCiQQXhHc1xWVvvoXr8euN+rtYhexrjVDLwdG0JOX+m1C5pz7DpWYQAacDQQzkd1JWknA4r3/NsN0TD+cLAiKywcC3kPS4phT5V+ddgsgn34i4xtdiNZxBiWCmWe1IXUhelezOkoMP471jspzEbERoKF4BPpC0lf/IVwT+TG/AVHklEI1ocICalPWDJSmC2o1kvexFjp3nkDz5R7mHuce5/2GE0Jb1j3CKmpvOLNhJmXGLhEQz3RnYidZNI2OatvVzKGvT/cvKdm8yrnLINxRmfIGCQcCsSwSfXKH+UOYtnLUyyMLkF27ZjzV2nC0maVY6aVz3ftBMVSI086S6wV9WW+cGeUWPJnfyNKkTshuPWmr8TIXrf+02KhkidoUlIz0eGgqKgXnGZOvO+lMBd7kl6TUafrpU4hZFPmujSuGBITYzEbxvBwEF14UarKlitrr760HpPXOIowE/mKS8/frC6c4pyENbScrLWaQyZUMYduu0rrPvG52XrhgSuTRCgoat/bW+8o13/z4XOckVTiK9bscc1FCqE5
*/