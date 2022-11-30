// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_PROJECTED_POINT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISTANCE_PROJECTED_POINT_HPP


#include <type_traits>

#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/arithmetic/dot_product.hpp>

#include <boost/geometry/strategies/tags.hpp>
#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/default_distance_result.hpp>
#include <boost/geometry/strategies/cartesian/closest_points_pt_seg.hpp>
#include <boost/geometry/strategies/cartesian/distance_pythagoras.hpp>
#include <boost/geometry/strategies/cartesian/point_in_point.hpp>
#include <boost/geometry/strategies/cartesian/intersection.hpp>

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
        
        auto closest_point = closest_points::detail::compute_closest_point_to_segment
            <calculation_type>::apply(p, p1, p2);

        return Strategy().apply(p, closest_point);
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
            std::conditional_t
                <
                    std::is_void<Strategy>::value,
                    typename default_strategy
                        <
                            point_tag, point_tag, Point, PointOfSegment,
                            cartesian_tag, cartesian_tag
                        >::type,
                    Strategy
                >
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