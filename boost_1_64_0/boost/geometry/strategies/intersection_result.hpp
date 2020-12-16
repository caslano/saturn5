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
R5alw3onnxIq/8jRBzv1+/E0PBsf7cvGBzwLH+3w42q4H9du76i6nMBlkfa1z83X5dP0jqboHfXSc/Pt8jNzj3Hq1vl23ZqODwf5No6H/tEM+kfT9L38+3DGRwWE/rp96MKB2xGu68zGz4YnuqcjfZTIpu+Dz6ap63w/VQ33UoXciAKaZjrfpYl8g1bn9lGhTu3DHMluB7BtuIvt0u84T3U5v65I19eFmi7XhRrk3OplgWXncRCU7Hx3/pwcBcSZPzpf0/fjaLgfV/ORjQ94R3zAsnsO8Owe0/x11NfZNMBfNj7DO+Lbbe/IP+DA9Y43MN18jZE9Xm57s+sE3K7Tmw8M//i6/ZNdH+BufW4+MDBPOksk4H6JysTPno9+zv3lXH3q70kv3KYMu3lG1DxkN5HzqW98MA2H/ZENBwxN8tMFLJuuH6601+jECP0/PDw0c2bqCYeODN+i29uthKtXs0tC/jvCdf92qa9bKeK4I3x05PT41NTkSLLU2HZgJ7ig7YfDDvTD7HpFZsd6Ac+uF3B/vYB1qxd52fW68uHCM+t1+je7PsC99bnwzP515c/f/5nlHHMC5bqMtF2uCzXIfSdKgGdT0PLeUS470RAcZuMD3hFfz8ue+iObkvb/kd/v8PDwoSHx5ejDZOTCoWYBfZgH/9BhiWh8seEJPiA6TI6Nj5jKcG58fAzfU3Lq5mO07XyWS53Xxc/V2z16Kqfv0fMtLitMvHELn9/9YjNiwA2/yjkJvwJ4EgZkvCThb0rBlX+9kQHfjb9ENwV/oczfL+NXpOCvJP5ErByPb5DwV2k4n2erHdU70nD69NHnhIS/T8LfpuHcduXnv+6pf5OYZxL+XQl/noG/WfSbhP/Cxgd8i+gXQAXAgaNvV1Q/peHb+VmTp6p+kvDXGvhbxbio8fXQv60hBuc88G1iXNT4euq/HcUvkPCVVP05SXv49Zx/p8AOr1Dj/qYtPfnj/l2BHmKJyYtpPndUMPNKlcaSOMqJo1jkFSryXGm5GLfo8OVCJA926Euh2DyP763KMrzd6nu93eI5ERElBJNeoVSvtaKVluansniZTjzidlVktaoxwQpL9bhVKzJZphVfIFx6NKfSulxYqtRanvwgwW9VShdIbyxGgh9d3oZze+vLDTRS8dlsFNrk6lWVL1aL52M+VyvMjc/NTZ6ZLozMTR/q7p+nji3GNeuQTs6nhpS76yIjl5zbLdabIfdHWCpWqwvF0oUezgGonhK5plU9+txtsVRv05NMUbNZbyb5KI5nnJI0P9vE6X3xg/aJ9t5PuszPzIxPi7aPTc4WxFne/vuWWisPDO+n6D0O/HIttwr8ocNH4nBfHD5m5di+oaNxONKm+MFxOF4r0ZeHxeHpYgk5W52nh+4lH+F6oNRNm6SO2Cfn2l6tb1mvvTXH/fhOOSF/nWcCv80zgYN9TOA2fUzgWX1M4LlSMV7p44F4Xh84QJoIiDQIfKWPV4A/U6x88Hmg8vcDfczfg/qYv6t55u8teebr233M11f7GPE7fXJs8Jf4z3N8Lc/0b9fPdG9PfwToDv1MZ3s/09nRz3XfsZ/rvVM/13fnfq5/Z7/dn3eR5XZJ+G5Jd1Di3VXSv5uke3dZ/z0MOts+5Oqvn/zjH/8IVhm2O3QED6sP+z/Uuz7tRP+EorPGRwYnFB0M8c2HmXWic26d6DxZ0YGs33worxOd6jrRaRl0BoKbD1cMOieCmw+vUHSgim4+XAWdtQv0uwSdHuZPt/A+RQeq9+bDRySdtTbtk4rOGufGF9eJzlcVnTXK9HcVnTXK9E/Xic4vFJ01jv1vBJ0edXnH8GFJZ41zbFuKztXg5sKdFZ016o67g04=
*/