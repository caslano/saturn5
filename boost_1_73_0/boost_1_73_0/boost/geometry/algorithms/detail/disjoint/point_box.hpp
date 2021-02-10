// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland

// This file was modified by Oracle on 2013-2018.
// Modifications copyright (c) 2013-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_POINT_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_POINT_BOX_HPP

#include <cstddef>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/dispatch/disjoint.hpp>
#include <boost/geometry/strategies/disjoint.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{


/*!
    \brief Internal utility function to detect if point/box are disjoint
 */
template <typename Point, typename Box, typename Strategy>
inline bool disjoint_point_box(Point const& point, Box const& box, Strategy const& )
{
    // ! covered_by(point, box)
    return ! Strategy::apply(point, box);
}


}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Point, typename Box, std::size_t DimensionCount>
struct disjoint<Point, Box, DimensionCount, point_tag, box_tag, false>
{
    template <typename Strategy>
    static inline bool apply(Point const& point, Box const& box, Strategy const& )
    {
        // ! covered_by(point, box)
        return ! Strategy::apply(point, box);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_POINT_BOX_HPP

/* point_box.hpp
bBho8xG9Pr3sXHUujn9qX7U8p14OgeIIaCZ/Xgn6TFywt3Zdggjf0FGse2fhygmeOfg1RyRlJr8WK5LwW+slWWWnfEw1Zyk+sjbbPh+Xk9ZRUNpJruUgSb0PD3sruLJdCSDBlyAALO/xCN0XKcLOk5QK4tYom8rX0Jk6NAOt5RCeGk4ASOyf3UjVg93l74Jsl+fUfqj85AKel+2qERP4I359tAjWuwPGIG29jzKUjMTsCDSQjMn2YIOcphYlAv7vfHsFIho+IXHZgMwB9SO4CJ+EWgLloLkvKJvwk7jgkwlJccvyHMhqeCU+w7vlueawGUsQrVU8w+iEgzTX5ZrTyT1zom6DHr9NEb8uDhcoNz+fIFuQYgqdpORyGuXRdD7inERUG1Vz7bA24uVPFsFvji+Un4B+vUTaDDwWOML5I1kYlkDHo7aM51NkcpLSlTzqHL0nTXpcYAFCV3FZTT86J+mvcZMsBCFLCO3SbZdohV/vJV0bqP1iZK45COf+caWnU7JeMD9gS6Z4XkYsdmCKxyhj1z32xuU2ODE3GyVS2fQ7znWnjq6v3pJtrnvSueqenvxVfU9zXnfeXl5h7jI8qz/+4Q/f/4Eo6afBgPNb6v7iGnPxc/vy9dnFh8anpvobTNf4tO3kNOZenz+r
*/