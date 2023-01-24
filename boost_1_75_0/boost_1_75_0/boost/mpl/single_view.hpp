
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
KzNIXPkKpkXkzgYuuV+i2NGtJhx/NJdxzcuMr8WXyWanuGJgxs0XtWAgs1Z5wQ1TXiuZC7/4I5CZXAyvaVfN2CwdsWuEsyWLwVKVWlYwROdAGGSXSy4udFAqU5Vpd0iLm+apTHMoqr6zv+7PtbnLVfx05jR56C2R5sLBj0d3yWTN4AJOuhmgDVcV+4quFAhG1GI7TtHqdksY/7X+qPPBL0+x38jpa6ximgBmvL+WmHwZ5QqY4/GWIVI2dy5xGqd5VzBF8AuDl+KV3OAbVRaRSQ6BTSqWSJHm9UK0tqlhs58iKWUUVkVR1WTvbO3vcBxqWZL4z8bTM6kXxRxJVDg6wX71RAxbMY9cBugqatJNOy/12SR/eSuItk/vsCh7UcD+OBLkGu5dBnre5vy8A4b/KqjMcATnHS5zVHDL6Tmjfit0iyqiANhWEVPkooC1h7epuwa8pb4FdyqAsThvpbGpb8If226Xbj0u+Tn6Cl4RO3fQsRPeJPuzIXsiY16vGgbir7fk9LsMB/0qwrHPibiyWS6mKRz8gGfpQwPgWESBFv/VNAEDxbXQ1bQ/Q6fgXv/XZFxZkYt+fRXBq0XtLM/TkMybh6DIAn9NJ1V7g3j9A+/vdsOULBZm+cgMCwcjXCMREfMIoA4eh1svXs1MzWJWTXs1LeaxxIVRQQt8IXkbHQGabzH+wfwnEuUShhwVmo2qHVxf2BuJPrX+1r9i
*/