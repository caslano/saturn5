// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_INTERSECTS_ANTIMERIDIAN_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_INTERSECTS_ANTIMERIDIAN_HPP

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_system.hpp>

#include <boost/geometry/util/math.hpp>

#include <boost/geometry/algorithms/detail/normalize.hpp>


namespace boost { namespace geometry                  
{

namespace detail { namespace envelope
{


struct intersects_antimeridian
{
    template <typename Units, typename CoordinateType>
    static inline bool apply(CoordinateType const& lon1,
                             CoordinateType const& lat1,
                             CoordinateType const& lon2,
                             CoordinateType const& lat2)
    {
        typedef math::detail::constants_on_spheroid
            <
                CoordinateType, Units
            > constants;
    
        return
            math::equals(math::abs(lat1), constants::max_latitude())
            ||
            math::equals(math::abs(lat2), constants::max_latitude())
            ||
            math::larger(math::abs(lon1 - lon2), constants::half_period());
    }

    template <typename Segment>
    static inline bool apply(Segment const& segment)
    {
        return apply(detail::indexed_point_view<Segment, 0>(segment),
                     detail::indexed_point_view<Segment, 1>(segment));
    }

    template <typename Point>
    static inline bool apply(Point const& p1, Point const& p2)
    {
        Point p1_normalized = detail::return_normalized<Point>(p1);
        Point p2_normalized = detail::return_normalized<Point>(p2);

        return apply
            <
                typename coordinate_system<Point>::type::units
            >(geometry::get<0>(p1_normalized),
              geometry::get<1>(p1_normalized),
              geometry::get<0>(p2_normalized),
              geometry::get<1>(p2_normalized));
    }
};


}} // namespace detail::envelope

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_INTERSECTS_ANTIMERIDIAN_HPP

/* intersects_antimeridian.hpp
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
*/