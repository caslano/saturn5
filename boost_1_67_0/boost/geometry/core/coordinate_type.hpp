// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_COORDINATE_TYPE_HPP
#define BOOST_GEOMETRY_CORE_COORDINATE_TYPE_HPP


#include <boost/mpl/assert.hpp>

#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/util/bare_type.hpp>
#include <boost/geometry/util/promote_floating_point.hpp>


namespace boost { namespace geometry
{

namespace traits
{

/*!
\brief Traits class which indicate the coordinate type (double,float,...) of a point
\ingroup traits
\par Geometries:
    - point
\par Specializations should provide:
    - typedef T type; (double,float,int,etc)
*/
template <typename Point, typename Enable = void>
struct coordinate_type
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_POINT_TYPE, (types<Point>)
        );
};

} // namespace traits

#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

template <typename GeometryTag, typename Geometry>
struct coordinate_type
{
    typedef typename point_type<GeometryTag, Geometry>::type point_type;

    // Call its own specialization on point-tag
    typedef typename coordinate_type<point_tag, point_type>::type type;
};

template <typename Point>
struct coordinate_type<point_tag, Point>
{
    typedef typename traits::coordinate_type
        <
            typename geometry::util::bare_type<Point>::type
        >::type type;
};


} // namespace core_dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
\brief \brief_meta{type, coordinate type (int\, float\, double\, etc), \meta_point_type}
\tparam Geometry \tparam_geometry
\ingroup core

\qbk{[include reference/core/coordinate_type.qbk]}
*/
template <typename Geometry>
struct coordinate_type
{
    typedef typename core_dispatch::coordinate_type
                <
                    typename tag<Geometry>::type,
                    typename geometry::util::bare_type<Geometry>::type
                >::type type;
};

template <typename Geometry>
struct fp_coordinate_type
{
    typedef typename promote_floating_point
        <
            typename coordinate_type<Geometry>::type
        >::type type;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_COORDINATE_TYPE_HPP

/* coordinate_type.hpp
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
*/