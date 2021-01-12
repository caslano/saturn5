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
/f7OJ/BvPeHq/Z3ZR/h9q3+IU9zq9eku/pH1LeU/11+v4BdF+65E2HO+V+v3VP2yEz8HjxfO9bv+5S68gnN3/e5svsTzvTO92Vb/12r9wPxo5YtxV/7itxjtv8/xwcb+LofwAcb+Llfk0780+r+pR4kPGPO/euG3Ctf97974EOP9xDn4NHF+ev3PDnxK4febuf0zXsX/Klyvv38dHydcj7++gY8x3m+Wepz4prG/Q298kTF/
*/