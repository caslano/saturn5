// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2016.
// Modifications copyright (c) 2016 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CALCULATE_SUM_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CALCULATE_SUM_HPP

#include <boost/range.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


class calculate_polygon_sum
{
    template <typename ReturnType, typename Policy, typename Rings, typename Strategy>
    static inline ReturnType sum_interior_rings(Rings const& rings, Strategy const& strategy)
    {
        ReturnType sum = ReturnType(0);
        for (typename boost::range_iterator<Rings const>::type
                it = boost::begin(rings); it != boost::end(rings); ++it)
        {
            sum += Policy::apply(*it, strategy);
        }
        return sum;
    }

public :
    template <typename ReturnType, typename Policy, typename Polygon, typename Strategy>
    static inline ReturnType apply(Polygon const& poly, Strategy const& strategy)
    {
        return Policy::apply(exterior_ring(poly), strategy)
            + sum_interior_rings<ReturnType, Policy>(interior_rings(poly), strategy)
            ;
    }
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_CALCULATE_SUM_HPP

/* calculate_sum.hpp
k65HaYsGQ/uQTOLZrYj0nCALeImPACDDxleHIMlWZ97AnsCi3CZpNNaeECjVbKkz9LYkice+zbrqIWmbeMnowpzk28Q93afufo1n5yhjjooOSA91zbWuU+27YhL/MBuLpjk2L6C2A4Q1EyEsFXyWpPWx20au6jestYLVkatz9xIPek/d/i2Z0rVaWwW5C+MzicyrlybIW002fZCiMQNyHOK27pNEHzziUdJIdkSqCYJScz4doWqmFTrgQHZC2YFLl92OGFPQ7xIsLJCWP2a07xf8z57CMATaLD4gmwyhFwqTH3HZaPueORAJkqoiXpU62cSngVeb6pu5z7UpSva0iFfjkbQeYhGuMbFutF4gFdtraEXF5vam1M4Ir058/wLr+2IukAMoeMRHjWW1NjAe0AAejj/x2VMmx0maFEk0plosqN2JJkB6UVvWkayShIImfgSbN58S5I9/PmMZ8rL7x6tur2+GxHoHVAcLS9hrNj4vYDgeDJroINJt1Opvo0qfvqmJleH5gHtEFJQBNTTWfXBUACnVrcsMcQmY7qOI0xJum3Zh5iwoHR+e9nt/Olori8VaRbaQHzuEt+0qR7uPXo/VrFl+QhrhTV9WgZ0XgP8dFNnAqR/sfyFVzvUdlklL0ZYhqKzqRGvEQn0+
*/