
#ifndef BOOST_MPL_AUX_HAS_KEY_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_HAS_KEY_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
// Copyright David Abrahams 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/has_key_fwd.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>

namespace boost { namespace mpl {

// no default implementation; the definition is needed to make MSVC happy 

template< typename Tag > struct has_key_impl
{
    template< typename AssociativeSequence, typename Key > struct apply;
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2,has_key_impl)

}}

#endif // BOOST_MPL_AUX_HAS_KEY_IMPL_HPP_INCLUDED

/* has_key_impl.hpp
jtiD2IhYG+PDoC0g3X/ENXrRgM6nOBZdqdtUog4Wv4ZJaxsYlCZFK11a4X5eJziT2IV6BYf/O0dHu6lhON/9fv8HvTx+vP969fUSDkvlmkPGgtLfcDeFXVcf/aDzzx+vrj/NO0liut28VVW3+PkvmMK7d6AyODzExU/fgf25j8OO4O1b2G6gcMYy9cq25laj6YiuyRd+u7anQrH9X+HfUEsDBAoAAAAIAC1nSlIXtiEFqgMAABsHAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjAxNVVUBQABtkgkYJ2VUW/bNhDH3/UpburSJkBsWortxKrsoojbNFvSBIm37GkDLZ0sIhIpkFRtv/Sz7yjJdrINGFDAsEXqePe/393RsUVjE25w5sVCZop+nnG7Vjo1M+8WLS+EfPa+LBb3zRdcfVp4MTuYxKw95b3x3sAj6m+oe0ak6MUaq2JLBim3HKRKckyep/4WjT9rXLGgH0A4GMDdr96cW4zgCdNT2oFfakk/QQjBMBpOIjK5ul14rfMInOCeaRYs48/oXSppUdreDcqVzSMYjd2WxMQKJSNICmUORotthc7HxrLclsV+fy5MpYxoj2SiQMlLnLovUjJ6D0nOtUE7zWopt+9BVc5yaqzmcoXe
*/