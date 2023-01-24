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
fDr+rHcoS84btVh3jZhOZN0I46EkEGEplNeX6TP2pcSX0f5tEPeTA1b3+qgfFcdVGzNZ0WWT6Kban9vbs2sfMQl+ukwGymJYmj3ITo/wLnpVXkXUnnPZUj7TMKeaeMWkwVxzxkGRQ4PJ7sGWkgsMVF+TBvUVbtrJ6gaP68bfNge1VrsbGBc5dBIWq0qzg+ZtSSvUZ036lyzXK5KskX77VtaopxFFd0mtPWL/kGO+QM9urp38E26KukGc25ZThD4aI26uVdt4xt7iLVxzgTS354+qPMa9fbelNx/oOM3RTijfMlb6xBRe/vl8ItUILDn5Mjms20iEeypj6KKF8PvUGJyIa0S4nT/gy/ZnGOafmla2001NGkOr+Ve4/7RRQYvaKtdHg+6TSk1wVYmCyEHrUe9N1m+gZe5JsDBtsFH3+9wgqJecm5mbytY8Dqmt7trcFmfLUmPv6VnM744UscT0de2o+oYKa13cfAvj6KtufCswpbghX+UyYS8DJbbxi4iSUMaWZw+zcipd/9qROOc8q9putAjEAs0L3zn2T341fZ2eFZ/EQlyEJwQp184C59W4rHv+VP3IFAmHEPDfc/yqSH/VQ5ieJ0kYfH8ob5Jqa5I4n16ymPievi2okVKmrNLOODBh39D2i+xwyl4OthriNaasgnE+19DNuC+ttEDjrMxnZaEYlMcMXMr6LWYBlBguj9uNogEA02dQ72RX
*/