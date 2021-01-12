// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_PROJECTIONS_IMPL_FUNCTION_OVERLOADS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IMPL_FUNCTION_OVERLOADS_HPP

#include <cmath>

namespace boost { namespace geometry { namespace projections
{

// Functions to resolve ambiguity when compiling with coordinates of different types
/*
template <typename T>
inline T atan2(T const& a, T const& b)
{
    using std::atan2;
    return atan2(a, b);
}
*/

template <typename T>
inline int int_floor(T const& f)
{
    using std::floor;
    return int(floor(f));
}

}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_IMPL_FUNCTION_OVERLOADS_HPP

/* function_overloads.hpp
xqv0lubwvlYj20Du6/DW2/xtTEd5dQkVCwbbYN+V6uimQplxtc2+D72K7EGDtnV/o2RtnYyVrY3Nuu5vkqy9q7mRFtq9CgZrn4qthsE6ytprM6oAr0zDYJ2GKd3nklRPF2/saOukFrcEinfFekX39m6qXWtbqr2Fugfr1kzqTZu13lSr9NmJQrE0nh/dpfVZc6n0pndavbqpvaspM6kfqhJy2fdUR3JaiNCXrMzVk5R8qt5O
*/