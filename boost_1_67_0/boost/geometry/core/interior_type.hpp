// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_CORE_INTERIOR_TYPE_HPP
#define BOOST_GEOMETRY_CORE_INTERIOR_TYPE_HPP


#include <boost/mpl/assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

namespace boost { namespace geometry
{

namespace traits
{

/*!
\brief Traits class indicating interior container type of a polygon
\details defines inner container type, so the container containing
        the interior rings
\ingroup traits
\par Geometries:
    - polygon
\par Specializations should provide:
    - typedef X type ( e.g. std::vector&lt;myring&lt;P&gt;&gt; )
\tparam Geometry geometry
*/
template <typename Geometry>
struct interior_const_type
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<Geometry>)
        );
};

template <typename Geometry>
struct interior_mutable_type
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<Geometry>)
        );
};


} // namespace traits




#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{


template <typename GeometryTag, typename Geometry>
struct interior_return_type
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<Geometry>)
        );
};


template <typename Polygon>
struct interior_return_type<polygon_tag, Polygon>
{
    typedef typename boost::remove_const<Polygon>::type nc_polygon_type;

    typedef typename boost::mpl::if_
        <
            boost::is_const<Polygon>,
            typename traits::interior_const_type<nc_polygon_type>::type,
            typename traits::interior_mutable_type<nc_polygon_type>::type
        >::type type;
};




template <typename GeometryTag, typename Geometry>
struct interior_type
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<Geometry>)
        );
};


template <typename Polygon>
struct interior_type<polygon_tag, Polygon>
{
    typedef typename boost::remove_reference
        <
            typename interior_return_type<polygon_tag, Polygon>::type
        >::type type;
};


} // namespace core_dispatch
#endif


/*!
\brief \brief_meta{type, interior_type (container type
    of inner rings), \meta_geometry_type}
\details Interior rings should be organized as a container
    (std::vector, std::deque, boost::array) with
    Boost.Range support. This metafunction defines the type
    of the container.
\tparam Geometry A type fullfilling the Polygon or MultiPolygon concept.
\ingroup core

\qbk{[include reference/core/interior_type.qbk]}
*/
template <typename Geometry>
struct interior_type
{
    typedef typename core_dispatch::interior_type
        <
            typename tag<Geometry>::type,
            Geometry
        >::type type;
};

template <typename Geometry>
struct interior_return_type
{
    typedef typename core_dispatch::interior_return_type
        <
            typename tag<Geometry>::type,
            Geometry
        >::type type;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_INTERIOR_TYPE_HPP

/* interior_type.hpp
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
*/