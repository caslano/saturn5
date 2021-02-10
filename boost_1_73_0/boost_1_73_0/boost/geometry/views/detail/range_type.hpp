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
ovxV0GYdjdsGlOy3BrTdiLeZ2Yhqb5Fbtnm3rne1a5nsR8keVAg73GSyeXVjZdf1vwJn+9SWdDrOlxR3Ir5DfWgx9XsWmyYTtoGcWKu7HjpMbyoRs9e94nLdCrqoo8dc4st04FFg+2yAAkcnXRtbFqFuNxnms/O7ZzFyjx36mr35il35D++HJel8KsL3i+SpkNoDXt3XZ2cnEUV7e9NBZm/HKW8183HoLOjWdJEcYR+dm4Ap18vE4xgvRdRHPXi8tMkPyD9GIUj58dBqGVgdCt3vs8J12NpdKMzW/Vu4XNx4DRGeSKqympFWI7qGvHYzUDFFi3J4O8z1gomlnCSNSuw4SUfpJXLc8OHRru54cN439ovwxAY9kuGgvN34EsfK+L1RK0WpOXvnT6i5zboKPLR7CMJUxmoBk81n4lWaZ7DmeFpeI4eiBbvpGE8bXZrIptLtxVEXoG6X04MxS2OVvWj1QtPd33LbDvkMtPk662sB7asFDU7q3jwX7+l9NTBu35SCJZgFbH6JDrGc0tSJrozireUsWWAUxtv4js1YmKfFjWL1iNsZnSOGiSTooCyjMews5SCVEFYkacg5pwDON6Eo5fFotFywItf+9Fg5LRpoQlnYmmRL7I/He8THQQ69fLIOIeD2Rw3JwAYd
*/