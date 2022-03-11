// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_MAX_INTERVAL_GAP_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_MAX_INTERVAL_GAP_HPP

#include <cstddef>
#include <queue>
#include <utility>
#include <vector>

#include <boost/core/ref.hpp>
#include <boost/range.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

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
        : m_interval(boost::cref(interval))
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
    boost::reference_wrapper<Interval const> m_interval;
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

    typedef typename boost::remove_const
        <
            typename boost::remove_reference
                <
                    event_time_type
                >::type
        >::type bare_time_type;


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

    bare_time_type const& max_gap_left() const
    {
        return m_max_gap_left;
    }

    bare_time_type const& max_gap_right() const
    {
        return m_max_gap_right;
    }

    difference_type max_gap() const
    {
        return m_max_gap_right - m_max_gap_left;
    }

private:
    std::size_t m_overlap_count;
    bare_time_type m_max_gap_left, m_max_gap_right;
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
    typedef typename boost::remove_const
        <
            typename boost::remove_reference
                <
                    typename boost::range_value
                        <
                            RangeOfIntervals
                        >::type::value_type
                >::type
        >::type value_type;

    value_type left, right;

    return maximum_gap(range_of_intervals, left, right);
}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_MAX_INTERVAL_GAP_HPP

/* max_interval_gap.hpp
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
*/