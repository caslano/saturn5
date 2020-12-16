// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013, 2014, 2015.
// Modifications copyright (c) 2013-2015, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_POINT_GEOMETRY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_POINT_GEOMETRY_HPP

#include <boost/geometry/algorithms/covered_by.hpp>

#include <boost/geometry/algorithms/detail/disjoint/linear_linear.hpp>

#include <boost/geometry/algorithms/dispatch/disjoint.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{


struct reverse_covered_by
{
    template <typename Geometry1, typename Geometry2, typename Strategy>
    static inline bool apply(Geometry1 const& geometry1,
                             Geometry2 const& geometry2,
                             Strategy const& strategy)
    {
        return ! geometry::covered_by(geometry1, geometry2, strategy);
    }
};


}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL




#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template<typename Point, typename Linear, std::size_t DimensionCount>
struct disjoint<Point, Linear, DimensionCount, point_tag, linear_tag, false>
    : detail::disjoint::reverse_covered_by
{};


template <typename Point, typename Areal, std::size_t DimensionCount>
struct disjoint<Point, Areal, DimensionCount, point_tag, areal_tag, false>
    : detail::disjoint::reverse_covered_by
{};


template<typename Point, typename Segment, std::size_t DimensionCount>
struct disjoint<Point, Segment, DimensionCount, point_tag, segment_tag, false>
    : detail::disjoint::reverse_covered_by
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry



#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_POINT_GEOMETRY_HPP

/* point_geometry.hpp
4DV4/DRMWyUWt+GioxeoJWnG+46YONc5fpO7YneUsSTTT87Los+DwbGfaQgf+UuHalsGvn5tn6/rLz+UWBfVJ6mhi8TPGy+qO+aeoh/ZQSvNR5PvqIZOyK7uptIfn4g4jG6cTZ49bT3qFn1mHn0NrXXGXDxcLL670v8/Fb8j1WZaWlN9w6IUMahfbz+QFq+O3Vif9nnQ78Vhrs7OvUi9rhrnd9o4Lej5ntbv4d26uvRs4z3jTpqC+t3/RzhDv5pLW29tjI/rjYasE4/GfuQxeO9a2eDHW4nn0RwXI/CvRGZc6ph55DYW+Fl1E41UDl0h/56YgfPn1S8+Tz9uDDfYsOD3coVdftaTpjwnr+HMCD9fVQuO4m1N5M+I1vqJeo6bLc/8fWK4+sr3qXIn+yx1k1/H29dXmOaWq4Kx4tI96O/tPqMDDZYf8KjeF7BefWhzPh2xnvoxxzjU42H4a+pGuV/YfPGwseK1Yi/7vd+y7+YRHBw+j9yE+2yiM/eAjbhc+yT2hY8JTaxzPderqkeqx26X6UdS4NkgexTMu6q6vHK+WMGLp52gSU7Gy3rLC1yx0t1ygr5Q+Dran57w4AzXzYcvqLFjElwDz97is6DHLAOXZ6sdKWlwbKOaWEVsiPvC8q/qa8a3SizOUfde5lsaUcXXYQD8yZtsj74xfdyG/9+hbcK1FXrZ4UtpBHx5NvwdYu5vfUnzzOxcLrcjsQ+wJj5+NVucBRvkQ5Zm+Lf/byhrHeZTMbEQLp+nd70fLzwY0rX6bmpqwcpyXJ2ubsyl34IBo6wRmOdYnLvsI2KsPDyax/6R64mPveZQ0t6hXhXtrb3dGvAg+ssAtfJ+vipON0+lGU5gO7rF+FXiG+4d1Os2OyLHS+HyTfWY/L9Wfn/4fhR217I2WRDl/Iy+1xRWJPYVuGYT4y93nfzcJMYqmgN9aMs7eAwMPSA3b7YvaoT1kgrO3U1Nbl5aTHVQz3erNXtwmbF0kb7yTXzV/F6+s13em/U4mdTVY7GQe4qeUX53Uidzyq1cz+LHML3C0MheE30Yjvn4K8ZIpz7vS/cTwNDp4mTMIXF6rl64ut65kuPVqqG5g+eosxt7XrbfvrTR7CCe37fn6Ef6x9qL2SOJpj48Sl9nfaS2HrMYm8OrL+bpT3rTCRr5nj3e8/VDnd7AKdWb3urLyrtg83vsd5/aAVqaNMdd9PYdt+lji9v3Uloc+re+/Qdf4vx30dnCUj39WyefHX9EXXhZft9QSh+YZA9XJfVWHauvh2kVx7HtvRhqrsuWi+821mx9fZKal9ZB35NFfduh/1hx8v6F579Xt3vQmeL2QI2wr1m/0+NqHOEpuXonbeO8BO7iMPTp6nqDIcusB/rO0Jvk2xw+VyuKDtLL02Q7dRNvMHWcfKl0D2yBC4/rVfKJ71Ew9iX+e4O+2gGfyoZvr1JnC3WHSzP4TW4+2iRSi8x3Mnwrji/R1o69d/L96zX7q/Nyfn6q84vVhcnyKNB+p8qdZsZxwvcXJfboWk+egsvSGZ6Tc1/1UYtegSsjxFiQq7BsXQ3H8N/InXov+FJrBD5CJ2wjv2usxHNgOOgIfR8I6bwjrTK//AaXxNpPeoue6+TRfrWuGU04DYf8xnq07028Wf2We1X0Xq9tcsx3cLe+eH+NriJGZnQRq+YxJTMNIHE/Qlm57fib5iViGq7eSFOGQTP83HegfrSseyfY6prv6VCN5NFc9SeFprqcPcrJ0ytwxs/EkL5532qa8NfiEN88/qG9VFvVm/n27oqNyx7XE54F5/M5fj1f5KSLlYVFhayBt4HpD8g9tWZTYt2qHJyEPUXH67XvFht4a+MhYu1F8ZibjiFHR88=
*/