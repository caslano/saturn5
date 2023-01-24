
#ifndef BOOST_MPL_LIST_LIST0_HPP_INCLUDED
#define BOOST_MPL_LIST_LIST0_HPP_INCLUDED

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

#include <boost/mpl/long.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/list/aux_/push_front.hpp>
#include <boost/mpl/list/aux_/pop_front.hpp>
#include <boost/mpl/list/aux_/push_back.hpp>
#include <boost/mpl/list/aux_/front.hpp>
#include <boost/mpl/list/aux_/clear.hpp>
#include <boost/mpl/list/aux_/O1_size.hpp>
#include <boost/mpl/list/aux_/size.hpp>
#include <boost/mpl/list/aux_/empty.hpp>
#include <boost/mpl/list/aux_/begin_end.hpp>
#include <boost/mpl/list/aux_/item.hpp>

namespace boost { namespace mpl {

template< typename Dummy = na > struct list0;

template<> struct list0<na>
    : l_end
{
    typedef l_end type;
};

}}

#endif // BOOST_MPL_LIST_LIST0_HPP_INCLUDED

/* list0.hpp
yX1+dGC4U3CGYxhe/Jisv1Lv3KK4AyiQxQIDzeIZimu/jm9vmLok6/S1WxHd8dpk7+5ZZ8QugTS+/Tl8j0Lj5/CA7gJCuF+A+pfe1XOPN1hRRp+RCtMz5YtT19T9DHia4H12Z0W3db7g+70se4vmIebHAhkTsrY0KKVRv49LpSI7LbmfIbcrLZ7+tqtkfkZ2DGJex28j2aiFmnnbc/hKYFzx7pER/IwuppgmezY33UL0mWmGe3vBOPpEB37YChdsZ30TesEYUm16/hNhZx0Th5fE8Ssc7u7uXlwWKW4FihQpWtzdvbhTHIq7u/+QxaU4izss7m4Lu2e5XC53l3v/vLy8yWT+m3wy851hmWpfe92OPiffIvIFuAPmKXxNjvMHumybTMkS8mUkMV75R3KOqmqD5J9fxnKPD6wd1kjWY8D1izCUjMCmbKkfeQf7g/GXMP0ODlPYdkQHUSOFC9Ve4BATNgC75ZxKRjTsCzYWnQh24sdGRkppd1pPnm/rcRdyognecDf0plimXHgzmZzdEBxW2mBk2j9wxKKMZKhMJfZSogKHPgxJyl0JxGFQI+JIR2HTxkVRW5PMlz3g0zI+iMY/DUbRRRVHmUWBo9SHeKPwojr2xaKfXLIk4p94o6xwrHCOzAP4M2W2WMJ+eAemBerVZEt2R33EEQ4LH6PjbDzN7x9tsQn4nK1wJt9c6f8tkfibCEBYQLA4svnk
*/