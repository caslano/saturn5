
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
jufNwuayJ4v7WydsNj/p7A/3r03YVD2V4y9Pzt/OpyBrK5Tzd5+w69a2XrLL4+9Fl/5eFnbfd+HvhEt/w8LufRf+zCOQtRXylxZ2l2pbJ383ufS3VNg1uPC3w6W/PcLugAt/fS799Qu7f3Dh7ycu/f1M2L3nwp/vG5C1FfIXFXZl2tbJ3/Uu/X1O2H3ehb9Wl/7ahN0+F/6edenveWH3sgt/b7r097awG3bh75RLf4GnxRx5Wj138lf5NGRthfw=
*/