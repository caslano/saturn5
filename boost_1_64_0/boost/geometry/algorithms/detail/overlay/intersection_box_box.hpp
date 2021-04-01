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
KoPRlpVIn+uguSvH67U+i8c0p35r1LvvKPqmtXqDq3Yn/kd5nP4D5KPQgwvZSf2V0g/iEJm06CftY1Q6HsPaNITDjZSYWFayZtWs7CqegOx0PoB036IhparWOluivB86GMRn6phtgO4l9ZJHDQtRHwHB+PAQJh1LgKqGZFMH2sI6bjiZDRE9HkP8srSbZL+MzM6FwQ3l14z0EJwxqkVNVCOxj2Sc5ZM8T9kHc8SC7qmlevlQmXvPMR4rgxJmDfjba89nZqiYB/3Zuzm7zj0HSh+m1D5ueYYx9svJeVcc+LV5YTU59uYyzlBhk96OmqQP/+5cBmbQS0dJgsg+UcqskNQJ+ty0dIlSoiz29Zxsrwk+vhV/cGCUug7GnZHs+0tnL57XKqOPCp4zpxUL5i7TWKeFy4U7AqNQUlaZ2a5m6Tk2bLXoVvRPaxaCnLX5PPGnp7pscWAM+bmMDBmRpEV9UEw+Gbgpabyz3n9UJSDeI1jYfD6pZsqT3psYEf7YU/+ckJy3N41dKyrmAhIGqVnKXXFMYyFz1G+FsHnZ/WZzX0n7XEuDNbqJ2dfZXQ==
*/