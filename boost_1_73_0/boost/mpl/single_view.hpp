
#ifndef BOOST_MPL_SINGLE_VIEW_HPP_INCLUDED
#define BOOST_MPL_SINGLE_VIEW_HPP_INCLUDED

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

#include <boost/mpl/aux_/single_element_iter.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct single_view
    : iterator_range<
          aux::sel_iter<T,0>
        , aux::sel_iter<T,1>
        >
{
};

BOOST_MPL_AUX_NA_SPEC_NO_ETI(1, single_view)

}}

#endif // BOOST_MPL_SINGLE_VIEW_HPP_INCLUDED

/* single_view.hpp
9+Cuq0p+OGZAxdKr+139p9jzm//U5zcdZfT+v7J3H1BVXGkAx+3d2BDR2KKo2MGKvYTYgooRjTWI8BCU8oSHLahYY4ti7J214ootQYMtscWSGEVjwW4MMZioMWrUVRP3P+99b+bNBCNuds/unsOcc/15L1Pu3LnT7rszw+80Lrx0sAHBl2AhzCUkEdII2aJ4vxvBm2AhzI369zyzO0Pt9/zXf9uhL7M8r5v553Q9CVp/5Zc/
*/