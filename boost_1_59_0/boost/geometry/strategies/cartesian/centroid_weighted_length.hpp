// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2009-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2015-2021.
// Modifications copyright (c) 2015-2021, Oracle and/or its affiliates.

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

#include <boost/geometry/arithmetic/arithmetic.hpp>

// Helper geometry
#include <boost/geometry/geometries/point.hpp>

#include <boost/geometry/strategies/cartesian/distance_pythagoras.hpp>
#include <boost/geometry/strategies/centroid.hpp>

#include <boost/geometry/util/algorithm.hpp>
#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace centroid
{

template
<
    typename Ignored1 = void,
    typename Ignored2 = void,
    typename CalculationType = void
>
class weighted_length
{
private :
    typedef geometry::strategy::distance::pythagoras<CalculationType> pythagoras_strategy;

    template <typename GeometryPoint, typename ResultPoint>
    struct calculation_type
    {
        // Below the distance between two GeometryPoints is calculated.
        // ResultPoint is taken into account by passing them together here.
        typedef typename pythagoras_strategy::template calculation_type
            <
                GeometryPoint, ResultPoint
            >::type type;
    };

    template <typename GeometryPoint, typename ResultPoint>
    class sums
    {
        friend class weighted_length;
        template <typename, typename> friend struct set_sum_div_length;

        typedef typename calculation_type<GeometryPoint, ResultPoint>::type calc_type;
        typedef typename geometry::model::point
            <
                calc_type,
                geometry::dimension<ResultPoint>::value,
                cs::cartesian
            > work_point;

        calc_type length;
        work_point average_sum;

    public:
        inline sums()
            : length(calc_type())
        {
            geometry::assign_zero(average_sum);
        }
    };

public :
    template <typename GeometryPoint, typename ResultPoint>
    struct state_type
    {
        typedef sums<GeometryPoint, ResultPoint> type;
    };

    template <typename GeometryPoint, typename ResultPoint>
    static inline void apply(GeometryPoint const& p1, GeometryPoint const& p2,
                             sums<GeometryPoint, ResultPoint>& state)
    {
        typedef typename calculation_type<GeometryPoint, ResultPoint>::type distance_type;

        distance_type const d = pythagoras_strategy::apply(p1, p2);
        state.length += d;

        distance_type const d_half = d / distance_type(2);
        geometry::detail::for_each_dimension<ResultPoint>([&](auto dimension)
        {
            distance_type const coord1 = get<dimension>(p1);
            distance_type const coord2 = get<dimension>(p2);
            distance_type const wm = (coord1 + coord2) * d_half; // weighted median
            set<dimension>(state.average_sum, get<dimension>(state.average_sum) + wm);
        });
    }

    template <typename GeometryPoint, typename ResultPoint>
    static inline bool result(sums<GeometryPoint, ResultPoint> const& state,
                              ResultPoint& centroid)
    {
        typedef typename calculation_type<GeometryPoint, ResultPoint>::type distance_type;

        distance_type const zero = distance_type();
        if (! geometry::math::equals(state.length, zero)
            && boost::math::isfinite(state.length)) // Prevent NaN centroid coordinates
        {
            // NOTE: above distance_type is checked, not the centroid coordinate_type
            // which means that the centroid can still be filled with INF
            // if e.g. distance_type is double and centroid contains floats
            geometry::detail::for_each_dimension<ResultPoint>([&](auto dimension)
            {
                typedef typename geometry::coordinate_type<ResultPoint>::type coordinate_type;
                geometry::set<dimension>(
                    centroid,
                    boost::numeric_cast<coordinate_type>(
                        geometry::get<dimension>(state.average_sum) / state.length
                    )
                );
            });
            return true;
        }

        return false;
    }
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