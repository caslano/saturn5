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
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
*/