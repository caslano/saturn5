// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_FEATURE_GEOMETRY_TO_RANGE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_FEATURE_GEOMETRY_TO_RANGE_HPP

#include <iterator>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/util/math.hpp>

#include <boost/geometry/algorithms/dispatch/distance.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace closest_feature
{



// returns the range iterator the realizes the closest
// distance between the geometry and the element of the range
class geometry_to_range
{
private:
    template
    <
        typename Geometry,
        typename RangeIterator,
        typename Strategy,
        typename Distance
    >
    static inline void apply(Geometry const& geometry,
                             RangeIterator first,
                             RangeIterator last,
                             Strategy const& strategy,
                             RangeIterator& it_min,
                             Distance& dist_min)
    {
        BOOST_GEOMETRY_ASSERT( first != last );

        Distance const zero = Distance(0);

        // start with first distance
        it_min = first;
        dist_min = dispatch::distance
            <
                Geometry,
                typename std::iterator_traits<RangeIterator>::value_type,
                Strategy
            >::apply(geometry, *it_min, strategy);

        // check if other elements in the range are closer
        for (RangeIterator it = ++first; it != last; ++it)
        {
            Distance dist = dispatch::distance
                <
                    Geometry,
                    typename std::iterator_traits<RangeIterator>::value_type,
                    Strategy
                >::apply(geometry, *it, strategy);

            if (geometry::math::equals(dist, zero))
            {
                dist_min = dist;
                it_min = it;
                return;
            }
            else if (dist < dist_min)
            {
                dist_min = dist;
                it_min = it;
            }
        }
    }

public:
    template
    <
        typename Geometry,
        typename RangeIterator,
        typename Strategy,
        typename Distance
    >    
    static inline RangeIterator apply(Geometry const& geometry,
                                      RangeIterator first,
                                      RangeIterator last,
                                      Strategy const& strategy,
                                      Distance& dist_min)
    {
        RangeIterator it_min;
        apply(geometry, first, last, strategy, it_min, dist_min);

        return it_min;
    }


    template
    <
        typename Geometry,
        typename RangeIterator,
        typename Strategy
    >    
    static inline RangeIterator apply(Geometry const& geometry,
                                      RangeIterator first,
                                      RangeIterator last,
                                      Strategy const& strategy)
    {
        typename strategy::distance::services::return_type
            <
                Strategy,
                typename point_type<Geometry>::type,
                typename point_type
                    <
                        typename std::iterator_traits
                            <
                                RangeIterator
                            >::value_type
                    >::type
            >::type dist_min;

        return apply(geometry, first, last, strategy, dist_min);
    }
};



}} // namespace detail::closest_feature
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_FEATURE_GEOMETRY_TO_RANGE_HPP

/* geometry_to_range.hpp
DT0fO6c/KWE2a8KgIMdQ9eT64Ua0t15GKgV0MvxbFJPLuGiYoGcFy4AVR1AyD836hPcE/8A/x7XDuUKQAR7rT7IXnima+cRjpRQhm+LHxbgxGjGPoIf4FISDiIzAA474uwVPNF3Kl9rGUS5uQfIG5fvzR6AnIeDBepuw1v5mAKiq2KAqXyofbrOTcOXWuJDxedtOT+/FtC0KZ9ua74ZDnhrLQyRzaqDGlNO+9SCV0xd8jfTKCh0iskuyE4oM96bTFLoV3zPXTkte8h0g0QZ/Srdl/CUXIfAFIWYndW11Zotu6kaKp82fLUsYDlh4tsbbCyxjoTFW0T84brcT0Eio2ac1cYaOdBzxsq4llx/v/yj37aJ7sB8GIQ8k1JfsCZCMyB3hhISdbuCdYfR9Jr5ae8nuWT/M5Cl9Dmx3eWjV3UCAkGEiI6naH5Z+yAOK6XBO19sf1n5xoiJ3yR7UiRm0geUHMtfQRGfF/63cDCPHFBJeBgEpsT/ry/qNuOmPFP8dBbWuRiV3AtFOjPgJbQ1sVC5WTlp35KHsD9WFTnX/xZdZ4al2etfqXr24LQ==
*/