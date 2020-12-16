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
vq8S/BKC/30yvk+Z8hvxpoizvybQOeBt6rNV20b7dhfkY7/wG5NxLtriwMe8PF9/sVgMb8bHg9KsQL3/BZ9up/Hp/pvWn3cg60MHhrL+B2Py1XwzJoF3mMRYeW9yXO73kZ6Wj/LWjsP6C3ykcT4efSB3/XYNhpWY8SzlJtGbJnklYf2WmPoNL4nXb0SJLSP5EU3AWGd7lphvR2ERfMeEjvVeLNrdyLt3SbydJxds3875kMfB0Ebo40pf292emRxNtJO+LYwlnKT3QgpLVP+iz4Hrs5/Sc7jJ9dlf9an0YvUbX4L6AZ6rfkXEK6l+EwgnqX4HU3uvKs7Wd/0O2u9QQ399jvY7TOsLelTfI7S+gOeo72TilVTfKYSTVN8yqu9naHwNVN9KQ78iR/tWa31Bj+pbo/UFPEd9pxGvpPp+mHCS6nsM1beyOGsfjx+tsnlYbUk8PXakHR+4b0L0Z1H7dtH3t9kKD2HrCT43qoM5c9ybp3J4Hsfads0hxzzlE65HG0bH9b6gJJynX6AzeA0lyfQ+Bl181O4VQN/lzRoTr0cz8N/bZ3t8lzeCYpqcUBKH59EaukTgn435n8JYZdl4SR097qX6CD4yTGt8KxcjpVDyxBeCtH93J9UVu4fRmu4uQ0wsjasjoXf8zjHMn4YYVx8vSfBLnmpjSlDe9OnJ+/JBlnVt9cmSeFudWJJ8LqWlBH0aOHbP14q01F/Tlt560fsJ+XF67VjTxuPc0EfdeQjAmUbeyOSYDyvR3zoS6nDDWMeXzphDTgf3MZ8L0T9QhsdNt5HhUugEOLp/6Y36GPY40I3S6DNzkaUhcCPLsCBTEpeFz5esojlmrPqiwvQi+d++z+JspWnhD3g4cx7VCXi35oc/u4deZ2SRPP+zdTpD1+uwPjLH6Y/Pwq/3uDYWb8a8ldMVRO9of7bE+kL9V4TmGfOamht93zVp6bfaJtDlBJpXPk/tdl4CzpmmPxcAdjD674aSHDFeBpbL231nl2TPypxTonHZYun1lD4JMX3Psf0Ycl0AHJXPxQSi+iXZ7l+GHdpk7NCvlpCfh/rUxVG7Awaaume5pCS+l+M9y9dpHWL4N0t4P4E1F3sp/Iztu1tweUl2n9M1iH3Oldo3Q9v95FFqx3t+tm9+uyQ+hlbRHu0IU58M+GPse/j3UX5pwvrl8ipo3FxdYu3qUP63DuQ6DAt+RPZaLrxrqf0uLYjzv5Lms422fUDXwq83fO8dn8VhvjcqnRB+NOrp2sa/C2v65ybofSnt0W7RdvK8sMclfminTainwHw9Hz4w7NvHmL79C+rbt5FufqkyC8z07VljQplv17qHsdFeFyGmCJ+hefZtn2HBHYS33yFxvIqDQ7zfEN4BhPcw6N1NeFfsE8f7xj4h3r1Y64KCsJ62zH0lsTKCE5b5HdH+uKFt30+5H7Q3j9qe9haivRlyP4AyT+ZvX2YrlXkSfB5CmTtGb1/mESojOL7Mo7R+5mqXPxBernb5I+HlapcnCS9Xu/yJ8HK1xTOEl6stniO8XPp/gfBy6fwlwsul5z9HczPa4wG8RQS7XctYX88r0ZjSMuTDIvhuB5MPi3g+PAie24gmvz/1OsFdO1n4Pwke0DuubxF8I82Rb5PMmwch8ztYi+83b+G/i/nK8nqPbMf3SRZ+S2vIlDj8SZJ1KMFdW1v4rgJHXaRvDK7Nd1OaKEMyjSA4t/keMZ6Da/O9iCa3+d4E5zbPJzi3+SiCc5uPick8uDbfh2hy2+5LcG7bcQTntj2A4Ny2Bxr4RqxnmC89/CAL9+sT5j/AJxJ8C+TfDPghArc+yd5d4m/+/0N8lDs4v764qvSolvoFsxfiBBFn6/fUw4Q=
*/