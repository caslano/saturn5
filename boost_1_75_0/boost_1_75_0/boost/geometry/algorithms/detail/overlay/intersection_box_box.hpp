// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2015.
// Modifications copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_INTERSECTION_BOX_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_INTERSECTION_BOX_BOX_HPP


#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace intersection
{

template <std::size_t Dimension, std::size_t DimensionCount>
struct intersection_box_box
{
    template
    <
        typename Box1, typename Box2,
        typename RobustPolicy,
        typename BoxOut,
        typename Strategy
    >
    static inline bool apply(Box1 const& box1,
            Box2 const& box2,
            RobustPolicy const& robust_policy,
            BoxOut& box_out,
            Strategy const& strategy)
    {
        typedef typename coordinate_type<BoxOut>::type ct;

        ct max1 = get<max_corner, Dimension>(box1);
        ct min2 = get<min_corner, Dimension>(box2);

        if (max1 < min2)
        {
            return false;
        }

        ct max2 = get<max_corner, Dimension>(box2);
        ct min1 = get<min_corner, Dimension>(box1);

        if (max2 < min1)
        {
            return false;
        }

        // Set dimensions of output coordinate
        set<min_corner, Dimension>(box_out, min1 < min2 ? min2 : min1);
        set<max_corner, Dimension>(box_out, max1 > max2 ? max2 : max1);
        
        return intersection_box_box<Dimension + 1, DimensionCount>
               ::apply(box1, box2, robust_policy, box_out, strategy);
    }
};

template <std::size_t DimensionCount>
struct intersection_box_box<DimensionCount, DimensionCount>
{
    template
    <
        typename Box1, typename Box2,
        typename RobustPolicy,
        typename BoxOut,
        typename Strategy
    >
    static inline bool apply(Box1 const&, Box2 const&,
            RobustPolicy const&, BoxOut&, Strategy const&)
    {
        return true;
    }
};


}} // namespace detail::intersection
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_INTERSECTION_BOX_BOX_HPP

/* intersection_box_box.hpp
aVROfDIKTbizATLh3deZq5lC3gO+bhZerDD7XoFU6MunFPcZF6PVl3S/L+lAXxK170Vwjvzti0p2Fkq1qdrbgq+ZEfHoVEmDbIFb18zKClLXE+uOot9V4GLC+pLw782atL3a1L3apPrGHsj2Cg5o7ziTn1oC5GY1vAfwrKamqf+o4D296apX24E+alIM4RagbSJyZrEpACYxuG8uNxUt01S1XeC9QlRfUmdf0phpzvjrRe6TJs62TYXNfUknM+boo8e8RFf5DdttKXKue74XyzY439lVOQFwC713iPsRBWlwNmnjkrehRKffpfoUpsZfMwNLdwbvxiGDHwu8b2/aVunGX+lmKNJ6UyXNvjzaPgAI45ZXW7zrb40vcl5t4l5tIl5X2q+NmNwRrHQTq3TbUTmh0yfbHV7Sn2Tp1Rbg1bYBUDjc1MgnYmO2VqyQ+V7hm/+cxB31ysI4+/Ice1VzJbGHujhhSfPsvQlFXfzu1hFfjvZdGA2fufxA7aGE5t+dpQr09wr/97omxn5/c5Re/ICgpHE2vyXy7C6/opXHVtdQO0CFvruqr4fExGX9CN5tco0cjS82+yJR/LGpso/vgfzy8b+iM2f/5iZrHn+EtNZp+p9Atls//5nC1CVrM30DjODQVaWM150rfCbW5PvtWMVWljAQzZD58G5B3ScDAh3I1BLgvxeVCFeUMh5+6E/61pf0sVhBw9rsuBCZ
*/