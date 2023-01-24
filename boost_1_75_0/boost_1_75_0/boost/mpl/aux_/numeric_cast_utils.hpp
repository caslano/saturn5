
#ifndef BOOST_MPL_AUX_NUMERIC_CAST_HPP_INCLUDED
#define BOOST_MPL_AUX_NUMERIC_CAST_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/numeric_cast.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>

namespace boost { namespace mpl { namespace aux {

template<
      typename F
    , typename Tag1
    , typename Tag2
    >
struct cast1st_impl
{
    template< typename N1, typename N2 > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : apply_wrap2< 
              F
            , typename apply_wrap1< BOOST_MPL_AUX_NUMERIC_CAST<Tag1,Tag2>,N1 >::type
            , N2
            >
    {
#else
    {
    typedef typename apply_wrap2< 
              F
            , typename apply_wrap1< BOOST_MPL_AUX_NUMERIC_CAST<Tag1,Tag2>,N1 >::type
            , N2
            >::type type;
#endif
    };
};

template<
      typename F
    , typename Tag1
    , typename Tag2
    >
struct cast2nd_impl
{
    template< typename N1, typename N2 > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : apply_wrap2< 
              F
            , N1
            , typename apply_wrap1< BOOST_MPL_AUX_NUMERIC_CAST<Tag2,Tag1>,N2 >::type
            >
    {
#else
    {
        typedef typename apply_wrap2< 
              F
            , N1
            , typename apply_wrap1< BOOST_MPL_AUX_NUMERIC_CAST<Tag2,Tag1>,N2 >::type
            >::type type;
#endif
    };
};

}}}

#endif // BOOST_MPL_AUX_NUMERIC_CAST_HPP_INCLUDED

/* numeric_cast_utils.hpp
KsqLo9qJwbTx2Yv41mhw6ujzpiIrd4hItbw2EVRQ9qw5srMOHv7sBBU5EMZvIfUe29RFoRsVz7nXUkXxX3jBpIFqYxqgQx+AKCONXZYYNXAWjRowBcLfOFn0MexmGut/MLhk/8L1b07WtrQ3d3Kw/Bco+9qTDvrArR6LqTMSLHWbjJiGi6nlC4eoaFTzyfeufvH3A6U06AXrxCu9mWxj2vSBXrF4la38tFoZb2jxiLTSUUQyEXVkg39bZ3KJT9FKoxd+myKAYNik00oVSIdN89jYLzokDFzd3o+PkcUOhssWB/YFAS7Pxsb9ODfdDlbTVsGvFcmiz2Oj9+v5de6/GSFnfmSaqQ1omBzcH77MXTTfPPrl8cONgNpFxgjvl85YHQYZk+xviMVYcrFUsHVQdLB0EFoQnUsG2BQrADa+bC9WJbN7n1Et1JLU6IWJmTbRDxTtSstbDpZlsh11WFfBea2+8i7GvjdMZKK3YCpG1YtWmUZNVYoihgh72RWZ7n4p573hlCDSOfWbqU2lgQZhAKVQzpuGP8o38GGX8d7355cbSz2WrIqjwx+Y2asTw2bgH0yE8SEUR34FJVTXru7DUEIWOKWYjOorlYx0QcTQbjj4j+UOJDIu5uBXrACN5OmLdrKOQBso8oXsqTpG0aTsHCEkkKOu0svrYflyNF54G3MdvlLvr2rwJ4J/9vEvqSnA27AWvVxw5+HV0Blk
*/