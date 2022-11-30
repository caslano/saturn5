// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014-2020.
// Modifications copyright (c) 2014-2020, Oracle and/or its affiliates.
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_COUNTING_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_COUNTING_HPP

#include <cstddef>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

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