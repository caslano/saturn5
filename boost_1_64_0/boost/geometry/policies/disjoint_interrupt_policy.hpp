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
wRn77njF2aKgaCk+YepUuU12UnQHasEruU/RSk3zCjaFtce909EVm95VHqy/bxMqd6AOVeCjrpmHJZ+yRCaUA7b4+6Q6XxMjhsaehrN01waA+awyUnM8o2KWRLUZiDzHOgQivgxsJvzQoGnkghQs5lQbq7yfmVT0SuL5GgxNCF9EjphcFKyzccKVJneXk+MGaugdCTegJ/SrTknT1dwS5ZGOj8v7Z6rzUc61SuX6D+2WM3FYi4yfy9d4BkXOIJo6vP5StiuSDfoOJwNMJiLKy7hD3o8325bN/96zpYa/r0BREs8XFmWiaCdnetqiDQHLpfRx2Y5vEWBLjWbsd4dhuMbt5A2+VcciRVVyRVGKA6B3FUcZv+bp8TOBWibjgY9SEbzztCelwo2zsRcRQuKKYB0Yax6mETDBR+Kjbs3pVsaAQ0DRTfIQ6LhTSWiDmRr1XYpVFsQzN9Gs9gKg0ZY9X/YYZ2B3h35BGLgWyESFPuEiJU4nknOVV14s1+JHFCl+k4SevmvME3xTqMIioADEER5IR4JKlSpgg2uBfMJ73SfCldpJRmRFXNPOSQ==
*/