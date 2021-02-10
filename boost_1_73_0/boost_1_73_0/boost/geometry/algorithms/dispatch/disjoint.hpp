// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2018.
// Modifications copyright (c) 2013-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DISPATCH_DISJOINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DISPATCH_DISJOINT_HPP

#include <cstddef>

#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/reverse_dispatch.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Geometry1, typename Geometry2,
    std::size_t DimensionCount = dimension<Geometry1>::type::value,
    typename Tag1 = typename tag_cast
        <
            typename tag<Geometry1>::type,
            segment_tag, box_tag, linear_tag, areal_tag
        >::type,
    typename Tag2 = typename tag_cast
        <
            typename tag<Geometry2>::type,
            segment_tag, box_tag, linear_tag, areal_tag
        >::type,
    bool Reverse = reverse_dispatch<Geometry1, Geometry2>::type::value
>
struct disjoint
    : not_implemented<Geometry1, Geometry2>
{};


// If reversal is needed, perform it
template
<
    typename Geometry1, typename Geometry2,
    std::size_t DimensionCount,
    typename Tag1, typename Tag2
>
struct disjoint<Geometry1, Geometry2, DimensionCount, Tag1, Tag2, true>
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const& g1, Geometry2 const& g2, Strategy const& strategy)
    {
        return disjoint
            <
                Geometry2, Geometry1,
                DimensionCount,
                Tag2, Tag1
            >::apply(g2, g1, strategy);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DISPATCH_DISJOINT_HPP

/* disjoint.hpp
BPQC7Eyp85WbLc/OCp2pF1MnTgQbC8uqDw0HEEkCyYB3A/yZlliOA9sV5Vv3HwkW2iAXu3wrguIOWcjLlg1KQ9snW23VuKPEX6W/tDmdaXqtowPT5IPfbHEBawftwvK9tYC1zOG9cSXIeXenoherHaMiKoaxPY/D3xB2h7S/aPG+TEBQlI8t5Wz4w44ohXDnCwSKdlOTwNDZku86VBkYRGLjC0bckfFshCZHaBw8H6PFMZpt4wlbLGtppE+Dtaw7g8CU0cECjEFoIaEwHrR3eUzyDY1TiMR+jcEA/eKYiNM91WjgtuhARkNLi50N7zHlLi0inncpsjPD3zLzZbnXNwebuY//8xhCQC5tF2C5p/ZOuAUQWCtWYhtibANQOL/gJuVTHFtd2XzAoq4cvHLVlSAPfYCYZ+giRNY9dU0cZfAftvrhqB8ClyhAIGmdaAvI39YXuAj6Akrh8mpGbrDakgaanGcJFtoP+UKLSYInbC0jB+JqUAjSAJDDPIijQSFIE0AajTyMrYEhTAthjo0npWmvl2Z/vTQHz5Dm8BnSHK2X5ni9NI36M8RpNJ4hT6P5DGe1niFR+zkS7UuJsmBq5oLpIi/gBQ8mqFP1xb511Dw8Pj7OC3uRF/aCu3sJfj8Prwt+wR2yBH+ch9d1
*/