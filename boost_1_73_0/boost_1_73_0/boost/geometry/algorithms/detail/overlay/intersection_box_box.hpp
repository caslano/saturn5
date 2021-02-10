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
BaNOQURAs9qJFQV/JWKdWGaQn6BlSybFdtLFXqBDT8TjHTVa95g9QRdZYc8a9gmtOIKR3QBX+kjDt3os2p5dzwOJNH3U1e9+JpqZafaJRG3YSLV92CqnZmyI60MJypK6cDOmNSrvpyuQ92zlPfOc/fSdZzs6rruMxqQW/K5Oy1xrCdbKTCu+12a+ZezaadSgCTAQJYGYf9qSx1OaVS7vlvcXqq0RnExDgstGvglyFqBaOmP3Kkn014ZLRqks2zp52UpZsVQekhz5sKCjrh2xCVK4MXS9Q+ewGiJlNdYjW4eGtMi2Rw01jBjW3hc51UVBlyoct7ab8G5SOrb8/fs/9qswxR28dCEIsaW/eeG52Hauz5mTNrFVWWqDoe1YnTkcIDyIIGUlmwuJuAEbTpjjghuqRKtL6qVQCV676DraKqMI6AzaeL/m6FQiTJc/NW7Up7hZR/WkN09BZKOILtKSclqjHJ0GDXA+lk52YXMPMrEV/OwZHNIGMjfebfdVtlLzakGv3ZDWc+6Rv0mPXY85f8AeU9Sz5GqtyB83OD6ZxFi3FwmN2dn/kLE1oAQdvbmQbOm9Wf9m9Sd4fDsJk+EIT/k4/C2Gozdwfg6nxx1Mfpr8UzO9OX7SFKYYEa7b1vh6HNZqTjt28cLe5PPf
*/