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
Qvjw1abPLHGLTEKp9JcEtJVfeGsZ5/FUbNh4hRjWpfmCVOSxV3nMsxxHbethmjXBKJlCi6LxK/+farzah98JOiI/G5uTIlW7MjzB5sxBxgyeP30AbUdeSHlylxidAY1Ii7idlWIZArn59RT833r01HA6vRk0xhOTPmYLrzRYlU83PrKTQx8FyC3XokDZ1G8rwy7vhpPy34Nh9hSQH03T43l5fk1u1FwinR1W7aoZeWUYZBv1wEcLenLGbmTOR2SRL5C8wVvWnWgDjPJQJFs82nYUT2ypNGf8YRydsTXkDkZ6YUBeVA70meJYZ6UvMjfdiK1oBOD1u3xeaoLkIZOZcMsHgKS63HeqXoGZLmZ4oPzbHkjkbk4FzYeM0Joe1mIZV1KTLBdtlW7BYWRMCMcOJhS8tZsXFREZyj+OXJinnXTAfjbqIw2qfsUiTLoPuBf1UhFLRL17TVMp3z/aswdWCyvPr568tFe+G/vzK9fkqGP+6gPvCcpBBlAHYHtjKSCOWl2Sgtmd08aOwTpyIGH87WConWDYz+vmXtkQf2ScUfP/UZKao93o/JlU0w==
*/