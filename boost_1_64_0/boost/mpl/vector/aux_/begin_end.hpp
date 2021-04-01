
#ifndef BOOST_MPL_VECTOR_AUX_BEGIN_END_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_BEGIN_END_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/typeof.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <boost/mpl/begin_end_fwd.hpp>
#   include <boost/mpl/vector/aux_/iterator.hpp>
#   include <boost/mpl/vector/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct begin_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef v_iter<Vector,0> type;
    };
};

template<>
struct end_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef v_iter<Vector,Vector::size::value> type;
    };
};

}}

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#endif // BOOST_MPL_VECTOR_AUX_BEGIN_END_HPP_INCLUDED

/* begin_end.hpp
wgiZ3Uv8N29uC/6td7C0OUEcopA0aHvT0lzcHx06Vz5BnvgoPrmYyg6+BgAvSTV1DKhohxr6I2S51JxJ26NkFJEfa9JWOFbXeFPJZhIrA4O0bFtsu+ITC4ptL8raHXGoTghtmWv0DmsUGOELCxYG68RD3Ng5G1Pj2PhGDbo5ebKm32qZUVozF0leXEr42z+F0vK0wL+W96RQ1faU/cuO3/5RrRjHwYFKYZgwXbK8+3lMjxNFGlL4Uy2dKgva5U/An/37XRmcRDwqEHQi83dLv3/JNDhfPuGYwLZmYJDURuYP2+gPKTcfgig6rLRwNywz88AlSlPi5724nkMwxnVWuTRFenFIrOc5QYV0n5sZ8mXJW4iPleSaZZu//RIPkcplC6oQD1HSvnYeukNZ05nTDN348nrBubflFCQBFKde0qkZxTaxeMpYXwxK//HRaO6XPSb4ZuiFF2fxEu2vKNxpspWwCopIGtffsTB88RCGEszJTHdCgtC9jnMVc49qT1Iy9Hsb3jArBVj6k7uwJkcOMuzjK2qTHGGlg78CiTZ6C7oNkK6rF161qyPtcQ==
*/