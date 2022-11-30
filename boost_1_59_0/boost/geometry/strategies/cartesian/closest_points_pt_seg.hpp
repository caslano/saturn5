// Boost.Geometry

// Copyright (c) 2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_CLOSEST_POINTS_PT_SEG_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_CLOSEST_POINTS_PT_SEG_HPP

#include <boost/geometry/core/coordinate_promotion.hpp>

#include <boost/geometry/geometries/point.hpp>

#include <boost/geometry/strategies/cartesian/distance_pythagoras.hpp>
#include <boost/geometry/strategies/closest_points/services.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace closest_points
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename CalculationType>
struct compute_closest_point_to_segment
{
    template <typename Point, typename PointOfSegment>
    static inline auto
    apply(Point const& p, PointOfSegment const& p1, PointOfSegment const& p2)
    {
        // A projected point of points in Integer coordinates must be able to be
        // represented in FP.
        using fp_point_type = model::point
            <
                CalculationType,
                dimension<PointOfSegment>::value,
                typename coordinate_system<PointOfSegment>::type
            >;

        // For convenience
        using fp_vector_type = fp_point_type;

        /*
            Algorithm [p: (px,py), p1: (x1,y1), p2: (x2,y2)]
            VECTOR v(x2 - x1, y2 - y1)
            VECTOR w(px - x1, py - y1)
            c1 = w . v
            c2 = v . v
            b = c1 / c2
            RETURN POINT(x1 + b * vx, y1 + b * vy)
        */

        // v is multiplied below with a (possibly) FP-value, so should be in FP
        // For consistency we define w also in FP
        fp_vector_type v, w, projected;

        geometry::convert(p2, v);
        geometry::convert(p, w);
        geometry::convert(p1, projected);
        subtract_point(v, projected);
        subtract_point(w, projected);

        CalculationType const zero = CalculationType();
        CalculationType const c1 = dot_product(w, v);
        if (c1 <= zero)
        {
            fp_vector_type fp_p1;
            geometry::convert(p1, fp_p1);
            return fp_p1;
        }
        CalculationType const c2 = dot_product(v, v);
        if (c2 <= c1)
        {
            fp_vector_type fp_p2;
            geometry::convert(p2, fp_p2);
            return fp_p2;
        }

        // See above, c1 > 0 AND c2 > c1 so: c2 != 0
        CalculationType const b = c1 / c2;

        multiply_value(v, b);
        add_point(projected, v);

        return projected;
    }
};

}
#endif // DOXYGEN_NO_DETAIL

template
<
    typename CalculationType = void
>
class projected_point
{
public:
    // The three typedefs below are necessary to calculate distances
    // from segments defined in integer coordinates.

    // Integer coordinates can still result in FP distances.
    // There is a division, which must be represented in FP.
    // So promote.

    template <typename Point, typename PointOfSegment>
    struct calculation_type
        : promote_floating_point
          <
            typename select_most_precise
                <
                    typename coordinate_type<Point>::type,
                    typename coordinate_type<PointOfSegment>::type,
                    CalculationType
                >::type
          >
    {};

    template <typename Point, typename PointOfSegment>
    inline auto
    apply(Point const& p, PointOfSegment const& p1, PointOfSegment const& p2) const
    {
        assert_dimension_equal<Point, PointOfSegment>();

        using calculation_type = typename calculation_type<Point, PointOfSegment>::type;
        
        return detail::compute_closest_point_to_segment<calculation_type>::apply(p, p1, p2);
    }

};

}} // namespace strategy::closest_points


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_CLOSEST_POINTS_PT_SEG_HPP

/* closest_points_pt_seg.hpp
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
*/