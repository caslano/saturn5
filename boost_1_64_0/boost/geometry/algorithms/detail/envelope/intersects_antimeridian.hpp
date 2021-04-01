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
yTFlWY9/mSquv5mEzFEpDLhAx1uwo9WAJ20DgR3L/jlHpZo9MRpaDSqEOeYZ7/XqzeppXMoGcaneLOUKWuwwQFoQmSQ661kIHxNRVYMDtw5CjWr/drHfsve7oBJcfEoPLiN2mkWJ+4tjXLgFvy+4tbz7o0TLMucEYSMiUUmWQdn9Fq8rogSK14dpb1yeSIUpwW9nZKPXbLR6WroHLOGjHyhRvxPYRa2XZbZYJK04AUU0L0v3JLBKzAuh5z43Hud3vtxY9dn1rWwsOJc1x77MMavRz1N5v7Ph6QsFtcgDZbzawmrtcY8E5dDLaU7UiPOp24SIztTaGAUb30kMTJZlFnDFcOEbojmuA11AoS+tLoeUgei74eihPgIB4W3aqxietwgdS0tiCHDsk36JpcMv7jI+uSb7WW4eFHaKfKHM3E1jKYAC4Odm4iPpIcmvOF7YCYIEFx1x+eGJ5Y5kNXFHV8pSzP83uyWikk8/2P3MuiAa92/Zha2ck0ZLr5HFBZUM+70SflylWpNXLYJjAkdzyrXsZvZqzI9XVx4zlrftyFj7NFFS0+zCt4xqVA==
*/