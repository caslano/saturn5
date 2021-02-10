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
gsgw3vzLbkEJ8CvAyL42Q89X3FPrYIRZHemZFflXJz2WiGi+8ysSkv9Qkn8jSmIQ4B8iHDoFU/nKIV7TldOboIvnT+zc/crtYh0epaTnhPTsDD7Pta/xojkXz7YaeavJAmi7OReYutRcYgo0XXyLHxMXu/CC11MY19G+HAKrnqpSxKuL+GVK5BHz8klxvMcySPljOwxWaWzD8jnOp1yrqoXRDjmGvGAow+3YRnnqAj81oS16gK9wEvZIOIoEBp4GUyI7USVLI5YNR4/UqFxhTnxlxjqajTyfTC4r1A98YJGQlEgUN2HCUC1rydGowzGVErA3qFkuaIc16WhPmuA4aT0kMHZMLZlO4qbhS1IH4HWTBBPFrMjwE2IFpkjAfqtdsHd32uqpN5LjrcSjiIr3/OXLvpdjxPP5h7s/MMH3rhnCG9tLouF2cZ30vafiTfQpmYDwZ7MSxZ8wjt4P0feoJQbmY4GqQffPR93ucffYdwqnKFYpMhkAIX0NSzPBrwe6vR9mZ4oGaBWW6UBjm1SKrrrUQoXSpul0FAkIsFGeAFaR5Did5ts6GwyhGDBcM8xP6MZys1YIswnkWYbecKidzZNrt/KQqzQ7ltU5ClXZVjA3ZfXkX56ev/V0XaJEKnkh1CLFP/WEOR2NF5WI
*/