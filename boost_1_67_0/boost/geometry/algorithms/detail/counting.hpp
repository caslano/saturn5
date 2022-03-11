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
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
*/