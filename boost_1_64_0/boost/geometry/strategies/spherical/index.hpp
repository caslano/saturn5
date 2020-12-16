// Boost.Geometry Index
//
// R-tree strategies
//
// Copyright (c) 2019, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_INDEX_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_INDEX_HPP

#include <boost/geometry/strategies/spherical/distance_haversine.hpp>
#include <boost/geometry/strategies/spherical/distance_cross_track.hpp>
#include <boost/geometry/strategies/spherical/distance_cross_track_point_box.hpp>
#include <boost/geometry/strategies/spherical/distance_segment_box.hpp>
#include <boost/geometry/strategies/spherical/envelope_box.hpp>
#include <boost/geometry/strategies/spherical/envelope_point.hpp>
#include <boost/geometry/strategies/spherical/envelope_segment.hpp>
#include <boost/geometry/strategies/spherical/expand_box.hpp>
#include <boost/geometry/strategies/spherical/expand_point.hpp>
#include <boost/geometry/strategies/spherical/expand_segment.hpp>
#include <boost/geometry/strategies/spherical/intersection.hpp>
#include <boost/geometry/strategies/spherical/point_in_poly_winding.hpp>

#include <boost/geometry/strategies/index.hpp>


namespace boost { namespace geometry { namespace strategy { namespace index
{

template
<
    typename CalculationType = void
>
struct spherical
{
    typedef spherical_tag cs_tag;

    typedef geometry::strategy::envelope::spherical_point envelope_point_strategy_type;
    typedef geometry::strategy::envelope::spherical_box envelope_box_strategy_type;
    typedef geometry::strategy::envelope::spherical_segment
        <
            CalculationType
        > envelope_segment_strategy_type;

    static inline envelope_segment_strategy_type get_envelope_segment_strategy()
    {
        return envelope_segment_strategy_type();
    }

    typedef geometry::strategy::expand::spherical_point expand_point_strategy_type;
    typedef geometry::strategy::expand::spherical_box expand_box_strategy_type;
    typedef geometry::strategy::expand::spherical_segment
        <
            CalculationType
        > expand_segment_strategy_type;

    static inline expand_segment_strategy_type get_expand_segment_strategy()
    {
        return expand_segment_strategy_type();
    }

	typedef geometry::strategy::covered_by::spherical_point_box covered_by_point_box_strategy_type;
	typedef geometry::strategy::covered_by::spherical_box_box covered_by_box_box_strategy_type;
	typedef geometry::strategy::within::spherical_point_point within_point_point_strategy_type;
	//typedef geometry::strategy::within::spherical_point_box within_point_box_strategy_type;
	//typedef geometry::strategy::within::spherical_box_box within_box_box_strategy_type;

    // used in equals(Seg, Seg) but only to get_point_in_point_strategy()
    typedef geometry::strategy::intersection::spherical_segments
        <
            CalculationType
        > relate_segment_segment_strategy_type;

    static inline relate_segment_segment_strategy_type get_relate_segment_segment_strategy()
    {
        return relate_segment_segment_strategy_type();
    }
    
    // used in intersection_content
    typedef geometry::strategy::disjoint::spherical_box_box disjoint_box_box_strategy_type;

    typedef geometry::strategy::distance::comparable::haversine
        <
            double,
            CalculationType
        > comparable_distance_point_point_strategy_type;

    static inline comparable_distance_point_point_strategy_type get_comparable_distance_point_point_strategy()
    {
        return comparable_distance_point_point_strategy_type();
    }

    // TODO: Comparable version should be possible
    typedef geometry::strategy::distance::cross_track_point_box
        <
            CalculationType,
            geometry::strategy::distance::haversine<double, CalculationType>
        > comparable_distance_point_box_strategy_type;

    static inline comparable_distance_point_box_strategy_type get_comparable_distance_point_box_strategy()
    {
        return comparable_distance_point_box_strategy_type();
    }

    // TODO: Radius is not needed in comparable strategy
    typedef geometry::strategy::distance::comparable::cross_track
        <
            CalculationType,
            geometry::strategy::distance::comparable::haversine<double, CalculationType>
        > comparable_distance_point_segment_strategy_type;

    static inline comparable_distance_point_segment_strategy_type get_comparable_distance_point_segment_strategy()
    {
        return comparable_distance_point_segment_strategy_type();
    }

    // comparable?
    typedef geometry::strategy::distance::spherical_segment_box
        <
            CalculationType,
            geometry::strategy::distance::haversine<double, CalculationType>
        > comparable_distance_segment_box_strategy_type;

    static inline comparable_distance_segment_box_strategy_type get_comparable_distance_segment_box_strategy()
    {
        return comparable_distance_segment_box_strategy_type();
    }
};


namespace services
{

template <typename Geometry>
struct default_strategy<Geometry, spherical_tag>
{
    typedef spherical<> type;
};

template <typename Geometry>
struct default_strategy<Geometry, spherical_polar_tag>
{
    typedef spherical<> type;
};

template <typename Geometry>
struct default_strategy<Geometry, spherical_equatorial_tag>
{
    typedef spherical<> type;
};


template <typename Point1, typename Point2, typename CalculationType>
struct from_strategy<within::spherical_winding<Point1, Point2, CalculationType> >
{
    typedef strategy::index::spherical<CalculationType> type;

