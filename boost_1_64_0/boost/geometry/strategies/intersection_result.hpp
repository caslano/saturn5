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
wEcIcR/+wQb41uTtBiJc7Qlgl4KVjzYT1ysQjds+BMLMKw7gnXuziVkFgOJ8vA0swfdhLkkDjBeA3+YbTOMrUgMY8Rzi/jQURg/IT8mm6b7JzIZAqxzvpLS9s95KT9brYlV/qDqJXRtggxyVjv1X3xieIa4CrCaEk6So3vMZ7v5zeVp+hh/BUvriO1CNtulglQHcn1AfBnGpp8VZkBFQmh5O8a8J7c9srn5kDBVgTrDpzmRUMEHmWj9dsByffju6hTmYz9TTL2oKP0nExqFxYxVs7BJVbK0eRaHXfeq5NSEiguu6Mjxo9mMPn4BvUOJcHbPsF1sN0Dyk3QEQ3UrDtdEI0/Tjmn6xOR4c6+b6cFIh2w0cdbfjQbq8SOW8dVb2f0RwQjIy8Vr7CoIDxxohVUuViWruwWuQAMCpuDmKvYoIHd+HKxsbsjC0eFZCT4+OWtmNS5wlhrqNpc4YowJ7hNBrnSQS/kdcI2UNYptYSQ+g3Fp4enhHhWl2ZuphjKK9+KDJyii2lLDYnDDkv3uH5JFoDt/iR1y0BEzKjVTjnL1q6rN+bgPw2aC3gQ==
*/