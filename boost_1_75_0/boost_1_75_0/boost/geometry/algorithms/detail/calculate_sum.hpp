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
t8W5an/mC8j0Pszfn3bYeW6a6ZKnYvw4KqWRVlO3TeKwaJtRQIyFVHOY+S0xXpX5LU3sVOhcl/o+Hkt2wJZUTnIs/Y5zb2g6bKvjVsg8Ler4WKfilmG5HTdyH5AU5Vywl3MFMl+Jcj6ylSNlZaOhLijnMOw8gZTlBH9tK2cwZP7l17ycob921uceWp9F8HGFKcuZbS/nXsj8TJTzQKdyVmP5SzhalnZju95iL+cYZM6Jck792jnXb8gn8WR25Oyi07r+6072x2lH4NmzKffd4BH790Om7Ij4/iPO97XLLYzn001+xeBn905zoO6IbQ48AJlfiPKWHXHOga1EPoXxICrKjNrXgk5x61qP2Na+M5D5syjvjU71O0PkEZiaE9azg3t3mBr6UXv8N8jccZSXN/CoszyY84+56JEbdYtZOeWobf24GzL/Lcq6x1bWVBiDeyUZOLZRBLiWBtS1v3YeFVjStJz9kHlelHPUKofZR53HHcn52ol3e9/+XZ9CpuczvIybnb7rBy75NL4AvFtB6vjHz3SSnw6HH+CJOTDyqa4xVayw6meEbHguEEvFe+99xqo7xaM9R+7Dm0VbUj/G+RYGGuP/nhE2XfuBOP4M1SFZUvJS/Xk0EZ8ndXgSKoDzrI67tOH79np/ChnlN+L7n3F+/wq8GyX1OTrsd72RsdbS58TgschQuBTT5xUKbsCw2I7DM2ksRlsGrNXw
*/