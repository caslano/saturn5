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
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
*/