// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2009-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2015.
// Modifications copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_CENTROID_WEIGHTED_LENGTH_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_CENTROID_WEIGHTED_LENGTH_HPP

#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <boost/geometry/algorithms/detail/distance/interface.hpp>
#include <boost/geometry/algorithms/detail/distance/point_to_geometry.hpp>
#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/util/for_each_coordinate.hpp>
#include <boost/geometry/util/select_most_precise.hpp>
#include <boost/geometry/strategies/centroid.hpp>
#include <boost/geometry/strategies/default_distance_result.hpp>

// Helper geometry
#include <boost/geometry/geometries/point.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace centroid
{

namespace detail
{

template <typename Type, std::size_t DimensionCount>
struct weighted_length_sums
{
    typedef typename geometry::model::point
        <
            Type, DimensionCount,
            cs::cartesian
        > work_point;

    Type length;
    work_point average_sum;

    inline weighted_length_sums()
        : length(Type())
    {
        geometry::assign_zero(average_sum);
    }
};
}

template
<
    typename Point,
    typename PointOfSegment = Point
>
class weighted_length
{
private :
    typedef typename select_most_precise
        <
            typename default_distance_result<Point>::type,
            typename default_distance_result<PointOfSegment>::type
        >::type distance_type;

public :
    typedef detail::weighted_length_sums
        <
            distance_type,
            geometry::dimension<Point>::type::value
        > state_type;

    static inline void apply(PointOfSegment const& p1,
            PointOfSegment const& p2, state_type& state)
    {
        distance_type const d = geometry::distance(p1, p2);
        state.length += d;

        typename state_type::work_point weighted_median;
        geometry::assign_zero(weighted_median);
        geometry::add_point(weighted_median, p1);
        geometry::add_point(weighted_median, p2);
        geometry::multiply_value(weighted_median, d/2);
        geometry::add_point(state.average_sum, weighted_median);
    }

    static inline bool result(state_type const& state, Point& centroid)
    {
        distance_type const zero = distance_type();
        if (! geometry::math::equals(state.length, zero)
            && boost::math::isfinite(state.length)) // Prevent NaN centroid coordinates
        {
            // NOTE: above distance_type is checked, not the centroid coordinate_type
            // which means that the centroid can still be filled with INF
            // if e.g. distance_type is double and centroid contains floats
            geometry::for_each_coordinate(centroid, set_sum_div_length(state));
            return true;
        }

        return false;
    }

    struct set_sum_div_length
    {
        state_type const& m_state;
        set_sum_div_length(state_type const& state)
            : m_state(state)
        {}
        template <typename Pt, std::size_t Dimension>
        void apply(Pt & centroid) const
        {
            typedef typename geometry::coordinate_type<Pt>::type coordinate_type;
            geometry::set<Dimension>(
                centroid,
                boost::numeric_cast<coordinate_type>(
                    geometry::get<Dimension>(m_state.average_sum) / m_state.length
                )
            );
        }
    };
};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{


// Register this strategy for linear geometries, in all dimensions

template <std::size_t N, typename Point, typename Geometry>
struct default_strategy
<
    cartesian_tag,
    linear_tag,
    N,
    Point,
    Geometry
>
{
    typedef weighted_length
        <
            Point,
            typename point_type<Geometry>::type
        > type;
};


} // namespace services


#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::centroid


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_CENTROID_WEIGHTED_LENGTH_HPP

/* centroid_weighted_length.hpp
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
*/