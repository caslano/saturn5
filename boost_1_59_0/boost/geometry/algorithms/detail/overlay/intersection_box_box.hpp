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
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
*/