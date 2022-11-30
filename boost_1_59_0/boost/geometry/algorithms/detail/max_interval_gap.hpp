// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_MAX_INTERVAL_GAP_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_MAX_INTERVAL_GAP_HPP

#include <cstddef>
#include <functional>
#include <queue>
#include <utility>
#include <vector>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/algorithms/detail/sweep.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace max_interval_gap
{

// the class Interval must provide the following:
// * must define the type value_type
// * must define the type difference_type
// * must have the methods:
//   value_type get<Index>() const
//   difference_type length() const
// where an Index value of 0 (resp., 1) refers to the left (resp.,
// right) endpoint of the interval

template <typename Interval>
class sweep_event
{
public:
    typedef Interval interval_type;
    typedef typename Interval::value_type time_type;

    sweep_event(Interval const& interval, bool start_event = true)
        : m_interval(std::cref(interval))
        , m_start_event(start_event)
    {}

    inline bool is_start_event() const
    {
        return m_start_event;
    }

    inline interval_type const& interval() const
    {
        return m_interval;
    }

    inline time_type time() const
    {
        return (m_start_event)
            ? interval().template get<0>()
            : interval().template get<1>();
    }

    inline bool operator<(sweep_event const& other) const
    {
        if (! math::equals(time(), other.time()))
        {
            return time() < other.time();
        }
        // a start-event is before an end-event with the same event time
        return is_start_event() && ! other.is_start_event();
    }

private:
    std::reference_wrapper<Interval const> m_interval;
    bool m_start_event;
};

template <typename Event>
struct event_greater
{
    inline bool operator()(Event const& event1, Event const& event2) const
    {
        return event2 < event1;
    }
};


struct initialization_visitor
{
    template <typename Range, typename PriorityQueue, typename EventVisitor>
    static inline void apply(Range const& range,
                             PriorityQueue& queue,
                             EventVisitor&)
    {
        BOOST_GEOMETRY_ASSERT(queue.empty());

        // it is faster to build the queue directly from the entire
        // range, rather than insert elements one after the other
        PriorityQueue pq(boost::begin(range), boost::end(range));
        std::swap(pq, queue);
    }
};


template <typename Event>
class event_visitor
{
    typedef typename Event::time_type event_time_type;
    typedef typename Event::interval_type::difference_type difference_type;

public:
    event_visitor()
        : m_overlap_count(0)
        , m_max_gap_left(0)
        , m_max_gap_right(0)
    {}

    template <typename PriorityQueue>
    inline void apply(Event const& event, PriorityQueue& queue)
    {
        if (event.is_start_event())
        {
            ++m_overlap_count;
            queue.push(Event(event.interval(), false));
        }
        else
        {
            --m_overlap_count;
            if (m_overlap_count == 0 && ! queue.empty())
            {
                // we may have a gap
                BOOST_GEOMETRY_ASSERT(queue.top().is_start_event());

                event_time_type next_event_time
                    = queue.top().interval().template get<0>();
                difference_type gap = next_event_time - event.time();
                if (gap > max_gap())
                {
                    m_max_gap_left = event.time();
                    m_max_gap_right = next_event_time;
                }
            }
        }
    }

    event_time_type const& max_gap_left() const
    {
        return m_max_gap_left;
    }

    event_time_type const& max_gap_right() const
    {
        return m_max_gap_right;
    }

    difference_type max_gap() const
    {
        return m_max_gap_right - m_max_gap_left;
    }

private:
    std::size_t m_overlap_count;
    event_time_type m_max_gap_left, m_max_gap_right;
};

}} // namespace detail::max_interval_gap
#endif // DOXYGEN_NO_DETAIL


// Given a range of intervals I1, I2, ..., In, maximum_gap() returns
// the maximum length of an interval M that satisfies the following
// properties:
//
// 1. M.left >= min(I1, I2, ..., In)
// 2. M.right <= max(I1, I2, ..., In)
// 3. intersection(interior(M), Ik) is the empty set for all k=1, ..., n
// 4. length(M) is maximal
//
// where M.left and M.right denote the left and right extreme values
// for the interval M, and length(M) is equal to M.right - M.left.
//
// If M does not exist (or, alternatively, M is identified as the
// empty set), 0 is returned.
//
// The algorithm proceeds for performing a sweep: the left endpoints
// are inserted into a min-priority queue with the priority being the
// value of the endpoint. The sweep algorithm maintains an "overlap
// counter" that counts the number of overlaping intervals at any
// specific sweep-time value.
// There are two types of events encountered during the sweep:
// (a) a start event: the left endpoint of an interval is found.
//     In this case the overlap count is increased by one and the
//     right endpoint of the interval in inserted into the event queue
// (b) an end event: the right endpoint of an interval is found.
//     In this case the overlap count is decreased by one. If the
//     updated overlap count is 0, then we could expect to have a gap
//     in-between intervals. This gap is measured as the (absolute)
//     distance of the current interval right endpoint (being
//     processed) to the upcoming left endpoint of the next interval
//     to be processed (if such an interval exists). If the measured
//     gap is greater than the current maximum gap, it is recorded.
// The initial maximum gap is initialized to 0. This value is returned
// if no gap is found during the sweeping procedure.

template <typename RangeOfIntervals, typename T>
inline typename boost::range_value<RangeOfIntervals>::type::difference_type
maximum_gap(RangeOfIntervals const& range_of_intervals,
            T& max_gap_left, T& max_gap_right)
{
    typedef typename boost::range_value<RangeOfIntervals>::type interval_type;
    typedef detail::max_interval_gap::sweep_event<interval_type> event_type;

    // create a min-priority queue for the events
    std::priority_queue
        <
            event_type,
            std::vector<event_type>, 
            detail::max_interval_gap::event_greater<event_type>
        > queue;

    // define initialization and event-process visitors
    detail::max_interval_gap::initialization_visitor init_visitor;
    detail::max_interval_gap::event_visitor<event_type> sweep_visitor;

    // perform the sweep
    geometry::sweep(range_of_intervals,
                    queue,
                    init_visitor,
                    sweep_visitor);

    max_gap_left = sweep_visitor.max_gap_left();
    max_gap_right = sweep_visitor.max_gap_right();
    return sweep_visitor.max_gap();
}

template <typename RangeOfIntervals>
inline typename boost::range_value<RangeOfIntervals>::type::difference_type
maximum_gap(RangeOfIntervals const& range_of_intervals)
{
    typedef typename boost::range_value<RangeOfIntervals>::type interval_type;

    typename interval_type::value_type left, right;

    return maximum_gap(range_of_intervals, left, right);
}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_MAX_INTERVAL_GAP_HPP

/* max_interval_gap.hpp
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
*/