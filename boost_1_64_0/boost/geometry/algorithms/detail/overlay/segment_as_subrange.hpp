// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2019-2019 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SEGMENT_AS_SUBRANGE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SEGMENT_AS_SUBRANGE_HPP


#include <cstddef>
#include <map>

#include <boost/geometry/core/access.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename Segment>
struct segment_as_subrange
{
    segment_as_subrange(Segment const& s)
        : m_segment(s)
    {
        geometry::set<0>(m_p1, geometry::get<0, 0>(m_segment));
        geometry::set<1>(m_p1, geometry::get<0, 1>(m_segment));
        geometry::set<0>(m_p2, geometry::get<1, 0>(m_segment));
        geometry::set<1>(m_p2, geometry::get<1, 1>(m_segment));
    }

    typedef typename geometry::point_type<Segment>::type point_type;

    point_type const& at(std::size_t index) const
    {
        return index == 0 ? m_p1 : m_p2;
    }

    static inline bool is_last_segment()
    {
        return true;
    }

    point_type m_p1, m_p2;

    Segment const& m_segment;
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_SEGMENT_AS_SUBRANGE_HPP

/* segment_as_subrange.hpp
6KK5M/WA+EbA/pcezehqtEEK3zi4uG1n7ahJ5LlB/CG2PGVI/fUgtRvmj1h4vdzR9mLOnJQSUsRKBioZwj+fid/SJFCvazvaQV+mikK97cR6eUrdgBMZXAchv8TBH5kNEwQT9s2a6pXcw/46O1fRFNevQKSApPUf/ummWJVaMCWUMFLb5CTL5nrYkBXK/fSqy3YOxVWBwk2bvQNNHSFbbfVcnMxz5/3pQ1yLcdyKVNRtPHrKYZH5nwsfUHTkCo3J6QGC2flj7aQKTJHkB5HdiBEalOj3WQmyGYc0K1GxYLkmCwtIUE9oH8L3AxQG3HkDPOK8ZykqyKJwJaMYFNz5uClkr5a250QDugwL4rEZGaCzmJo8lFpy5/VbnfxD91VhepLlEF+9dIHeZlk8Cv0IWBEFOCrjnmmwEN1WIJ0GiQXu/HHdaSF+DtgHqw98IYZSrZubqAmH3OIXiXJc9RlEHEcS1zvH0PXquc5c8JQl4RIPEfNTq4R728QB7uT7i/W6NfR5TCmrUUfqMrH6xNsaRf3E/k4+O9RAtnQ0VqhhmnjxQhTH8CWdNUDdYw==
*/