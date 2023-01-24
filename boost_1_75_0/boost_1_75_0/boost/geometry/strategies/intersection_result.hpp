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
v3zU85LnxAWcmBkN5skC11TKL5EoUKfFJuhyvmmKaNlRsMawxuB7SWjtyAlX2zIWCSNB1Ca8BQ5ZX3M2SI7uxerLHZoZyFBkupeA5d/Npbrzg1SdlBb6sixIh7b1rqIzvzJllpW6CVEP1to2xi73N7Z1uz8c878j1eilS87mHX8SfJY2/xZF9bs4OmnF1vZx2tf2YeP+/rCQg1UjYGWV2l+iYoFBgN4kWs8Stc343Z5w0N9OytslhhPdi5Pjo6jwCyxLltX0RO2qwnvwz2zznOEbEsH6aw0LCS8nmMtps4RJlWW67VWhEQB6UHzZGOqlhWtxc6y4iX28L9/8Uh3uLSk0TNZYy39dtxs5ZkBxHTlfxS8tzWPcVRjqbDLSpUg85a0zVn++8si2ylvjrx41VOdttr2gVlNUNi1BOpQOfCd7EZ/kNDLODtm21Qcpj/glr+rxDTCPBM8NJ1e/5YAmtpYYHThQkZMKcpIKun4S/LZUp6aU+cFvXz0w3170T/oSC069sqa8PysyMzNHaTRv8hMrAcmtZjMfSccTwFMH5w5fHO75U9mFU9SYs4ItqpeEKiNeuXj2RhQdQSc01G4pbjwr53TaaAP4yy/zIxn8B9qrD5s132Zms/9Ks4d2zYQFFWA8SdZEJC1Jcpa/XbsOh5L2szW2q7J7l0N7PuRgBtmr+uDcVxuW/FY2plOV46tZegWRtAj/eTfJVTN3
*/