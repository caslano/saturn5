// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_VIEWS_DETAIL_RANGE_TYPE_HPP
#define BOOST_GEOMETRY_VIEWS_DETAIL_RANGE_TYPE_HPP


#include <boost/mpl/assert.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/views/box_view.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Geometry,
          typename Tag = typename tag<Geometry>::type>
struct range_type
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_OR_NOT_YET_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<Geometry>)
        );
};


template <typename Geometry>
struct range_type<Geometry, ring_tag>
{
    typedef Geometry type;
};


template <typename Geometry>
struct range_type<Geometry, linestring_tag>
{
    typedef Geometry type;
};


template <typename Geometry>
struct range_type<Geometry, polygon_tag>
{
    typedef typename ring_type<Geometry>::type type;
};


template <typename Geometry>
struct range_type<Geometry, box_tag>
{
    typedef box_view<Geometry> type;
};


// multi-point acts itself as a range
template <typename Geometry>
struct range_type<Geometry, multi_point_tag>
{
    typedef Geometry type;
};


template <typename Geometry>
struct range_type<Geometry, multi_linestring_tag>
{
    typedef typename boost::range_value<Geometry>::type type;
};


template <typename Geometry>
struct range_type<Geometry, multi_polygon_tag>
{
    // Call its single-version
    typedef typename dispatch::range_type
        <
            typename boost::range_value<Geometry>::type
        >::type type;
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

// Will probably be replaced by the more generic "view_as", therefore in detail
namespace detail
{


/*!
\brief Meta-function defining a type which is a boost-range.
\details
- For linestrings and rings, it defines the type itself.
- For polygons it defines the ring type.
- For multi-points, it defines the type itself
- For multi-polygons and multi-linestrings, it defines the single-version
    (so in the end the linestring and ring-type-of-multi-polygon)
\ingroup iterators
*/
template <typename Geometry>
struct range_type
{
    typedef typename dispatch::range_type
        <
            Geometry
        >::type type;
};

}

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_VIEWS_DETAIL_RANGE_TYPE_HPP

/* range_type.hpp
Yb84X9RgcV2531jqyCkDQJ5biH+cKdaf1p+PMuO8cnx/XHF5P08mKFjVi0jSYKxUCbkBXJUMYt7PvF7uRD9todUxp1m320HYJPN+brq5FO2EHjfnNFbjluOOOixtdXO7O77jYrjabqid4Ib7MO82+MV+a33dOWTnLQHHbyCU23eA+c8Jj4gfQg4p8E/xrsa1xyqgc9xDSOT44qvTWtxLcHGnwgIgfGmnxJhx2ywyip3qIVN/id/rNk/98TNRTD6Kr+QINOUn5KSyg9yAM7ZJMrvYV2w954N9sviOU+yIi8jVr9iVAm6HPZeJIe/nnYYfK4X2J+d3j9xw3w4njTBMVkXJS1FeTCmNTpkoSNMqylMCgzkKjuM7Bw59T2KUIPs3dFz+RzPI5Gkn5qTBDi+hwjShvXTX8RbSpoA364WPXrui6Yp+tBneIzhuOJy4J1YHqtg4ubKMJ7JjVVYuHn851Y20g3JUnmuvd2bRmIdXI5777PoEgNJuTR0xIfRDSy71O1geGlc5psXLFB7JEpOtNU4ARUjMVdd4kXc9pHvdDPTVv8SPwuGRt20SkQCfmUU98WS9ddOW0QP0+W+a5eR6hum2E3QdtvVg23MBrSeH9v2Evz14SQLVcKh4uH/eJadbXdsCs4p9GtQ4RKBbkAfHIZxOKn/vEy3Wy/29+bc7k+zDEbeej3uPe7JcwAP2e0forn+Td6wY9pHW3k/8
*/