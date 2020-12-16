// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_POINT_ORDER_HPP
#define BOOST_GEOMETRY_CORE_POINT_ORDER_HPP


#include <boost/mpl/assert.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/util/bare_type.hpp>

namespace boost { namespace geometry
{

/*!
\brief Enumerates options for the order of points within polygons
\ingroup enum
\details The enumeration order_selector describes options for the order of
    points within a polygon. Polygons can be ordered either clockwise or
    counterclockwise. The specific order of a polygon type is defined by the
    point_order metafunction. The point_order metafunction defines a value,
    which is one of the values enumerated in the order_selector

\qbk{
[heading See also]
[link geometry.reference.core.point_order The point_order metafunction]
}
*/
enum order_selector
{
    /// Points are ordered clockwise
    clockwise = 1,
    /// Points are ordered counter clockwise
    counterclockwise = 2,
    /// Points might be stored in any order, algorithms will determine it on the
    /// fly (not yet supported)
    order_undetermined = 0
};

namespace traits
{

/*!
\brief Traits class indicating the order of contained points within a
    ring or (multi)polygon, clockwise, counter clockwise or not known.
\ingroup traits
\tparam Ring ring
*/
template <typename Ring>
struct point_order
{
    static const order_selector value = clockwise;
};


} // namespace traits


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace point_order
{

struct clockwise
{
    static const order_selector value = geometry::clockwise;
};


}} // namespace detail::point_order
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

template <typename Tag, typename Geometry>
struct point_order
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<Geometry>)
        );
};

template <typename Point>
struct point_order<point_tag, Point>
    : public detail::point_order::clockwise {};

template <typename Segment>
struct point_order<segment_tag, Segment>
    : public detail::point_order::clockwise {};


template <typename Box>
struct point_order<box_tag, Box>
    : public detail::point_order::clockwise {};

template <typename LineString>
struct point_order<linestring_tag, LineString>
    : public detail::point_order::clockwise {};


template <typename Ring>
struct point_order<ring_tag, Ring>
{
    static const order_selector value
        = geometry::traits::point_order<Ring>::value;
};

// Specialization for polygon: the order is the order of its rings
template <typename Polygon>
struct point_order<polygon_tag, Polygon>
{
    static const order_selector value = core_dispatch::point_order
        <
            ring_tag,
            typename ring_type<polygon_tag, Polygon>::type
        >::value ;
};

template <typename MultiPoint>
struct point_order<multi_point_tag, MultiPoint>
    : public detail::point_order::clockwise {};

template <typename MultiLinestring>
struct point_order<multi_linestring_tag, MultiLinestring>
    : public detail::point_order::clockwise {};


// Specialization for multi_polygon: the order is the order of its polygons
template <typename MultiPolygon>
struct point_order<multi_polygon_tag, MultiPolygon>
{
    static const order_selector value = core_dispatch::point_order
        <
            polygon_tag,
            typename boost::range_value<MultiPolygon>::type
        >::value ;
};

} // namespace core_dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
\brief \brief_meta{value, point order (clockwise\, counterclockwise),
    \meta_geometry_type}
\tparam Geometry \tparam_geometry
\ingroup core

\qbk{[include reference/core/point_order.qbk]}
*/
template <typename Geometry>
struct point_order
{
    static const order_selector value = core_dispatch::point_order
        <
            typename tag<Geometry>::type,
            typename util::bare_type<Geometry>::type
        >::value;
};

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_CORE_POINT_ORDER_HPP