    static inline type get(within::spherical_winding<Point1, Point2, CalculationType> const&)
    {
        return type();
    }
};

// distance (MPt, MPt)
template <typename RadiusType, typename CalculationType>
struct from_strategy<distance::comparable::haversine<RadiusType, CalculationType> >
{
    typedef strategy::index::spherical<CalculationType> type;

    static inline type get(distance::comparable::haversine<RadiusType, CalculationType> const&)
    {
        return type();
    }
};

// distance (MPt, Linear/Areal)
template <typename CalculationType, typename PPStrategy>
struct from_strategy<distance::comparable::cross_track<CalculationType, PPStrategy> >
{
    typedef strategy::index::spherical<CalculationType> type;

    static inline type get(distance::comparable::cross_track<CalculationType, PPStrategy> const&)
    {
        return type();
    }
};


} // namespace services


}}}} // namespace boost::geometry::strategy::index

#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_INDEX_HPP

/* index.hpp
076WfCzby/petcjL+r2krzm/VM/3fhVlvfbTybIPykVGH5SmvNrqvVLaFKSluL1XcnyxoPtfqMX9T2vn71/R3I9bT6MfRckvTfdD/fge49gur0I5M5+/6CjvN6Z7T5J2HNW8B5i3KzON7yTngvn3iwx2jWl+jztYN3x0l7Hu7ALWnca8Ez25HrtY5aHy/se8XsxnI/gz02P6vHKM2AcV9X2g/TTB/BJfplNeIeelse132Lcnv7vEKW0PTvqruqmm+Q8xv7ZvLvY24k1T20N+rp8yRp7u11k9b5iuh+XVZLx20hWCnqi9q+cMcKo/HmW/HnYW8s62wemdbZ/Fs+Qhi2ejY+j6nn7a4tmtqrSTkOlpKbFR4x3vVhXM2y79t5mOl+SH5ueFSLc6wXKdWryvSz+uMr+8l8s78u3m9205F9W8rNx+vpznmOVUs/f7MHCg0/mCK3zcz5cst/NF6v5eQ/9y1nVVr19dW+u6ocWvg2tdl7T4dXP/1+rgWtdtvX51c63r1Ba/zrd1nd2C63Zb180tft30guqaf6D3R3e8m0+r6WFfNQ9NO3t27Jfn7yq4Drq9LpKU3+IswumS5rpIdXmNr4QNsSU2wj7YBJOwKT6CzXAGBjvXFfKWfoUsxigMkfW2lvW2weEYKuttizZs51THNce74DFFO0pdoU4Ygnc516mV5ZoQbCWLXrdZL4vEehbLLZLlnsJa+LTTcpGyXAN9uaLXbc4xxVf0us37ZLlG+nJFr9usl71hD325otdttslyfvpyRa/bnC3L1dWXK3rd5jxZrrnFcmukbvPr2BjXynLhJaUMScqWOF/07eyG2t/b3tTdw61YDXdgU/wI78K92As/Rht+gpPwEC7Dw/gJHsHDeBRP4HG8hCewFJGfxFvxG7wTz2Bz/Ba74jl8DM/ji/gj5uEF/Bwv4hn8GeuT9ss4BH/F0fg7LsU/8XX8N27DEqWo84wl8Th64tdYGr20enHog2WxFt6K9bACtkIf7Iy+OBj9cDhWxVS8E6didXwRA3EN1sQtWAv3Ym08gI3xa2yGJb04rlgWm2MlbIH1MQSbYCfsinfhAAzDKOyMcdgTH8BemIHh+CAOxCU4BD/Ge/BzHIancDj+giPwCo5EP86PUVgd78dgjMBWOBrbYQxe0OsOSlmalLFp51V7e/+Z+p83+78BlscOWAHD0R8fwNo4FYNwBtbBVVgXc7EhbsVG+DE2wRKsuyWWwdboj22wLoZiI+yOY7EnpmJvnId9cDsOxltI6zD0xeHYCkdgOxyJkRiNYzEG/4GxOB/jcCEm4mocjzvRhr9hCtbl+KZiU0zDzpiOvTATw3ESjsTJmIRTMBWz8J84DZ/Eh3AJPozb8BHciTPwKM7Er/GfqJ1Hj2E5nI1VcQ7Wwmzsjk9gT5yPQ3AJxuHzOBmX40P4Ij6FL+Ez+DJesPdnKGVy7BvJTxry/5Fy3Ed7ct/BsdgRx+FoTMRMHI+zMAlnYzKuRRvuwgfwCKbhz5iOWmQZWBYnYGXMxCY4GSfhLHwI/4XLcDbm4hzch9l4DJ/AkqR5LpbHedgU5+NAXIAZuBjP4LN4EZ/Dy7gUS7K/l2FZXI7+uAKD8EVsiStxHr6BnPMeb2J1XI91cCM2x03YHt/GnvgO9sU8vKD3zyblYlJedppwpz5OtuTfXqQfd2FH3I3huA+H4wF8Ej/FPXgIv8F81McaxRr4JdbDY9gMj+Pd+BVm4AmcgSdxEZ7CXPwG8/A07sMzeBrPYiXS+i22wHPYBs/jXfgjRuJFzMBL+CL+hNvwZ9yOJR3nnYeUG+FHFmPS92T+atgb6+AADMFwbIeDcBgOxgy8B+fhUHwDh+EuHI4=
*/