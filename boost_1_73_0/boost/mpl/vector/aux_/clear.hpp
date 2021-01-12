
#ifndef BOOST_MPL_VECTOR_AUX_CLEAR_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_CLEAR_HPP_INCLUDED

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
#include <boost/mpl/vector/aux_/vector0.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct clear_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

#else

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< long N >
struct clear_impl< aux::vector_tag<N> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_CLEAR_HPP_INCLUDED

/* clear.hpp
zYjxhTzbVvN1izjsfUJY/Dbldl2SoaVebtWiXrA9RRFQ/SaNfVEadz+sadzGlr2CdovqZj/xI8j8EBaRrhQ0mSr5uF3Ix2imw4PoJNpXbk8eLIymnQUb/9TXm+1Pd7CcSZgsOjrCYmt5DkTl6e/T8HckFp4fV10iPBQL+b2zlkl5sBuBMo1PmXo7GKfTr+nchZhYTWIubb3fNQ5/T8UOR9g9TF+9e4wdUqyf2INRLBRtBFdh
*/