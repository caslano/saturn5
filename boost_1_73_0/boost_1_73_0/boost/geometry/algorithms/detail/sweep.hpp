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
2ho7LRLmCNjpsl8BYmNWulqd+nc4XgKHLSCxeUY7NXK25BJfPfEwKY5QDuebjqqbTgHRrpN99y7Uvvfb5Gw6ns0mZx+n3un4jP34BljYc35PgV1I3Hh/ZIXD+J0L6YT+1zqJfzfqN4K6UIXva8gQLlhrGo3Md2RewcCTbeqn6DWUZIldIHVz1aXZSdfgVX9ek8Fyjacjwe09ZAioBm+TMSldSNd0NHMTuYmRnHJUUzQ6u21lLaLhDLGaaep6J8wIvIEo7T5gU99TJ8k2umnTJKfGFLY5UA+d+OSPhS9VKszqYrJGhXJyzTkPsL+wwzlGYw40y6pTmKPnPvMjM7Gw4KtQkIXJtACJIx2sO64WKghK3Mnj8CMqadQnDRETLr4yk79FkUEI0gQmNGMJ9zYEmKFJMKJsC4vGHRl4iOpSaUJ6ashaHTG1Ul5nXzw5Ni+OGZjwgTZyk9qtxQyhkZSezrSfGE6wGwMV0LiG6WvFropkCj0kHxJwvZMlk8D/Ps5TY4eG88JbEZa+o6DYdj2sNclA9VsZsJFw3I+R5UFnyVlUp6564Oi2SkSpVtbAedh6QaOIpa26+a+DZiJoP/PAjUfNbMeLIivarTR0EXS36qXd2Tr23qUsXV+WF7B5xNEcswflBVv4hbSb/Uam
*/