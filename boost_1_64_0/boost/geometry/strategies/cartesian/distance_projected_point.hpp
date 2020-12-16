// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014, 2018, 2019.
// Modifications copyright (c) 2014-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_PROJECTED_POINT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_PROJECTED_POINT_HPP


#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_void.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/arithmetic/dot_product.hpp>

#include <boost/geometry/strategies/tags.hpp>
#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/default_distance_result.hpp>
#include <boost/geometry/strategies/cartesian/distance_pythagoras.hpp>
#include <boost/geometry/strategies/cartesian/point_in_point.hpp>
#include <boost/geometry/strategies/cartesian/intersection.hpp>

#include <boost/geometry/util/select_coordinate_type.hpp>

// Helper geometry (projected point on line)
#include <boost/geometry/geometries/point.hpp>


namespace boost { namespace geometry
{


namespace strategy { namespace distance
{

/*!
\brief Strategy for distance point to segment
\ingroup strategies
\details Calculates distance using projected-point method, and (optionally) Pythagoras
\author Adapted from: http://geometryalgorithms.com/Archive/algorithm_0102/algorithm_0102.htm
\tparam CalculationType \tparam_calculation
\tparam Strategy underlying point-point distance strategy
\par Concepts for Strategy:
- cartesian_distance operator(Point,Point)
\note If the Strategy is a "comparable::pythagoras", this strategy
    automatically is a comparable projected_point strategy (so without sqrt)

\qbk{
[heading See also]
[link geometry.reference.algorithms.distance.distance_3_with_strategy distance (with strategy)]
}

*/
template
<
    typename CalculationType = void,
    typename Strategy = pythagoras<CalculationType>
>
class projected_point
{
public :
    typedef within::cartesian_point_point equals_point_point_strategy_type;

    typedef intersection::cartesian_segments
        <
            CalculationType
        > relate_segment_segment_strategy_type;

    static inline relate_segment_segment_strategy_type get_relate_segment_segment_strategy()
    {
        return relate_segment_segment_strategy_type();
    }

    typedef within::cartesian_winding
        <
            void, void, CalculationType
        > point_in_geometry_strategy_type;

    static inline point_in_geometry_strategy_type get_point_in_geometry_strategy()
    {
        return point_in_geometry_strategy_type();
    }

    // The three typedefs below are necessary to calculate distances
    // from segments defined in integer coordinates.

    // Integer coordinates can still result in FP distances.
    // There is a division, which must be represented in FP.
    // So promote.
    template <typename Point, typename PointOfSegment>
    struct calculation_type
        : promote_floating_point
          <
              typename strategy::distance::services::return_type
                  <
                      Strategy,
                      Point,
                      PointOfSegment
                  >::type
          >
    {};

    template <typename Point, typename PointOfSegment>
    inline typename calculation_type<Point, PointOfSegment>::type
    apply(Point const& p, PointOfSegment const& p1, PointOfSegment const& p2) const
    {
        assert_dimension_equal<Point, PointOfSegment>();

        typedef typename calculation_type<Point, PointOfSegment>::type calculation_type;

        // A projected point of points in Integer coordinates must be able to be
        // represented in FP.
        typedef model::point
            <
                calculation_type,
                dimension<PointOfSegment>::value,
                typename coordinate_system<PointOfSegment>::type
            > fp_point_type;

        // For convenience
        typedef fp_point_type fp_vector_type;

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

        Strategy strategy;
        boost::ignore_unused(strategy);

        calculation_type const zero = calculation_type();
        calculation_type const c1 = dot_product(w, v);
        if (c1 <= zero)
        {
            return strategy.apply(p, p1);
        }
        calculation_type const c2 = dot_product(v, v);
        if (c2 <= c1)
        {
            return strategy.apply(p, p2);
        }

        // See above, c1 > 0 AND c2 > c1 so: c2 != 0
        calculation_type const b = c1 / c2;

        multiply_value(v, b);
        add_point(projected, v);

        return strategy.apply(p, projected);
    }

