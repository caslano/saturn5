// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_FEATURE_POINT_TO_RANGE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_FEATURE_POINT_TO_RANGE_HPP

#include <utility>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace closest_feature
{


// returns the segment (pair of iterators) that realizes the closest
// distance of the point to the range
template
<
    typename Point,
    typename Range,
    closure_selector Closure
>
class point_to_point_range
{
protected:
    typedef typename boost::range_iterator<Range const>::type iterator_type;

    template <typename Strategy, typename Distance>
    static inline void apply(Point const& point,
                             iterator_type first,
                             iterator_type last,
                             Strategy const& strategy,
                             iterator_type& it_min1,
                             iterator_type& it_min2,
                             Distance& dist_min)
    {
        BOOST_GEOMETRY_ASSERT( first != last );

        Distance const zero = Distance(0);

        iterator_type it = first;
        iterator_type prev = it++;
        if (it == last)
        {
            it_min1 = it_min2 = first;
            dist_min = strategy.apply(point, *first, *first);
            return;
        }

        // start with first segment distance
        dist_min = strategy.apply(point, *prev, *it);
        iterator_type prev_min_dist = prev;

        // check if other segments are closer
        for (++prev, ++it; it != last; ++prev, ++it)
        {
            Distance const dist = strategy.apply(point, *prev, *it);

            // Stop only if we find exactly zero distance
            // otherwise it may stop at some very small value and miss the min
            if (dist == zero)
            {
                dist_min = zero;
                it_min1 = prev;
                it_min2 = it;
                return;
            }
            else if (dist < dist_min)
            {
                dist_min = dist;
                prev_min_dist = prev;
            }
        }

        it_min1 = it_min2 = prev_min_dist;
        ++it_min2;
    }

public:
    typedef typename std::pair<iterator_type, iterator_type> return_type;

    template <typename Strategy, typename Distance>
    static inline return_type apply(Point const& point,
                                    iterator_type first,
                                    iterator_type last,
                                    Strategy const& strategy,
                                    Distance& dist_min)
    {
        iterator_type it_min1, it_min2;
        apply(point, first, last, strategy, it_min1, it_min2, dist_min);

        return std::make_pair(it_min1, it_min2);
    }

    template <typename Strategy>
    static inline return_type apply(Point const& point,
                                    iterator_type first,
                                    iterator_type last,
                                    Strategy const& strategy)
    {
        typename strategy::distance::services::return_type
            <
                Strategy,
                Point,
                typename boost::range_value<Range>::type
            >::type dist_min;

        return apply(point, first, last, strategy, dist_min);
    }

    template <typename Strategy, typename Distance>
    static inline return_type apply(Point const& point,
                                    Range const& range,
                                    Strategy const& strategy,
                                    Distance& dist_min)
    {
        return apply(point,
                     boost::begin(range),
                     boost::end(range),
                     strategy,
                     dist_min);
    }

    template <typename Strategy>
    static inline return_type apply(Point const& point,
                                    Range const& range,
                                    Strategy const& strategy)
    {
        return apply(point, boost::begin(range), boost::end(range), strategy);
    }
};



// specialization for open ranges
template <typename Point, typename Range>
class point_to_point_range<Point, Range, open>
    : point_to_point_range<Point, Range, closed>
{
private:
    typedef point_to_point_range<Point, Range, closed> base_type;
    typedef typename base_type::iterator_type iterator_type;

    template <typename Strategy, typename Distance>
    static inline void apply(Point const& point,
                             iterator_type first,
                             iterator_type last,
                             Strategy const& strategy,
                             iterator_type& it_min1,
                             iterator_type& it_min2,
                             Distance& dist_min)
    {
        BOOST_GEOMETRY_ASSERT( first != last );

        base_type::apply(point, first, last, strategy,
                         it_min1, it_min2, dist_min);

        iterator_type it_back = --last;
        Distance const zero = Distance(0);
        Distance dist = strategy.apply(point, *it_back, *first);

        if (geometry::math::equals(dist, zero))
        {
            dist_min = zero;
            it_min1 = it_back;
            it_min2 = first;
        }
        else if (dist < dist_min)
        {
            dist_min = dist;
            it_min1 = it_back;
            it_min2 = first;
        }
    }    

public:
    typedef typename std::pair<iterator_type, iterator_type> return_type;

    template <typename Strategy, typename Distance>
    static inline return_type apply(Point const& point,
                                    iterator_type first,
                                    iterator_type last,
                                    Strategy const& strategy,
                                    Distance& dist_min)
    {
        iterator_type it_min1, it_min2;

        apply(point, first, last, strategy, it_min1, it_min2, dist_min);

        return std::make_pair(it_min1, it_min2);
    }

    template <typename Strategy>
    static inline return_type apply(Point const& point,
                                    iterator_type first,
                                    iterator_type last,
                                    Strategy const& strategy)
    {
        typedef typename strategy::distance::services::return_type
            <
                Strategy,
                Point,
                typename boost::range_value<Range>::type
            >::type distance_return_type;

        distance_return_type dist_min;

        return apply(point, first, last, strategy, dist_min);
    }

    template <typename Strategy, typename Distance>
    static inline return_type apply(Point const& point,
                                    Range const& range,
                                    Strategy const& strategy,
                                    Distance& dist_min)
    {
        return apply(point,
                     boost::begin(range),
                     boost::end(range),
                     strategy,
                     dist_min);
    }

    template <typename Strategy>
    static inline return_type apply(Point const& point,
                                    Range const& range,
                                    Strategy const& strategy)
    {
        return apply(point, boost::begin(range), boost::end(range), strategy);
    }
};


}} // namespace detail::closest_feature
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_FEATURE_POINT_TO_RANGE_HPP

/* point_to_range.hpp
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
*/