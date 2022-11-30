// Boost.Geometry

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2019.
// Modifications copyright (c) 2013-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISJOINT_SEGMENT_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISJOINT_SEGMENT_BOX_HPP


#include <cstddef>
#include <utility>

#include <boost/numeric/conversion/cast.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/calculation_type.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/algorithms/detail/assign_indexed_point.hpp>

#include <boost/geometry/strategies/cartesian/point_in_box.hpp>
#include <boost/geometry/strategies/disjoint.hpp>


namespace boost { namespace geometry { namespace strategy { namespace disjoint
{

namespace detail
{

template <std::size_t I>
struct compute_tmin_tmax_per_dim
{
    template <typename SegmentPoint, typename Box, typename RelativeDistance>
    static inline void apply(SegmentPoint const& p0,
                             SegmentPoint const& p1,
                             Box const& box,
                             RelativeDistance& ti_min,
                             RelativeDistance& ti_max,
                             RelativeDistance& diff)
    {
        typedef typename coordinate_type<Box>::type box_coordinate_type;
        typedef typename coordinate_type
            <
                SegmentPoint
            >::type point_coordinate_type;

        RelativeDistance c_p0 = boost::numeric_cast
            <
                point_coordinate_type
            >( geometry::get<I>(p0) );

        RelativeDistance c_p1 = boost::numeric_cast
            <
                point_coordinate_type
            >( geometry::get<I>(p1) );

        RelativeDistance c_b_min = boost::numeric_cast
            <
                box_coordinate_type
            >( geometry::get<geometry::min_corner, I>(box) );

        RelativeDistance c_b_max = boost::numeric_cast
            <
                box_coordinate_type
            >( geometry::get<geometry::max_corner, I>(box) );

        if ( geometry::get<I>(p1) >= geometry::get<I>(p0) )
        {
            diff = c_p1 - c_p0;
            ti_min = c_b_min - c_p0;
            ti_max = c_b_max - c_p0;
        }
        else
        {
            diff = c_p0 - c_p1;
            ti_min = c_p0 - c_b_max;
            ti_max = c_p0 - c_b_min;
        }
    }
};


template
<
    typename RelativeDistance,
    typename SegmentPoint,
    typename Box,
    std::size_t I,
    std::size_t Dimension
>
struct disjoint_segment_box_impl
{
    template <typename RelativeDistancePair>
    static inline bool apply(SegmentPoint const& p0,
                             SegmentPoint const& p1,
                             Box const& box,
                             RelativeDistancePair& t_min,
                             RelativeDistancePair& t_max)
    {
        RelativeDistance ti_min, ti_max, diff;

        compute_tmin_tmax_per_dim<I>::apply(p0, p1, box, ti_min, ti_max, diff);

        if ( geometry::math::equals(diff, 0) )
        {
            if ( (geometry::math::equals(t_min.second, 0)
                  && t_min.first > ti_max)
                 ||
                 (geometry::math::equals(t_max.second, 0)
                  && t_max.first < ti_min)
                 ||
                 (math::sign(ti_min) * math::sign(ti_max) > 0) )
            {
                return true;
            }
        }

        RelativeDistance t_min_x_diff = t_min.first * diff;
        RelativeDistance t_max_x_diff = t_max.first * diff;

        if ( t_min_x_diff > ti_max * t_min.second
             || t_max_x_diff < ti_min * t_max.second )
        {
            return true;
        }

        if ( ti_min * t_min.second > t_min_x_diff )
        {
            t_min.first = ti_min;
            t_min.second = diff;
        }
        if ( ti_max * t_max.second < t_max_x_diff )
        {
            t_max.first = ti_max;
            t_max.second = diff;
        }

        if ( t_min.first > t_min.second || t_max.first < 0 )
        {
            return true;
        }

        return disjoint_segment_box_impl
            <
                RelativeDistance,
                SegmentPoint,
                Box, 
                I + 1,
                Dimension
            >::apply(p0, p1, box, t_min, t_max);
    }
};


template
<
    typename RelativeDistance,
    typename SegmentPoint,
    typename Box,
    std::size_t Dimension
>
struct disjoint_segment_box_impl
    <
        RelativeDistance, SegmentPoint, Box, 0, Dimension
    >
{
    static inline bool apply(SegmentPoint const& p0,
                             SegmentPoint const& p1,
                             Box const& box)
    {
        std::pair<RelativeDistance, RelativeDistance> t_min, t_max;
        RelativeDistance diff;

        compute_tmin_tmax_per_dim<0>::apply(p0, p1, box,
                                            t_min.first, t_max.first, diff);

        if ( geometry::math::equals(diff, 0) )
        {
            if ( geometry::math::equals(t_min.first, 0) ) { t_min.first = -1; }
            if ( geometry::math::equals(t_max.first, 0) ) { t_max.first = 1; }

            if (math::sign(t_min.first) * math::sign(t_max.first) > 0)
            {
                return true;
            }
        }

        if ( t_min.first > diff || t_max.first < 0 )
        {
            return true;
        }

        t_min.second = t_max.second = diff;

        return disjoint_segment_box_impl
            <
                RelativeDistance, SegmentPoint, Box, 1, Dimension
            >::apply(p0, p1, box, t_min, t_max);
    }
};


template
<
    typename RelativeDistance,
    typename SegmentPoint,
    typename Box,
    std::size_t Dimension
>
struct disjoint_segment_box_impl
    <
        RelativeDistance, SegmentPoint, Box, Dimension, Dimension
    >
{
    template <typename RelativeDistancePair>
    static inline bool apply(SegmentPoint const&, SegmentPoint const&,
                             Box const&,
                             RelativeDistancePair&, RelativeDistancePair&)
    {
        return false;
    }
};

} // namespace detail

// NOTE: This may be temporary place for this or corresponding strategy
// It seems to be more appropriate to implement the opposite of it
// e.g. intersection::segment_box because in disjoint() algorithm
// other strategies that are used are intersection and covered_by strategies.
struct segment_box
{
    typedef covered_by::cartesian_point_box disjoint_point_box_strategy_type;

    static inline disjoint_point_box_strategy_type get_disjoint_point_box_strategy()
    {
        return disjoint_point_box_strategy_type();
    }

    template <typename Segment, typename Box>
    static inline bool apply(Segment const& segment, Box const& box)
    {
        assert_dimension_equal<Segment, Box>();

        typedef typename util::calculation_type::geometric::binary
            <
                Segment, Box, void
            >::type relative_distance_type;

        typedef typename point_type<Segment>::type segment_point_type;
        segment_point_type p0, p1;
        geometry::detail::assign_point_from_index<0>(segment, p0);
        geometry::detail::assign_point_from_index<1>(segment, p1);

        return detail::disjoint_segment_box_impl
            <
                relative_distance_type, segment_point_type, Box,
                0, dimension<Box>::value
            >::apply(p0, p1, box);
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


namespace services
{

template <typename Linear, typename Box, typename LinearTag>
struct default_strategy<Linear, Box, LinearTag, box_tag, 1, 2, cartesian_tag, cartesian_tag>
{
    typedef disjoint::segment_box type;
};

template <typename Box, typename Linear, typename LinearTag>
struct default_strategy<Box, Linear, box_tag, LinearTag, 2, 1, cartesian_tag, cartesian_tag>
{
    typedef disjoint::segment_box type;
};


} // namespace services


#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}}}} // namespace boost::geometry::strategy::disjoint


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISJOINT_SEGMENT_BOX_HPP

/* disjoint_segment_box.hpp
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
*/