// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_COUNTING_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_COUNTING_HPP

#include <cstddef>

#include <boost/range.hpp>

#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>

#include <boost/geometry/util/range.hpp>

#include <boost/geometry/algorithms/detail/interior_iterator.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace counting
{


template <std::size_t D>
struct other_count
{
    template <typename Geometry>
    static inline std::size_t apply(Geometry const&)
    {
        return D;
    }

    template <typename Geometry>
    static inline std::size_t apply(Geometry const&, bool)
    {
        return D;
    }
};


template <typename RangeCount>
struct polygon_count
{
    template <typename Polygon>
    static inline std::size_t apply(Polygon const& poly)
    {
        std::size_t n = RangeCount::apply(exterior_ring(poly));

        typename interior_return_type<Polygon const>::type
            rings = interior_rings(poly);
        for (typename detail::interior_iterator<Polygon const>::type
                it = boost::begin(rings); it != boost::end(rings); ++it)
        {
            n += RangeCount::apply(*it);
        }

        return n;
    }
};


template <typename SingleCount>
struct multi_count
{
    template <typename MultiGeometry>
    static inline std::size_t apply(MultiGeometry const& geometry)
    {
        std::size_t n = 0;
        for (typename boost::range_iterator<MultiGeometry const>::type
                 it = boost::begin(geometry);
             it != boost::end(geometry);
             ++it)
        {
            n += SingleCount::apply(*it);
        }
        return n;
    }
};


}} // namespace detail::counting
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_COUNTING_HPP

/* counting.hpp
qrByyJIVnizsxGqoh+KqF8IFb0g5Nze+YMO2ewwyv3mB63r2vuCUl1zG2jM4jxTjCpSPizjODpMVGF1iWV19Qcwhal/+BWR6v8jLTHvRKX49QbRsqkF5nilQOL5vN2WWvij6mepIfwCZf3+R69YmWGVWP3jFi9b3cO+E2ZGBcQS4qufJYBs+MuOb4ewGvJWdb97yoqgvtT1+EjK/FfXd36m+l4hxHgfIQJzUdxURn1muBuX2csg4rr9om4dpp0Oo72k+DzNOO9t2kEu+gddBu1Z3W1bpabscEjL/Lsqa0KmsLJd8Ha/lZXXiwxvtZZwYFUKPwA/S64xtT3VmO+i4/yFI9P5BOIl3zNY9P6x7/WDd8zjWvY7TQsd+E4jbX4I9/6XkmlFpsjNc0TKf6384DED+A0n9fwinuei68Z2XrB6eAaN8Sa/oWeDOC6VqeSiW7leGubSleq02TZlF3LgSTWOxG6okXYvpAa07PKiml+zyT8g8/ZKQf77kXCMHu+TN+HOObct4vP7A4/mBx3N34fHefUnYNHwMRNHLIVT5MuNZO+MAJ7EZmLPT/w0U+B7Gtpa9nKwcAwU+Nag2C5PFAhS4Th7hUiLyEUjnID3fTXqPxm+35VepcT3uLvSUGgEtpq7yzMPH1Yh3jvoe04cE5KseYIQ8PhETsZv52f6ymEMfAfEZJPVMEl+Ly6m/ftk5ma4QPROWW1KLX0YH
*/