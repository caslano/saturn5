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
z3T/ByIrIfzj3br94Sxub8XFIn7ghglWu3UMBpPpALcgShxLmCUQM8T1dxtj+zUo2pNq4Rv4lLiLYzIs00oddc5aV4Uz5ohpMVjrlkgN6hYhDxo+WzQjePpVZvdM7OaDSIMymO3mr+rlsM+DgkOonKfbIvdw3M6o7Ct26MXoPkPZywAWRFmJwbNYUSfOM1rh1p2JVugaCoveY8muN/BfxbuwslxugG5JT5/A2PH3c96gnWRB/lkQPbUuQM8b+EU09LJV//rIPP0M4qQgehIS/0U+Dpk4NM9qEz0yOeMYPiwWSEvkXKVMjcitFCC5lBvnU3zNQezptF/wPfeREPkxhLt/oe9zH+G4swmjOWq4zffbmbSYOGHC2ryD7nb/5BcGupS4y4NG+3I+xlOwtBfLDyvtag206CUJNztO4Xccm3Gj42H1PKoQKiU/Q6KF5tw/uP7m6C+4XP8aROpbMtFCCBFm/8LtjbntGkf979Bt1/QOaFINp2NWoFJWZF2TxzXK9PmE9M/eZoacunGc3vfp2TH232n8moRxOHtOi2FF2AwVMSPY9DG+LsalaujaM9Wl2kOOQjWi5Mv5zpXYNc8Ny9k47N5t88Z9K/ztGbX+umA8tCKrNpyb3ZBVGZoajPmrQUT5q1hH6qsXhK3fXc/EFD+xRtGytSw25vs5KyvMN83bdmCV0+CG1IXnEOvcxDza169F4Xy+3p2rDaAp
*/