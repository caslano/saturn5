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
jltlhajPd6VL2opBwUJ/WR2i8HFCdhVJ7kpWnbt2U7nqqXflVa+tAjJwhYTXkMvRiYgsuhdMZwIn7OggcZ+1bcYJD2XNDTWxZusouatO4JjPFumVcoCQ8CIcHpA4D+NUFr438ehT5DE1x1xxB21CoANm3IvCEHmOxqBND529x6lyEUUBxEl0e0dpEuKmvZWLG1oxFzfW2vuC63OPMFrSQB7hkOB/MkdCwMKjPXxE0CYRbpginOIYsy4J3TVlmSvEDYKEHrLkGklFJc8qQkMIGlRs0qr4qDaoFPgbw0ZbfZgUb/XIi5KECoDB6QYzQB+g8sKM5jBr/PDR8eStsoF457Moju/KDF82FXgt+ELxjFm9hEooT6bjf1+oM1C7g2N1RAfvVEiqpV2aOFIiZq/bhPSUFsuQPAby8+AdplQXd/CbPZsieWiTjm1NPw8HljPqf7J+h59rYfDkhYfQoGxsaMvq3LZ4R+NdOnAtZoBDyWdaVEnhqPGf4MvVqLkiwh0D7jcsEEyJJ8gYSahgRa/GM+fX+fBs5gxHJBQip6PUV/ynBfBlC9YPA/wXUP0/8Hw6kjvgy8HZhl+V3DL4CBKdBqMIox6L/Zq5WKfYOpZ3OugxdvcVUK0KZo1GFtn7Bq5WDTsjgbrHC+mankAR
*/