/* point_order.hpp
MCE2PCghjvh8RQhWey9PQ37dy8cA+lPI+1HIvAqyNMEH9tw5IR6A8OkNRp0GTpi4UL5qjmnpXa87UP4wrzx/r4TYfCwhejZyGm0p0Sb9hg2n56ItOBGBOZPtYvJqsxjH3Nro5XbxYLXfZdbc7+KsxRro43nnDq+bqvHtKpTrSnH+bgnxLYRPg6feF9BBsB8dSIjvEJzzczVNsB0HE+JPWi4bLEpP+5cQkK4Af2FLm/S/yobT+p9JixmUuTnHX3/Pa3j9rbG9Ol5727EvIfYj/G2Tnz8TZtuTHRzHwu5nb58Qu++AstuseZgw29rtRfD/AkJV0wRgFj+7OH+p0hum9FB/3GxC3A3hymbDn8AeW6ppOa4g3CmEX2h5rLAgH6lr6Hdk3ULn/Oq5jtkVpfbhtgGea9ZzL26LcGEXLsreLXs7cHwd0lrzwEMT4m0IpZv4aUVg5JeicdkOllP9DKzTYw70rwhzJv0i4Pa+aAPj3q5U3faye1cL9NEl3Bp7LeruOYvD2fcz19/Hdq08A7ZXuzwOFBLiGQjDrqH3RcCvW3k8LC0ehvfuKvZYo1y8fdZONi2yeH8gcJ3AdQ7SHBOfoViBMxTtOEOB58HgGQq2cx6jtGGMIveMtdBeqsj4oEwyqLZCtuVDsIPzqGcIpS2GrwROWHEiBFuEX4wbN75a38l3lL3+AdrMZyXEbRDcm2kZgrCaY9Ae+zyK7gsHxyymT1gmSk9PiDc/A3M2Ot0ArN74fx7yrX02xvqaPgIz5InZh+G3RyV/XAHfKfs48y9JiI0vhS5uHmrnrThhwK5xHtFrK0fSYgT2cQfYyapBtQuQ/MpuzOE4t+e9Z8G9ehedBvxKYI1hOWwZd+iHxtvGHtu5lyVEy8sT4ha30HkLwq5hjpvzVn/eqE2WB9WluuvhcTqkdr0d89NtWDMMteuow3P4sE3np9Bn2urnMQIjX2WJ67xphXgTdHxv9IuOwR7ugT77oaHVYvXbm+a8snLu0Sbugb0YhzC/th/53AddY86O9mPV3QP/n7o3Mha/mXePzgs1PD4N7I1qDbYv5H9Xwf92wP/CD5dD/pfwKy3+uYE2z74Gp/3XTVvETbFGfVOke9PB1Qsd8ytmaZ06uB9Mt3NoNzqWJcVnEI7cyrCRRcC9tGu1J7TGhraJa3fNOXvaQwK90T6Ssi87xVf5ake+2gL5suukgbk2NUaKnsk63iKOX20R/WjP10FX2E85G9hPibpR+hHmGBEmtul6ZsKC9b6V6r25N8ftTYonI7xjm6FXK1wEYaSHtLjp86juzy0vpYeX9ZBsvE9iNfpoSXHmdknRtt3gbYWLCMzZuExs/CH2NcyjdzdMp8f03uXLK+gMzty2pEjuSIrx7Ub7AZyw4kQERraAfvX6Mq23BvrU7q6kuDfC5xFX66uNYJcQ5jVfCyzF+zzbonwQQjDaO7zB2S9wUm5++ZzeIU177L12p7NZ9qkWPJwvE85zzP0+IXr/kBAzOziN1pRolftKLDhnIi0mYAfr4S9Ce7UofwM/S4jfIcxSfJI3AnOm02KaeOj9XvpM124ByJx5pmvYMffW94jZXybEvX+VEJtu3WycJbotwV6DcBeCU9pWmElfd04NdQtzrvPyfI4+g9QhSndKitcgXPL4fr5FfB5+8Hloc45eXi7ahqA/WzzRosbriCPxAjQCccPxImchdnj7P1v9fZ5SN9uAI/xNMZ/1Q2q91D5Pb7/7rjaxCz5g+xXQ4WzLapRpe24F9LhGzJ1MihwOEdz/Nr5uwjCc9ZP+fQ38+2r4d7QDz9P+XaZzhGIZexJoX9EKyNku9xWRnKY+u3ta4RNdcTNnne1MB31Pqq6/s5U=
*/