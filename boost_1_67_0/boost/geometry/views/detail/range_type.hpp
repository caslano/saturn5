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
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
*/