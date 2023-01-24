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
Ts8GMg280/T50P5wQx1NkE3XM2TTMuaD05rHxNwUCvL3x0GkGEJ1kObR2KhgfonjQaNJiUuXdLtjK8YzxamY+JaMERg5hlU1AO74Onif+T+GyOMQjgYzdf/iFeZtEYpZ95TxNerecq/dNYkUKUfMlp6m3iyJX7dyyd9v/74aNLXhmlEBZM+EuSIVwytMlzmAv4EoPEax8SdApBzC7ExaF0TnuNGEjV6VadTFA5+60RTJsQMLz+Onxa9ojYPMINI6p/LuqX7l3QeBxh9FYv8Ekb9AuJRJdS0GiA9ne5PwHq55WSQInOns5Hxxko2oW94zsnPxKky401Kz3hFuE8Qc6UExJiyU85X31ZBWrE5WKoU4KsAZQkjSlIiqGbrMzH59QheHMtF/0XULItMh/DxE18TKFXxNvDNk7biLZfUrHBLeSoZZtx2WxGrEcCQIDt7F5B77YbZvSMsPrw4h8vY+iFyDMHR0JsFpN3HTpy1MNfdAc4QBr8xiP8A6C+lpXPzjGHAlOhTcaQrVnjTaqJ3VkPGX04u+EkrFUqlVflBpwFF5s9qpzXZMdqaKrgL3Kux2N7tizpjjECbutolWSvIqFJ+Ucs8F7khfHVqPgW/cNprzh4SP6IDE70czHdWa0Vb+4a5k9QuoqxMG+9AX/320Sd91AhInOS3iU1HaD+OhksnN/cyb10ebxsCUEwGUkgU8x1U8lTx/E4z4GDxK
*/