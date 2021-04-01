
#ifndef BOOST_MPL_AUX_POP_FRONT_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_POP_FRONT_IMPL_HPP_INCLUDED

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

#include <boost/mpl/pop_front_fwd.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>

namespace boost { namespace mpl {

// no default implementation; the definition is needed to make MSVC happy

template< typename Tag >
struct pop_front_impl
{
    template< typename Sequence > struct apply
    // conservatively placed, but maybe should go outside surrounding
    // braces.
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) 
    {
        typedef int type;
    }
#endif
    ;
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1, pop_front_impl)

}}

#endif // BOOST_MPL_AUX_POP_FRONT_IMPL_HPP_INCLUDED

/* pop_front_impl.hpp
UTFsVh9cz0BgtYUVwM2d/3BZuiebSaOKosaV90lvx7RZD1i0hkI9L62g55kmv0FwZJZwZuFaQYfQwuXSJUlijs3mNdLdTmhN/WBZr4PGPZxdFBPDNwqhHk+oDtlksaRqww87yNvCUfGFPioydD2xpTayzEio14yZGEfabCZgOmFuJ/BpGGOlUJVTm5QBuRBve8YQTwoDXOXtqvpPOHiun/Kyuy7Q7oDzUp9sEZRvxxwEhLeDDsOQu4Nw5Ldno/2ZPvlMPaXwy+csOM1kTTBwV4Pi8UAYKfQYZoQ7swlbcqKz0weF41YDC9LqjJ7fO7Y/BmJDBPiGwjK1OvMB1E0ovdje/A2db+a/hTci0+GtMIJuiol8Md2BCgIaaRFiBdAlDRwl3+rBp5VV96/gn0639xwkf71E2yxTrwME3H3vHUnljXc3vzKObJnfNzgPLqJ/ltAF1Is08TegUM4LwTqixT2A/zN9aY9qWqarn0PH1gJqsivnuPBSAibGd0o/NTDJvGlSnva0NdErmTvxxai6K8aopCDg1M8xYE5R0b0xr0UUX6i2WxR/um1PPQ==
*/