
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
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
*/