
#ifndef BOOST_MPL_VECTOR_AUX_POP_BACK_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_POP_BACK_HPP_INCLUDED

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

#include <boost/mpl/pop_back_fwd.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <boost/mpl/vector/aux_/item.hpp>
#   include <boost/mpl/vector/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct pop_back_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef v_mask<Vector,0> type;
    };
};

}}

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

#endif // BOOST_MPL_VECTOR_AUX_POP_BACK_HPP_INCLUDED

/* pop_back.hpp
1pd9X4s4eGWFnY2+JLV7iW9G3Eakw5t7J4s4TH6u/sK8k60bbVbr//xXGY5brut62mLUm7X5G/hNhK9kbQIm1yzO91qNuuTv8vUMPr+03lhwkSS2DH8yHKsLbPdLf7ac/BvUi1l8eXWt5pQ51LbXPQtmT95Q6xlmrZzcK+LQwfdyzdfnXcVWTJZHbdfgV9rowZB/n4jPDVPoL6djHNYi0pigGrQ4iwa1+5+YixZfa5o3kANx
*/