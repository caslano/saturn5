// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_SELECT_COORDINATE_TYPE_HPP
#define BOOST_GEOMETRY_UTIL_SELECT_COORDINATE_TYPE_HPP


#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{


/*!
    \brief Meta-function selecting the most precise coordinate type
        of two geometries
    \ingroup utility
 */
template <typename T1, typename T2 = void, typename T3 = void>
struct select_coordinate_type
{
    typedef typename select_most_precise
        <
            typename coordinate_type<T1>::type,
            typename coordinate_type<T2>::type,
            typename coordinate_type<T3>::type
        >::type type;
};

template <typename T1, typename T2>
struct select_coordinate_type<T1, T2, void>
{
    typedef typename select_most_precise
        <
            typename coordinate_type<T1>::type,
            typename coordinate_type<T2>::type
        >::type type;
};

template <typename T1>
struct select_coordinate_type<T1, void, void>
{
    typedef typename select_most_precise
        <
            typename coordinate_type<T1>::type
        >::type type;
};

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_SELECT_COORDINATE_TYPE_HPP

/* select_coordinate_type.hpp
oBtV3p1mR2NUlBGpaX7iEZzChYqly+bHKJsu9gs78diTqOJ/Vz8I7HfaZGQT67pQIjuDBBZcJHoSGRm6tXZXVRSQP4RB/XxIfA6aRiai/A0glOjEw0IkXL6P8gt5JnT8TJH+D/7I6Z/DO3RAHMxTRDGGV73dGNAtDdvvVf2MtULHH79kle38+V6tVjkumFdJj9xHC/SI6r/cedkfdsmScYhyQJa046oIEYQ2ryGhzpWBScFJ5rCsyzgC5eWMS8a7fsaRAuHZ89GfeFiOOxzOI1MHDWChR/rLlFDidlnWN27q7MXjbq0iLq3XchIEz6LahbyRX6Nw+oKjCnefJrKV1aIh+rqJE9T8pnUCT8LuPPpn7zRorbrByYTrNRgSpSiCNqwFDle16LRzlNDrVtlRMBqtDblx+8egpaMAPC0kPog2r2ThDPeHBrG5hOOClJkllfnv9n/Aj8ve6YKB6QEX8lgqOtgej0GeU5hYNT+HXrqH/cSdR/7YC+0LC0S2BxFKMbqOgvw+r3Okgev3SVA2cBd1EjA85aZCXZGbrEDCXU+aVaVhZr6wWd4etw==
*/