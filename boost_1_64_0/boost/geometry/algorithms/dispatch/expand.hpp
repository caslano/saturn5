// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015, 2017, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DISPATCH_EXPAND_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DISPATCH_EXPAND_HPP

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/tag.hpp>

#include <boost/geometry/strategies/compare.hpp>
#include <boost/geometry/policies/compare.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename GeometryOut, typename Geometry,
    typename TagOut = typename tag<GeometryOut>::type,
    typename Tag = typename tag<Geometry>::type
>
struct expand : not_implemented<TagOut, Tag>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DISPATCH_EXPAND_HPP

/* expand.hpp
rmDty0JvFtsFNkJI5VmvBRZXCSE2PNQ0yoNpLt2B8goZC5HI54ulYffXLdsefnrGr9v/9iUTLKgM4nCzehbyYIVlmboGlviOtYefa3ktqeBScjXB6ID/BxCPuzzw1KDdoB1T/OHRIfViJ4yLDaRS47Aft+HhMlKS8b/UwAMpwbXNT0GsKxFYxx1XS7QZnsxUAXAwNZHv7x+REA3n+Kji7IuJT+go4uGOpJWZAQhZse2rurYLmZcpq99l8uAmNenwLurQbhiynZSxXVwF77nOKlHcZW1ONwR26ZSiWUDQ409R0WTRNoYqjCEXae9XR3bgcrsE1cjsMLFdc9Ng5ie4P5lTRnclVYNlr6aHGWOZMu8xi1flhu+4jI/ek84yPB9m5E2+JZdcj3OZd3zADOr0JzTu6I0yfc4wp4HijkIb33hsP9yjm8GS5mopOETB/pNIvtjvkltHlOLp3OzTsrS3mhs9ZlI6erEhapeHOzrvE0XzAB3QJlPhhPVf5mDSVlLcgMi2cHTpXeCxTl2myFtUgrD5bTWjxZVcau7uOYnqR3rx9kzqp/Fvjl9dOw==
*/