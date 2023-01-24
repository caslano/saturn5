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
Xy1EhZO1O1y8dcX8iZZBag8oeajbQsTA09/ho3zI5VsP7ESGBR0ITqUm3TXdXkT11V/Ob6qDDfgzXCAHjsmneebcpWXzvbyQp91C4ln579H3XjFu/omddPW3//zRBzcDPy6xyS952NlombPv9OlwdwLCgj4XTNWEsCo5zq2+q49iPfMW7DaobrBq6pJv+XzvZvTk2b263Gs92Mis7bOsq6wRZFvipPHao7jNBt4v5Kd4BVTJPWqKf24Y48K1Z/IIGwp5QRT0yvXd6hXeBKXnT+pGSCz+U6VN2SFJMBJychKAw9YvY50QkUMdDEvPGJ4iKMd3f9pLbBSn1M/dYXpu4n/sHDujHb+ctpNm7url6HPa9fX+/rx/wfnZamzsOxs5srryMqcP1Kv6khU0qN8rycbFziCrb+8+iHkGlL0ZuZN1t9YMsND6tSsTpCMWui5msz5igC0DfyrW/Yh83gNys+xaPC8SVq+TG70a0uRbikskTiVwZjviNSVaCI3PYlc8f43Wb8bMyoyKZkRQh1nE/xjRZHpR5yLWqJlBKhq47vpG1FNmwEDss2+A8ehwbQImNUDM2KHxkSfZxbgdJzep6MsP3G1BmyPMYkGi+Mlkf7yy9DPaVr6u17pY8RHgZi2bBaUHkBtf7UV0aLh2RJispRNuYt0CXD8DM+Zsk7BhF7k7adGezYdq+mb5WLWO2CgnYyPrJcGlAnqqIjVR
*/