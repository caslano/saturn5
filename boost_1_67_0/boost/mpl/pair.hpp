
#ifndef BOOST_MPL_PAIR_HPP_INCLUDED
#define BOOST_MPL_PAIR_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/msvc_eti_base.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/eti.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    >
struct pair
{
    typedef pair type;
    typedef T1 first;
    typedef T2 second;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,pair,(T1,T2))
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(P)
    >
struct first
{
#if !defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG)
    typedef typename P::first type;
#else
    typedef typename aux::msvc_eti_base<P>::first type;
#endif
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,first,(P))
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(P)
    >
struct second
{
#if !defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG)
    typedef typename P::second type;
#else
    typedef typename aux::msvc_eti_base<P>::second type;
#endif
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,second,(P))
};


BOOST_MPL_AUX_NA_SPEC_NO_ETI(2, pair)
BOOST_MPL_AUX_NA_SPEC(1, first)
BOOST_MPL_AUX_NA_SPEC(1, second)

}}

#endif // BOOST_MPL_PAIR_HPP_INCLUDED

/* pair.hpp
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
*/