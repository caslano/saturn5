
#ifndef BOOST_MPL_VECTOR_AUX_PUSH_BACK_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_PUSH_BACK_HPP_INCLUDED

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

#include <boost/mpl/push_back_fwd.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <boost/mpl/vector/aux_/item.hpp>
#   include <boost/mpl/vector/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct push_back_impl< aux::vector_tag >
{
    template< typename Vector, typename T > struct apply
    {
        typedef v_item<T,Vector,0> type;
    };
};

}}

#endif 

#endif // BOOST_MPL_VECTOR_AUX_PUSH_BACK_HPP_INCLUDED

/* push_back.hpp
OlnkUO857dUSx3XBpZd6gonj0kZbb8FFu9bdvTcJ3lzlaC12JRXDiLM67wYmv/di+ptTvGl13l7Vm8tzbWFpFTjT2xLjGNWBi/56DvdfaHOpIXV8emuOs16HySUMNaBhXCAv2Rbz7KiA1jVt++s811m6wiymdVnZkeMs4/moxLGwK4fDLE4TFWt0+nbnOE+A3TPJc+fNiHMuQq9dw2DwuLUaWo8NEOrhSo7LmiIx5OuNeyKe
*/