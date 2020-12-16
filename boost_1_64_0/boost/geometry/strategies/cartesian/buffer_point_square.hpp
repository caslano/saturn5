// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2014 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_POINT_SQUARE_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_POINT_SQUARE_HPP

#include <cstddef>

#include <boost/range/value_type.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/strategies/buffer.hpp>
#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace buffer
{

/*!
\brief Create a squared form buffer around a point
\ingroup strategies
\details This strategy can be used as PointStrategy for the buffer algorithm.
    It creates a square from each point, where the point lies in the center.
    It can be applied for points and multi_points, but also for a linestring (if it is degenerate,
    so consisting of only one point) and for polygons (if it is degenerate).
    This strategy is only applicable for Cartesian coordinate systems.

\qbk{
[heading Example]
[buffer_point_square]
[heading Output]
[$img/strategies/buffer_point_square.png]
[heading See also]
\* [link geometry.reference.algorithms.buffer.buffer_7_with_strategies buffer (with strategies)]
\* [link geometry.reference.strategies.strategy_buffer_point_circle point_circle]
\* [link geometry.reference.strategies.strategy_buffer_geographic_point_circle geographic_point_circle]
}
 */
class point_square
{
    template
    <
        typename Point,
        typename DistanceType,
        typename OutputRange
    >
    inline void add_point(Point const& point,
                DistanceType const& distance,
                DistanceType const& x,
                DistanceType const& y,
                OutputRange& output_range) const
    {
        typename boost::range_value<OutputRange>::type p;
        set<0>(p, get<0>(point) + x * distance);
        set<1>(p, get<1>(point) + y * distance);
        output_range.push_back(p);
    }

    template
    <
        typename Point,
        typename DistanceType,
        typename OutputRange
    >
    inline void add_points(Point const& point,
                DistanceType const& distance,
                OutputRange& output_range) const
    {
        add_point(point, distance, -1.0, -1.0, output_range);
        add_point(point, distance, -1.0, +1.0, output_range);
        add_point(point, distance, +1.0, +1.0, output_range);
        add_point(point, distance, +1.0, -1.0, output_range);

        // Close it:
        output_range.push_back(output_range.front());
    }

public :

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    //! Fills output_range with a square around point using distance_strategy
    template
    <
        typename Point,
        typename DistanceStrategy,
        typename OutputRange
    >
    inline void apply(Point const& point,
                DistanceStrategy const& distance_strategy,
                OutputRange& output_range) const
    {
        add_points(point, distance_strategy.apply(point, point,
                        strategy::buffer::buffer_side_left), output_range);
    }
#endif // DOXYGEN_SHOULD_SKIP_THIS

};


}} // namespace strategy::buffer

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_BUFFER_POINT_SQUARE_HPP

/* buffer_point_square.hpp
4EYqZ5TFF9gPvAi4DbgHFf0Z4NNZ+I/1R+DZwJJsjLPABuBngU3A81k9AS8EbgReBNwB3AG8Dngx69/AncAfAC8BvgC8FPgG8DJgNuLyeeBE4BeAc4GXA8uAV8g44nPH4xRHao85vB2JdLlHjFNXeMT49EVgCfBK4Hw2jnlMPdoPhtZzMenZSXouIT2Xkp7LFD3tw+j5Oum5nvTsIj27Sc8Nip7rhtHzFdLzVdJzNem5hvRcS3pmeuQ1P7sXIPQwuUnUzv5K/exvwFnAN4DVwP3ATuABGq/fpPH6bWp377D6BL5L/e4fwOuB7wH3Av/J2ono39t/A/w38GXgB9TvPPDvA+AIIFubZwFnAbOBi4E5wGXAkcAWYB6bz4GjgacCDwFuBR4KvBx4GHA3cAzwm8B84H3AAuCPgGOBLwInAIsQgyOAU4FHAqcDiyheF2jGfQVtPI1TYzTW/kX6FcXrBSAb/35N8XoRWAv8DbAL+BLF6WU2PgBfYeMD8FXgTcDXNLEe+S2QnUf8PfXLPwLzgX+i9r1dM+4PaHvJHzbfpuW8AJHpwAdovn0QeCYbd8nud4BXsHkN+Gvg92n8+wHwPTbOk/0ngdOAP2R6gE+z8QT4LPnRpBnX9NoKGvtz+Xgr0s9pvPoF8EjgL1k/pXh5KV4tLF6kjym6g/R5qV0eje9vkb6FHqGvmua7RcAT2HgPbGDjPbCN+QRMsPEcOMDGc+AeYB3wDmA98GFmwyPWEQ3AvwCbqb6XsXbAxm/WDti4DdzGxm3gmWy8Bn4JuILpAXYAHwV2AvcB/cD9wFXAfwJXs36JsqwBHgZcC6wErgMuAa4HLgV2kf07NOMaXNtG9TuWr5NEOpriMNkj1lVTaJ1bTPEoAZ4CPAYYYvMw8MvAacBrgDOAfxLjwPbXgbOBuWw9yOIKnAs8DlgKPBFYBgwAy4ERYAUwBaz0iPluHvl9kyavpeEv+V3I138iBWgdsAE4A9gDjAN7gacB+4BnATeSv1EgK3M/kOv2iPXfJtZ/gUngz4Ep4Aus/bP+DBzwiHY8CGRneDcDRwFPo3HldOCl2WJAnYRPPT7p/7B3J/BVE3kAx19pwcrZcl9iuW8od7mkQAsFSilQoBzSlvZBKz0ePbjVIoigiKi4IiIg4ornouIuKq64orKKiq4HAu6ioIs3IiBeuL/J/PNe8l5KW3Cvz6fv85nPF9JkZjJJJslkJiFsIxwgVB/MPkbwENYQHiHsJRwmnB3M34dQRoQ4QiphMWHrEOYhfEkIGUqZEwYQphHmEzYTdhHeIRwfSjyEujFsA0IcwUNYRdhK2EM4RjgVwzyxzBNLXIRpsfrAWUvYHkteCT8TwoaRHiGakEjwENYRthH2EU4QGg4nDsI0QjFhDWHzcOIhvDOctAjV49jGhCRCNmFxHGkRdhCOEFwjSIcQQ0gawd8JqwhbCbtGEA/hLKHuSPJMiCMkE4oJGwg7CQcIxwmuUeSb0IkQQ8gkrCI8QthDeIdwltAwnjwR4gip8brC2EzYTthL+JIQNpp1IyQTMgnzCatGE9do8jWauEYTF6F6AscIIZKQRMggrEhgvgTiSiAugmsMeSdEEzIIqkJZQ9hG2DmG/I8hLkLTROYhpBI8hFWJxJNI3gknCCFjmYfQiTCAMI1QSFhGWEfYRtg5lnQJXxJCxlFuhFaEnoR4QgahmLCWsIOwfxxxE1zjWQ9CDCGTsGo88RH2EY4TwpJYR0IiIZVQmES6hA1JpJlEPIQjhNAJrCthACGRUEhYS9hB2EPYP4H4CNUnkh4hipBKWEzYOpH5CHsJBwgnCKGTyD8hmpBMWExYRdg8iXknESfhGCE0mfkIMYRMwlo=
*/