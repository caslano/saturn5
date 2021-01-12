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
PX7/wOlOVUUSNDpuvC6MpVg3jnDauTiJoyaG/RT2MI10tO9yuqN5GqZNE8E3H2M2O7OcpvCyKAzjqIy4Ce+c6U6W5xUyT9WoqqijnOVZarPY+fEbMz+qejEBvTKlwZhI8NEuPBxRLm3SpN3jF6kSb/3iid7w4vaBU4hziNa4ZjeNTSuaGtsefiZ54GVEMzTO59ZA2gXHWKBB2iZe4EC4T4eRF82TJIrH8uZdPZoV1OyS/VDP
*/