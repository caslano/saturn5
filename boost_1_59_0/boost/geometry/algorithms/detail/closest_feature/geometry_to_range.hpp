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
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
*/