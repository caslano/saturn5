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
T9s6n6v9eEuZtk0TRkDFWmSDUlxFlxMpJh+h+4Z2tNmgsMH3USZBEPQ1ae7zeBpl5K0BUjwwT+OIWdFZlk2Q+6DP74fAhVNS7W03/BOdWVCqHGBLDHFhb0kqZVZ49mxKMIYyKlyKvKtX5UULT6tFytyv8YE9VFP1XDNelEHrwDirUT6tKZJobPn0qWpsTvEwnikqMyZ//K141sQiZVNNxo2OkL7HrtC4wQtpNvDvLTVtqpcmUb2BKGWqL70GxrlT357UrRlj+wIr3aob0ZKQKWpxwq30K/vYbeuNV7YuHVrPKoU8rIvmF82F5x+TKTn1x58KwTgvvZm7rk36AwaeD/56gEIvpkxw3bG+DFwt6DAbE7iwtJNNFcEeTFS+htbD1+/0HO7u64vLD0eXJy3uc0Ieq/lSPU/fnF9ctnXHJO9Fme7F0lsWT0eYdh5TGKCUt1HE+8bTbaMy3lW7e3WJwfiXnbUv2jYCt4Osu5RJUmoHkgSHYgtFY2AJHypX5FE2ty5gdSigdWhxL3TtOvderVBtLvTjDhUuP8f4nANIesOGKdxA1xtLUu3taxRYr96XuFLxoYQf1ZP1X7QqySnnKVeee1f4fNR+FREO9Ab+a9+dsLIHyTZSLV1RNy8P709p9iZz7u54k1YpjeWP
*/