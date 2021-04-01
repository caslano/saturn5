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
OkvPJF3KxqciYp09Iroo9EJQ7kPCQKsmKkGC0itwGwEw8aE/mwxkIorXxtVWhTLphN7tFSbbAz49c+5iIp1aEgqkX7C2r09bBVlOY/JN4eequx9ULOHuud4ZTiAILPcLbe2E7+tQqY2TdRMTsvGvfCTsoNQJW87kcfXQzJWAxHFYRGfPdGuLE+O0xmj+zGgzBiF2atvv5nEynP6cY/iioRNP3yuVAYMtgfW3Pvc6lPs2CPMcfrbti039WjQF7qwE5nrE6Z0Bv1OsCuHkuZ9ckSDrMyAPYQEsezAmZN7ZchvDRke73fduBjUt+qvhWbUWDXvM2WElprerRb2HRzMBg1ZYr+/cDHruavYg8RPdK8UdmLdTWZ3Nh3F3eiUczPSk2sUfBe9o+8HvSEIz+AAq5PL1CuRZ3hrNxCgPL5TA5RivVNYf34NCwe20bxtzc0JihbjDNqBs+YylRqfAGLtY1C4faGHzx7CBH8pwqgb0bsZIOHa2UUItA1PAtwmEmf1K/hfywUmLVlh8VRpZAK6UzUfFBJsPojYjcl6D/OHOVtJ+/yoq/OJ71N/Y4A==
*/