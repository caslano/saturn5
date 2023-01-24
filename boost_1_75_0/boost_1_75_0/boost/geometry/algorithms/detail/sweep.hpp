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
HrZOGj6MfbPKYkLcwka4DQpjuDmXgOgxJIz6D0nK9poLLG2gpae1NLRtS9gs7j3EyUkP7mkszFAjGg1IE5djSkw1/bRYPTyp/R+HCB3ETCA2Q2oZwuashREtVLEFXaohAJ35IjOEzdgdtipt/rsX9Vd978CyEnJpS/FVI4vQ9Y+tJwmt3Ci36pa6ja4PEW2UVgBnXEhV/x9l7x8YRXH+j0/mJpvNsiyb9XJejuO8u4b0uB5piEd6pDEeMaSBRhpipECBJjQgpkADAgVEmiBQQKCRggIqDRQsUqRAhaIFmlCxqGgDRUQLNli1amvfaLUf9V3s95kfe7ubH/r+/jGbmcvd7OzszDPPz9dTyPaqhSltmjzsU9UmKKDF4yXF2A+yjVpRaAn040py0JNG5N9wRg93qYuJ5tf9xhIcMdZj9wKKu92VGnGR2mAUu4vYmFMxRd4ePoR7CgV9OQyVv0NJu9E2nwLRwEYQW22oMRyNm+/LJq4H/Vehc0LfV933EOUerI3ExjUXKseqVKSUa+VsMrmMk+XQGSVuFLziKKhMgtJ0Y9jEthSHsQ3bctqNTqn6FPG0kjFSDUnKD5B8EMeqaKiiFOgbk23PjUKWPwyVv0L55MawM29R0gbPws+mppO2OpeB/m4NpG4PvKRBRu427Cdl0i65XJmpPkmUvfpH6doGxq7GcZBZfT16hVhPr/W6nsrjMCRKY8ZBZTmU
*/