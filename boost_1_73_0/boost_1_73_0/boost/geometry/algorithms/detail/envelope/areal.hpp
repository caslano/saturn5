// Boost.Geometry

// Copyright (c) 2018 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_AREAL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_AREAL_HPP

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/iterators/segment_iterator.hpp>

#include <boost/geometry/algorithms/detail/envelope/range.hpp>
#include <boost/geometry/algorithms/detail/envelope/linear.hpp>

#include <boost/geometry/algorithms/dispatch/envelope.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace envelope
{

struct envelope_polygon
{
    template <typename Polygon, typename Box, typename Strategy>
    static inline void apply(Polygon const& polygon, Box& mbr, Strategy const& strategy)
    {
        typename ring_return_type<Polygon const>::type ext_ring
            = exterior_ring(polygon);

        if (geometry::is_empty(ext_ring))
        {
            // if the exterior ring is empty, consider the interior rings
            envelope_multi_range
                <
                    envelope_range
                >::apply(interior_rings(polygon), mbr, strategy);
        }
        else
        {
            // otherwise, consider only the exterior ring
            envelope_range::apply(ext_ring, mbr, strategy);
        }
    }
};


}} // namespace detail::envelope
#endif // DOXYGEN_NO_DETAIL

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Ring>
struct envelope<Ring, ring_tag>
    : detail::envelope::envelope_range
{};

template <typename Polygon>
struct envelope<Polygon, polygon_tag>
    : detail::envelope::envelope_polygon
{};

template <typename MultiPolygon>
struct envelope<MultiPolygon, multi_polygon_tag>
    : detail::envelope::envelope_multi_range
        <
            detail::envelope::envelope_polygon
        >
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_AREAL_HPP

/* areal.hpp
Jb0NSk/er7VwgoNNND/BjfuGcefsb8rCv9FCPGH3YdYj94dMUrxSnsQxDlOecNRQxN7lMo6FOGT0GGuLlzQyH0Uc8gzTIrNvq63TCxVw1D/G6cXFJ3zA2cez0wRXstRkMAlUzsktElzmzcw3JTebrqevCShAmu5eaqq0h7dFWEtH4LHRGZWeckiPnHzm9Jz/6BJBEQptCP3bu9lwdJNgrXSmosjW1vDK1iaHkiuCo4z0aqdRSRdgC6azeK59YME6aFt22ZsQyC191Ij20ngLuZLayDkbyQAVQuU/p2lWO9PdLyHNbebT7DmDrgrLl+XMuJKl3MJWAcGi9pQgIhMsba6L2HMqPFnVc6O9Sl5LYr8yT62DJ2OiFvM0+V3thMk+oyTCUHHZOsTO29JHq7Wyy7+AHGZUKWpXshGHwaDcctYJan6/XANulv9ssQ+2Sfm/+/Nabw5bcjFo9yYYTtqYS699gofhdHB7P8VDbzzujaYz3H5HbzSLYj+Goyvef81mDrSpHHk2d9DLymjK957v19JWR5eZqXNCO+6g8BTqqqvaLT4adk8EfwuuIHMkgy4XkGsvvF6szqFIxpRsHao6gLXiGZNZ1upHqd28eMEfcSw1v+jNTZJ+i5NcBplgbq1B5exme/yl1epQyc8B
*/