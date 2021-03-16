
#ifndef BOOST_MPL_SET_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

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
#include <boost/mpl/set/aux_/tag.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/insert.hpp>

namespace boost { namespace mpl {

template<>
struct insert_range_impl< aux::set_tag >
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

#endif // BOOST_MPL_SET_AUX_INSERT_RANGE_IMPL_HPP_INCLUDED

/* insert_range_impl.hpp
PdBVapqhRfYE40C8p5tM1lfRZFICVrHePtVLg6JvfQ9dwcdDOjrB00Z4AGfCRqKSYTm/ZkulWWh8Kod7wcVsatqYAjGkzRpz8vkAvGiN6/a03wzrmMvrYwlIDrxghj24XIrFtYQW8WkUB56tPlcKd8cx1IoRCEMqTYS/a1FmTnRvBAPGMOPJiJ8caCloD8X2JrxRkB3yxmKAnwP4DlvMKGXGIcOH3F2fyNHkcpr781w+q4Q2DOWvoEFBJ4/Hq1U=
*/