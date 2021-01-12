// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_PROMOTE_FLOATING_POINT_HPP
#define BOOST_GEOMETRY_UTIL_PROMOTE_FLOATING_POINT_HPP


#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_integral.hpp>


namespace boost { namespace geometry
{


/*!
    \brief Meta-function converting, if necessary, to "a floating point" type
    \details
        - if input type is integer, type is double
        - else type is input type
    \ingroup utility
 */

template <typename T, typename PromoteIntegerTo = double>
struct promote_floating_point
{
    typedef typename
        boost::mpl::if_
        <
            boost::is_integral<T>,
            PromoteIntegerTo,
            T
        >::type type;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_PROMOTE_FLOATING_POINT_HPP

/* promote_floating_point.hpp
7boVbey6nm20vMAqd21AXdYAXrDyJnX1fqt5K88YtTmoPao3e+3t9MwYrqEbl5E5zpN7SJVlp2dy9U9Ghn23mLKrVV1qenpWmnXTbMw4504huy4rJSklSb5JHjxuUoxT+Vv19+JiuaBMNrDqGtl1ScnJcQlRydhM2j1BI7uqEVqiV7GiZZ37l3rv2jJU7qUgtZ/R0M4GJqrf+loBvpT/WoH19hiFz5YK9xNae3M9VdF2NPU1
*/