    template <typename CT>
    inline CT vertical_or_meridian(CT const& lat1, CT const& lat2) const
    {
        return lat1 - lat2;
    }

};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <typename CalculationType, typename Strategy>
struct tag<projected_point<CalculationType, Strategy> >
{
    typedef strategy_tag_distance_point_segment type;
};


template <typename CalculationType, typename Strategy, typename P, typename PS>
struct return_type<projected_point<CalculationType, Strategy>, P, PS>
    : projected_point<CalculationType, Strategy>::template calculation_type<P, PS>
{};



template <typename CalculationType, typename Strategy>
struct comparable_type<projected_point<CalculationType, Strategy> >
{
    // Define a projected_point strategy with its underlying point-point-strategy
    // being comparable
    typedef projected_point
        <
            CalculationType,
            typename comparable_type<Strategy>::type
        > type;
};


template <typename CalculationType, typename Strategy>
struct get_comparable<projected_point<CalculationType, Strategy> >
{
    typedef typename comparable_type
        <
            projected_point<CalculationType, Strategy>
        >::type comparable_type;
public :
    static inline comparable_type apply(projected_point<CalculationType, Strategy> const& )
    {
        return comparable_type();
    }
};


template <typename CalculationType, typename Strategy, typename P, typename PS>
struct result_from_distance<projected_point<CalculationType, Strategy>, P, PS>
{
private :
    typedef typename return_type<projected_point<CalculationType, Strategy>, P, PS>::type return_type;
public :
    template <typename T>
    static inline return_type apply(projected_point<CalculationType, Strategy> const& , T const& value)
    {
        Strategy s;
        return result_from_distance<Strategy, P, PS>::apply(s, value);
    }
};


// Get default-strategy for point-segment distance calculation
// while still have the possibility to specify point-point distance strategy (PPS)
// It is used in algorithms/distance.hpp where users specify PPS for distance
// of point-to-segment or point-to-linestring.
// Convenient for geographic coordinate systems especially.
template <typename Point, typename PointOfSegment, typename Strategy>
struct default_strategy
    <
        point_tag, segment_tag, Point, PointOfSegment,
        cartesian_tag, cartesian_tag, Strategy
    >
{
    typedef strategy::distance::projected_point
    <
        void,
        typename boost::mpl::if_
            <
                boost::is_void<Strategy>,
                typename default_strategy
                    <
                        point_tag, point_tag, Point, PointOfSegment,
                        cartesian_tag, cartesian_tag
                    >::type,
                Strategy
            >::type
    > type;
};

template <typename PointOfSegment, typename Point, typename Strategy>
struct default_strategy
    <
        segment_tag, point_tag, PointOfSegment, Point,
        cartesian_tag, cartesian_tag, Strategy
    >
{
    typedef typename default_strategy
        <
            point_tag, segment_tag, Point, PointOfSegment,
            cartesian_tag, cartesian_tag, Strategy
        >::type type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::distance


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_PROJECTED_POINT_HPP

/* distance_projected_point.hpp
+A85fx7FP2FV8rcTm+HT2AqfwXh8VuUDd8nxGOXyvgOdNg99XIdgJ1mvFi7iw5Z4ObbCvthatn9okPf95VyT6nJpptp4ZPnpNXW5pMhxOUP283TZzzNwMrpxFs7EXJyF8zETr8Us3IBX4V9wNr6P2ajWPwc/xVz8GvPwJ/TgJWRuDtbEAmyBhdgb52IMzsNRuAALcCHejYtwEy7Ge/Fq/Cteg9/itXgGi2U/iXCZ7ypn/9D1oPHvumZ5uHzzHZH5mp9/PnlHOMd4KfMllnG+NTJf+1Lm2898Zv5C/eaLC/bN5/pc4itlvmjmM/O33W++8ZZ0i2W+5g7zjfLOx9/MdEuZ78R54kuzzBfxhcR3nvl2V5F3E8s7i9X+/q46Hpmufq8G6/PXa6ji2Yd91bw4TJUpjsW38Dp8B+/E9/DP+D6q/foD/AwPotqPD2MjEv0QW+HfsQ0ewY54TKWDn2Ic/hPH4OeYgV/htfg13off4EN4Eg/hd/gxnkb1HrMzOBnP4gL8Ae/BH3Er/oJPI5VF8esYhG9jMB7HWhiszn3YA8OxH9bFbKyHf8aGyDyuJtgam2IeXoY3YzPcgi1wJ7bGv2Eb/BTbYtXKnBcxHLvhYOyOcdgLF2JvfBX74FGMwiC2WV+sj1dgKxyulscROAZHYgGOUvHgeHwUk1Bt84kqH5iMAy7hvIHJOAXzcSreiKl4L6bhHpyBr2EGfoBu/AVnYkgo9RhGYR4Owjk4B/PxOixU5Y5F+CXOxWaXUo9hIi7ACbgIC/Fq3IfXYNOq1FvYE5fiCLxexYvLVXnjDWo74kr8FW/ETtUYP4qxuArj8Wa8Fm/B9bgGN+CteD/ehu/iWjyId2FVTtzrMRzvxqG4QW1vvAfvwI34DG7CN3ErZtbgvIo34Hb8Ez6Of8Yn8AQ+iT/iUxhak/OiyjfuxGvwadyLz+CH+ByexBfxHO5R83Nh/BLG48uYgq/gTNyLOfhXlQ98FVfhPtyIr+NOfAOfxzfxZdyPf8O3VHng2/gRvqPKF9/FKlwo/gOH4BEcgR/jIjyKn+AxtX74CY4M53jHxXgcV+Jn+CB+ocoHv1T7CX6NzWpz3GNLPIEF+K0qFzyJd2JYZVfxfmyMZ7EJ/opNsVsdjktMxzZ4B3bGN7ELvoddMZRKMxJnYTfcjd3xc+yh/l6P+wZsjn0wGftjAQ7AO3EgbsRYFT8OU/FjnFq+PscnjsZRmIPxeCuOxnU4Bh/FcfgqJuH3OAHP4TS8nBN0Gg7HGZiA6ViMGfgEZuJezMETmKviQQ+2b8hxiVNxAS7FhXgjLsJduBi/xmV4SSOOM2yDN+AQXIFjcCVOxBsxHVfhbLwTN+A6vA/vwndxPTZuzPGDXXADDsUt6Mb7MA/vV+WPv8eX8AE8qa5Pg+Vd1PKOanUey3cRD6rfw8zXAx/B/vgoxuFjOAGfRDX/DrwFn8Ln8Y/4Az6t1lddd2J9fBYvw+ewL+7GJHwB5+Nf8Fp8Fbfja/gnfB0/wzewSyWOI0zAt1T6+DYuwHdxNX6AG/GgKi/8UO13+DHWDuY4wkb4CY7CT/Fq/AxX4AncgifxUfwO38JTeAB/wVDOO+ewFrqqcL7AILwVK+FDGIwvYAi+hzVQ3TDXxnZYB7tiXUzDeng71sc7sAk+gM1wF7bEY9gKv8DWeFkVjkMcg+1xOXbGe7ELvoRdcR/2xl+wD4ZcwnkPe2M/XIQD8G4ciM/jFfgyRuMhHIZDQzk/YroaT4g34Ti8Dcer9cYk3Ilz8C3Mx8+xAGtzHpmPM3ERzsElKr94HW7DpXgQl+Hl1TheMAqXYzzegG68SZUTrsINeDM+jndgDOeL3+FU3IBL8R68ETc=
*/