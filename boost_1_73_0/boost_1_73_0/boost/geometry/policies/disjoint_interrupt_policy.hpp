// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2014.
// Modifications copyright (c) 2013-2014, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_POLICIES_DISJOINT_INTERRUPT_POLICY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_POLICIES_DISJOINT_INTERRUPT_POLICY_HPP

#include <boost/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{


struct disjoint_interrupt_policy
{
    static bool const enabled = true;
    bool has_intersections;

    inline disjoint_interrupt_policy()
        : has_intersections(false)
    {}

    template <typename Range>
    inline bool apply(Range const& range)
    {
        // If there is any IP in the range, it is NOT disjoint
        if (boost::size(range) > 0)
        {
            has_intersections = true;
            return true;
        }
        return false;
    }
};



}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_POLICIES_DISJOINT_INTERRUPT_POLICY_HPP

/* disjoint_interrupt_policy.hpp
drV85gd2m7kLjzUxYIgdrsdOf9DvrcVw5rt3Mfb5jmrof9WUkwpXb0kT7uHwJ0aJYyNAkh24/edguzrLjtJ36g8GEeGkecT6NZw1LXCtFoLyZs1H2LhF2CpNj/PtORDXO4ML523v7WD4ngbKv35Dyl+paowPwff7AvoXUyJoUwXYT+22YmYFHdolyFnCWQ3EYdj7mzPsnfUuf+2BGEEwCd4kQlu5AZtWH2UCra67XPrexCXNCgIjcaDVHJNDnPpBdeEitaS7oDxPJLFZm6BhNBWgo+rGcQqaPZkTOkxVZcgx2wFCIf6eglkBk+6m4JF79ByFBS279r0vwfKge4iudL5FW0RpwIyAq+P63hfZbOFMllJ+RiJk/gyloIAOmGMB7FMvnsO4yUqCgzLxQ+2Ka6ff+BPkcBqB9WLEulnrljEXoQ8Sf3F9XHHuD74C/AYWGQ9verS4Mf9muw+r0j3HBEmToFQ4Bm1xqBmIe57CA7KzJEeJt5AYxZD0CWu8i+7VqIcdv8M/6SORFYQnxFjO2ah31TsbO73h0IKXrZJHeSgZRZg9I5evNAbPafMQl31rBL2GEDElc2BEHqIDNMX0BqwRx1FqaUpjPiqsOlOfschER7UnyWHBuVDhPzIJq1T4/sWNvBDEx8UsQUI5
*/