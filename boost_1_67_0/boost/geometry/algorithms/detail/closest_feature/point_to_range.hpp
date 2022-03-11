// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_FEATURE_POINT_TO_RANGE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_FEATURE_POINT_TO_RANGE_HPP

#include <utility>

#include <boost/range.hpp>

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
    closure_selector Closure,
    typename Strategy
>
class point_to_point_range
{
protected:
    typedef typename boost::range_iterator<Range const>::type iterator_type;

    template <typename Distance>
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

    template <typename Distance>
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

    template <typename Distance>
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

    static inline return_type apply(Point const& point,
                                    Range const& range,
                                    Strategy const& strategy)
    {
        return apply(point, boost::begin(range), boost::end(range), strategy);
    }
};



// specialization for open ranges
template <typename Point, typename Range, typename Strategy>
class point_to_point_range<Point, Range, open, Strategy>
    : point_to_point_range<Point, Range, closed, Strategy>
{
private:
    typedef point_to_point_range<Point, Range, closed, Strategy> base_type;
    typedef typename base_type::iterator_type iterator_type;

    template <typename Distance>
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

    template <typename Distance>
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

    template <typename Distance>
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
+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
*/