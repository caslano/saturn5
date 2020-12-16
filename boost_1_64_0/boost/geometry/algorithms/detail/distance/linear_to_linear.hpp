// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_TO_LINEAR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_TO_LINEAR_HPP

#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/strategies/distance.hpp>

#include <boost/geometry/iterators/point_iterator.hpp>
#include <boost/geometry/iterators/segment_iterator.hpp>

#include <boost/geometry/algorithms/num_points.hpp>
#include <boost/geometry/algorithms/num_segments.hpp>

#include <boost/geometry/algorithms/dispatch/distance.hpp>

#include <boost/geometry/algorithms/detail/distance/range_to_geometry_rtree.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


template <typename Linear1, typename Linear2, typename Strategy>
struct linear_to_linear
{
    typedef typename strategy::distance::services::return_type
        <
            Strategy,
            typename point_type<Linear1>::type,
            typename point_type<Linear2>::type
        >::type return_type;

    static inline return_type apply(Linear1 const& linear1,
                                    Linear2 const& linear2,
                                    Strategy const& strategy,
                                    bool = false)
    {
        if (geometry::num_points(linear1) == 1)
        {
            return dispatch::distance
                <
                    typename point_type<Linear1>::type,
                    Linear2,
                    Strategy
                >::apply(*points_begin(linear1), linear2, strategy);
        }

        if (geometry::num_points(linear2) == 1)
        {
            return dispatch::distance
                <
                    typename point_type<Linear2>::type,
                    Linear1,
                    Strategy
                >::apply(*points_begin(linear2), linear1, strategy);
        }

        if (geometry::num_segments(linear2) < geometry::num_segments(linear1))
        {
            return point_or_segment_range_to_geometry_rtree
                <
                    geometry::segment_iterator<Linear2 const>,
                    Linear1,
                    Strategy
                >::apply(geometry::segments_begin(linear2),
                         geometry::segments_end(linear2),
                         linear1,
                         strategy);

        }

        return point_or_segment_range_to_geometry_rtree
            <
                geometry::segment_iterator<Linear1 const>,
                Linear2,
                Strategy
            >::apply(geometry::segments_begin(linear1),
                     geometry::segments_end(linear1),
                     linear2,
                     strategy);
    }
};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Linear1, typename Linear2, typename Strategy>
struct distance
    <
        Linear1, Linear2, Strategy,
        linear_tag, linear_tag, 
        strategy_tag_distance_point_segment, false
    > : detail::distance::linear_to_linear
        <
            Linear1, Linear2, Strategy
        >
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_TO_LINEAR_HPP

/* linear_to_linear.hpp
WMWBa3y/bpX5HflpwHjmkivmRbH8+SdarSVuj60mytBXhdVazM/J2PeZlnKmr0Lh0z76LckWWFcfL5aRD3NO2xV0/2J4ywspEqVH4Plfn/IGaYRro2AgTZmuAp30OV58ZW5yrZl99EEqPDgDHtTXi7dhfG56Ltj9cHhOzzVEj1F/HeFC0oBnd2hVvFAqu/slo1cS6sFH8ghXllVwnhDAjbD+enHaF743MFsezGfWoKnL7XB2LTcJqvMoCvD+cODeNbgDr2eFY1/tUhtHzO251TGvIkFX2MNf21uFj7vd+VwWNWh2Oj1T7uLrd+c5Q3OosfH6wl53JcezcpZL/35BM6zqYrarYfbdgOve0+v0VmNYMOgF70dvNG5Pe4vdf0Lhflz8+CW+H85TFvMo2m3xVf417PnhW7wKq282D/I7rszW8Pen4/gavu1xzS9p3RJ/wl748yu/8HZP3uxxs17vAD8Pj21Up9Y+ri3toBZfw5Lyf9NeB2nl2fi9pXUctDZ9O6MGjQRjf/kFJaxXWzn1TsmAv1/rvLyVM9pwmmABv3GNmWkKzr8DowNmPH1VPTXevc/3rmrWPgsnzTl71tEb6uE7OZ6dBNaIWbl9+LQhrcO3y1XaWfE7M8D3fHZeRPJJ+OYfaymnjvBYy5izxmXmzm3qhGc09is8oo726J1lXwf41fKeWN93l8OvfG0HjTpHT82Dy7DuWUu9MwjefRgwY8kpjby2G17tZc/z1G4uNUCz5MjpdRfVW106qoy9zjIT4PsFm2m7heIP16aJwZS1fDM1VHgVfBxmfdnF8y0vkY4ZvQyWiUvez82hsOwxjdirEX9PbySACzWO4Upar3Q7vHQkWM2YT/qKmZ6NRR9eg++9nE/H+0UtfqKGa8lRKrzcH56lV+sFaT01UQwndVIvK/vQF3rjEzF9KHdBjWjkzrRMPvpvjzyI5Sx1cDYhP2wdfUX7ZYIlCReb07LrQ+c0bWa6Ri37xevfP4Fh6r45ffPtafrqTzX9Un2YhUrw107wJyrBmaf8q+4lAJ562KB+ouTzVTg/ph/8DDPXwJBhvt9ED6y56bX2nywEb9l7BnUQHt85oBniWD+1XJ4GgvUphsN9+vy8WA+JMptGizn9sK4FHMkD2+H7i6JyYybN/t77UtP4GXlxctgZdm2qaeaBoXfV7gWvHTNRLfMq9+v1BvvMp1Nh3RdB/FPnmtbXaj4fRxxqqqtdOPRTOHN0C+9J3X8Yj86gE5LwzDertyqHnGOX1LOuXcv3v09ECxRUW3ywtd/7SGnth/kCb8yzd/SIOB2k2ePp8095PrGL8sv4hmmniYWZ6LOeNADNEocv/IH13CwGz6bB9rN4qQ2cpGUnqsEFl+GPdYSfhm89zN34KHkFfn0PZ6VZ6RLvP1ObX3idXodxq8LUdzecu1/Oc9FHJ2BkHtw5CcYk5TNmMpuaFz6e5EwDl+SBSb+Upqs665+z9qmvj+Cz6jD1FS8ldWb1Uc/P01jH1IPiHNe1f4RPh3nhMK4GLPtytD7p4PoTYE4q+bjl+niv7Crenlkm2np4gYEsj+WSt1/BewryPP+bglYtB/f4rx+431GvjeP5inbvcMAI9ScmLQNyNibIPpypLtI/sKKiWI7/AlfUosf70+w4rLt6XzeA5oBBEfp90hn6MLGY05fP6MRcchcfhmwZpR7z0ifb5SY/f8OZ4pkgcYF588vRTbPoLno5UWPcJm/NE/DQRptB+XHZOtKg/fWg2vj7FCzp7PnuOrioJv8M1uyHH/EicIuau+61qfVPkWa06DyffwOb+AGPxOntSs/jT5drGDde7WXDywVoyW+iaWzackkc8bxFz5ur+t/Qe9Y=
*/