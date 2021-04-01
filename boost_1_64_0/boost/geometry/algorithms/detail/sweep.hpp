// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_SWEEP_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_SWEEP_HPP

#include <boost/core/ignore_unused.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace sweep
{

struct no_interrupt_policy
{
    static bool const enabled = false;

    template <typename Event>
    static inline bool apply(Event const&)
    {
        return false;
    }
};

}} // namespace detail::sweep
#endif // DOXYGEN_NO_DETAIL


template
<
    typename Range,
    typename PriorityQueue,
    typename InitializationVisitor,
    typename EventVisitor,
    typename InterruptPolicy
>
inline void sweep(Range const& range, PriorityQueue& queue,
                  InitializationVisitor& initialization_visitor,
                  EventVisitor& event_visitor,
                  InterruptPolicy const& interrupt_policy)
{
    typedef typename PriorityQueue::value_type event_type;

    initialization_visitor.apply(range, queue, event_visitor);
    while (! queue.empty())
    {
        event_type event = queue.top();
        queue.pop();
        event_visitor.apply(event, queue);
        if (interrupt_policy.enabled && interrupt_policy.apply(event))
        {
            break;
        }
    }

    boost::ignore_unused(interrupt_policy);
}


template
<
    typename Range,
    typename PriorityQueue,
    typename InitializationVisitor,
    typename EventVisitor
>
inline void sweep(Range const& range, PriorityQueue& queue,
                  InitializationVisitor& initialization_visitor,
                  EventVisitor& event_visitor)
{
    sweep(range, queue, initialization_visitor, event_visitor,
          detail::sweep::no_interrupt_policy());
}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_SWEEP_HPP

/* sweep.hpp
UcWVFa1DQnVlx29ftPl8023M92Dl7XlMWKmhJfFb0rJF5U+0VueMEG1aVziH00n6R8MAcnGa/xB2AOZV01dnt8b9tTtx/CFHvEvCdbyBhYsODWjkhDdWuLcfufCXH+C2yswIGHnYSgB0CRbY/B4LogMXIxeRSw/ylhWkRBVPNPSIBYyQEEEspvQeKqPy8uyAL8XHBMb07mFHPy4TgkAIX31ZUYmPslQJPxScKTUtWL+rzlF6VQcp9UKY3zT7sBw6FDsqc4S7IFPf6OL096Cr/A2xfj6fTvBzYpq9/Y0ZTJ3Cxqryxtg4AyqdlS/1X0wzyTVVMQc1bPN/BCYrohXgIhdC5x3eZ/AN8qlDEI1d1BKmYVmYsnvLP3WTprK638HXR6NdJc0WOBxZzonsidpzo26zodY5mfHeQWTyHRzwz/fwl/HQuaii+kZC4ZOIRcWUa5mDsdmXBgT7zc6UqX1XdsdDosLHMznJ+d5pTDUQ2Ar1U0B+aw0d8Sz4nkt+B3OqZpYetFtIniPKcLa+IU/ZUF2wQNAXhmagVqWs9EpdtZR2ImlrgvwcyT6pEg==
*/