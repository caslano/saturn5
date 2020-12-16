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
PzgiCBAVtomfsf6wsSRuoxd8TMDs675sEyuJXtEkbOJutrewrdHse1BlRGOGhVFxAKsg2GwLs6w+4actsrDE7nifx/svSg1MzI1XUdqI5ZX4xB66SI2cCyR8euayd9iZTA4Rn6Hz3Lnx3Zi8RozJxd0KtTVqH7tqTzPQ3y2uQV/Be4zRJlU/Vg96U2WY0s+R7RPx0DHZPrmtS9txAuEgT8aReZyYux2CXrjdWkrpcshyEMczrCw5hPv6l9WI+xsg164CuV9orDdG8X54mlrrub/YjsM8/CZ9GbC/i62ekI4MpN3+S8RHzNwxdBEwM59MdxhaIOfTIPZBHigz4y3HNqnnSDrK+VEd7OLfbd4OtB07norHY1l6W2wYOgv8bTQPm6Fra5KifINeMt4fT9KNfHG+a3hWKUmB1pZc68TdxCSrveI8y60lRp+ouImRuDyHcpFnPB23r4hQpqyokW9Lx7I7LweD87R3lQTtVxOls3dIKt03ZX2oGPhC918O/FcA39T1nSXZul7l4Nw/n0ZhI5OHxHewzCPZgy7659Wg24z06FtM/rz38bjyoL/YgjRrkeb6HOsNK61dGojToxK0uymrD6cam2fP7GQAdvJdQ/BSb/uIMVlROgZEcmc6EbcXmMP1ci+w1jHw0mT27ttKdulaKd3qLD+wSOSf4g73daIu23K3MysLkg/qUZ6tdHKXNqdd2JDqEp7zBA1Xt2cInItLcP+lGrtt8PMBjr5DbCP7JMwH15+su1cpfgzeDpVXt8jryXKnOzKvTYIGlYHzkjTONHZP3veF9ss2RrTVFbjvaqsvf6yh0GbEwd2i3whAcp3XnUQ6e+95jVjbAU/YLwb+dkkbyL9LYZNebXUSNE0ZsJf7NaIM9eBl7yknNdIf8CIg4MXIUNqAaE24nmwjeGiZJ5nPdpTZ/O5Tdiem8qR4m2ecdUHpCnRhwPlohjbbooSjzel2hKTbqeim1XrLMOuYiXc6qOcBRoXOp/HVlmOPFsttmrerBmum4i16tl/TCrh/1ueYC+eK+yBkGyDtyNTIu3TsR/givdqXtscvD/BNQt1m9sF2mL5I7vd6BfhEf4HfsNl8P6K2PXQ3MssY9lzN17yO/SHYMoRN3yf7qIcwdpb18SZ80hd6M9cHcDQebNBFfrgwyEex5Bv1p9dMDG/S/l6sbBG1UftJub4ryxdwFB74ercYbyxXsnlPMB/sxVRnDYLyJnx114mKRx4cf5luEyr9h1Afy9C+TNyHa8Cf4P3DivePsrwZl+ftZdj0vzJ8qgqvVOG0ot8q4sGb5XtuCcoF3qaqtv7ZmmB8nb6nRMWvUXL7ooo/VcV/WcWvVPFfUfFa7l9T8a0q/ddhXyjM45LioM+dNMsFWEeA3w0/ZDQJmLUqqXg0luoV/uts8+YRJ8dbJbZPGo5J36fUS/b3LV+69CTn1lia3yS+yk0+6WH2pcbMOMXbGet3u574Psh6Cxt17zEgjwYLQz68TmJg/B4Lxk2AqT1ebY5mJg24mSufQwL7Vo1cJ1nbFu08o3Ur7QnZYnsuEc51zil/Gnd/r+qDvlOT9WPvKHH1dh3a07Hz9D134/24GygczgvVl3QUs0HeB/990Tf+AHw944WPyYonNSbbJfyRAe9/MRYzeKtzjJ3a1NjpRipTpxo7bQkZO23D2MnMwR5DQv2h0INBK0c+tsbvQOSo/+7mKM3Z+/gIyvWVm5R/Mw3z3neg//gx/JufQAd+Ksc/wKPxEvm/9Knxz8+Q5haZRuRBtG16meY2pPk50mDelvDEOG3C8dpM7w7QuVOO9yydyY337kb6XyA9+gzFL+1dB969IfmkuazOJ6spRNsS+dyP9L8=
*/