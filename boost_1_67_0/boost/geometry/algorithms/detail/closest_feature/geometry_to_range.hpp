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