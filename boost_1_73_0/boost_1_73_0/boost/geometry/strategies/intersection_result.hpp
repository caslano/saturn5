// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2015, 2016.
// Modifications copyright (c) 2015-2016 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_INTERSECTION_RESULT_HPP
#define BOOST_GEOMETRY_STRATEGIES_INTERSECTION_RESULT_HPP

#include <cstddef>

#include <boost/geometry/policies/robustness/segment_ratio.hpp>


namespace boost { namespace geometry
{

template <typename SegmentRatio>
struct fraction_type
{
    SegmentRatio robust_ra; // TODO this can be renamed now to "ra"
    SegmentRatio robust_rb;

    bool initialized;
    inline fraction_type()
        : initialized(false)
    {}

    template <typename Info>
    inline void assign(Info const& info)
    {
        initialized = true;
        robust_ra = info.robust_ra;
        robust_rb = info.robust_rb;
    }

    inline void assign(SegmentRatio const& a, SegmentRatio const& b)
    {
        initialized = true;
        robust_ra = a;
        robust_rb = b;
    }

};

//
/*!
\brief return-type for segment-intersection
\note Set in intersection_points.hpp, from segment_intersection_info
*/
template
<
    typename Point,
    typename SegmentRatio = segment_ratio<typename coordinate_type<Point>::type>
>
struct segment_intersection_points
{
    std::size_t count; // The number of intersection points

    // TODO: combine intersections and fractions in one struct
    Point intersections[2];
    fraction_type<SegmentRatio> fractions[2];
    typedef Point point_type;

    segment_intersection_points()
        : count(0)
    {}
};

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_INTERSECTION_RESULT_HPP

/* intersection_result.hpp
lyGpu4W3zAwEOSKWWRS4QAjkAIMsD8RcI5Fr0YAP5jOPSUiZcgHXy1ST8msRzwVmSKU9Iv1RhUwNZrMa+dAfv7ucjMmH9nDYHoyvyeUZaQ+uEdn7/qALdmQDsYDQez+gDIgHxF76jk0tSfPxXo2jo9/ZrulEFiUV1J7OaBj59UUFH8zAtGa2Sy1tMurpH4C3yw8jfTS66lfJ8TF5Fj/tTIbnerc/ar857+lXw8u/XldVvIDWMkIDkaY3GXWtWfaW6bkueJTcuDCgQeAF2buhvaS3sNayQz3zhuVQ8ikx3y64vYyc0J4+hDT7DNToOiD2FTYsIZfGC74iHIOF5GuSjECTYPHymlKxFG1UHloSCDpH3Q9sN8wLgLNFl17wkH0A9yw6jeZcLw1udu+oA7ZNcG6ECwjs2DVxxTK0ksYRC43QNoGPkJgLat5wMegwVIO5ROC4O0iNGuyBvED11I7KneaoByruj6/10bg9nowI4o7YOgjQJUPCBsw9Zqx69C+AsGeaACfPvkPEek+/fA/mJJBlH/X1zuXF1Xlv3NPbgy5cDMb9waS3efSg1+v2umvGCURyXJX8i4/j7E6j2YwGP43Gw95weDnUz3uDj6f88Qw83kzjsiIVXAVC8K/Jc8afUQs/VmqJJlQBdWJL
*/