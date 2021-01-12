// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_BOX_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_BOX_BOX_HPP


#include <boost/geometry/algorithms/detail/intersection/interface.hpp>
#include <boost/geometry/algorithms/detail/overlay/intersection_box_box.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Box1, typename Box2, bool Reverse
>
struct intersection
    <
        Box1, Box2,
        box_tag, box_tag,
        Reverse
    > : public detail::intersection::intersection_box_box
            <
                0, geometry::dimension<Box1>::value
            >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_INTERSECTION_BOX_BOX_HPP

/* box_box.hpp
SHm0dJ2+ioUD5dDG2jKNAEX8li/Ie64wqAodxqEKlvENkuRmf1gfK2JkXmD83sL5oYv6pAmjMP6P5XsVjKelxS2rFIEgStf6dzpfejAuVv/C9uhyW3FRg1Uho08wsvuGdv4HUXDY3NmCI8r1Efwu1uKnOTkFK2AnOqPvP+jp9kW9pTO54J2HPP0GjG7k4ezYCPP+w2Mwm1u769zm+r4egzpLxG0urkoZ5m0P9JibsGWvbyMn
*/