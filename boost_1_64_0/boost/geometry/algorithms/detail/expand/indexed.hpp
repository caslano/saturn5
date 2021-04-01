// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015, 2016, 2017, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_INDEXED_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_INDEXED_HPP

#include <cstddef>
#include <functional>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/util/select_coordinate_type.hpp>

#include <boost/geometry/algorithms/dispatch/expand.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace expand
{


template
<
    std::size_t Index,
    std::size_t Dimension, std::size_t DimensionCount
>
struct indexed_loop
{
    template <typename Box, typename Geometry>
    static inline void apply(Box& box, Geometry const& source)
    {
        typedef typename select_coordinate_type
                <
                    Box,
                    Geometry
                >::type coordinate_type;

        coordinate_type const coord = get<Index, Dimension>(source);

        std::less<coordinate_type> less;
        std::greater<coordinate_type> greater;
        
        if (less(coord, get<min_corner, Dimension>(box)))
        {
            set<min_corner, Dimension>(box, coord);
        }

        if (greater(coord, get<max_corner, Dimension>(box)))
        {
            set<max_corner, Dimension>(box, coord);
        }

        indexed_loop
            <
                Index, Dimension + 1, DimensionCount
            >::apply(box, source);
    }
};


template <std::size_t Index, std::size_t DimensionCount>
struct indexed_loop
    <
        Index, DimensionCount, DimensionCount
    >
{
    template <typename Box, typename Geometry>
    static inline void apply(Box&, Geometry const&) {}
};



// Changes a box such that the other box is also contained by the box
template <std::size_t Dimension, std::size_t DimensionCount>
struct expand_indexed
{
    template <typename Box, typename Geometry>
    static inline void apply(Box& box, Geometry const& geometry)
    {
        indexed_loop
            <
                0, Dimension, DimensionCount
            >::apply(box, geometry);

        indexed_loop
            <
                1, Dimension, DimensionCount
            >::apply(box, geometry);
    }
};


}} // namespace detail::expand
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_INDEXED_HPP

/* indexed.hpp
7Tbst+6y/40XegSlwsY3pc+NcfQ2LccbS+PxLBlDKr/p884TsZHDqEbMaFYKJFvTUG1zmEL1skb14yFlVG2NVXVvS/wpi2iB0pWijTCY8hayDEcoAFAiAcEEDrj03omSctjaHfsDQ/BgsAKOB2jf8JFxnuzEBByUgWaVEVsbmn734GeXWmm96l7KuZ64VnhIO+QYppirSb6RgT2DCYDn4q0F+ZwuDTTm8wcm7y0R4lK/Ln2far2KXD3H9STIxcXA06nzSvHTNRQIz/647w06gfnI4YNZ+TLtZlqekTg8FMQ1C3qqDcf8M+r5MppDk5sOmouoHf0oTHyfjyasF3q1jpy40Ho7jhR7aoN4Bq2hOAbHX7o4KhrL16Kkd+A0jSiYTVmHCZTdcakdQWjKMMriN3uRFXW7h7fBlhcvu17LPZgimkI74vaWycMP4lqGw370E8Fjyvmsdx/EZt3ERIFN4dWP8oYLOuzwHa9breS2K2w8CZmqkTxWb5k8VVpHdeWHG189FlqppVcQ7yBj87a0BePFV96k6wczg0FMW26wZR2crbGenJZZfbrf7w==
*/