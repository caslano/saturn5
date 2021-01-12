
#ifndef BOOST_MPL_MAP_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

// Copyright Bruno Dutra 2015
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/insert_range_fwd.hpp>
#include <boost/mpl/map/aux_/tag.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>

namespace boost { namespace mpl {

template<>
struct insert_range_impl< aux::map_tag >
{
    template<
          typename Sequence
        , typename /*Pos*/
        , typename Range
        >
    struct apply
        : fold<Range, Sequence, insert<_1, _2> >
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

/* insert_range_impl.hpp
7CB93/0v+Yv2e7xP+T2gfZze7O2zpv13WmX/NZfLD4ul35NUn9p/5OrZspu3z8OVym+p3s9Vut7fSu6Y3lNWfT5O+kcl193aX+jOX6udXKX9obTf5K9atP+Gt/+O/OM78sc8/f6T0l1yo+yi33WS9x/Sq71Z+1zsVrso03v/j9Y+Wdof5Am/UX3erfYgv10l+z71H3rfeK70K9Z70Crn6nfKzz8kP3y1/GGx9k+YUnyQ3e++
*/