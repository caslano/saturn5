// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_POINT_TYPE_HPP
#define BOOST_GEOMETRY_CORE_POINT_TYPE_HPP


#include <boost/mpl/assert.hpp>
#include <boost/range/value_type.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/util/bare_type.hpp>

namespace boost { namespace geometry
{

namespace traits
{

/*!
\brief Traits class indicating the type of contained points
\ingroup traits
\par Geometries:
    - all geometries except point
\par Specializations should provide:
    - typedef P type (where P should fulfil the Point concept)
\tparam Geometry geometry
*/
template <typename Geometry>
struct point_type
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_POINT_TYPE, (types<Geometry>)
        );
};


} // namespace traits


#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

template <typename Tag, typename Geometry>
struct point_type
{
    // Default: call traits to get point type
    typedef typename boost::remove_const
        <
            typename traits::point_type<Geometry>::type
        >::type type;
};


// Specialization for point: the point itself
template <typename Point>
struct point_type<point_tag, Point>
{
    typedef Point type;
};


// Specializations for linestring/ring, via boost::range
template <typename Linestring>
struct point_type<linestring_tag, Linestring>
{
    typedef typename boost::range_value<Linestring>::type type;
};


template <typename Ring>
struct point_type<ring_tag, Ring>
{
    typedef typename boost::range_value<Ring>::type type;
};


// Specialization for polygon: the point-type is the point-type of its rings
template <typename Polygon>
struct point_type<polygon_tag, Polygon>
{
    typedef typename point_type
        <
            ring_tag,
            typename ring_type<polygon_tag, Polygon>::type
        >::type type;
};


template <typename MultiPoint>
struct point_type<multi_point_tag, MultiPoint>
{
    typedef typename boost::range_value
        <
            MultiPoint
        >::type type;
};


template <typename MultiLinestring>
struct point_type<multi_linestring_tag, MultiLinestring>
{
    typedef typename point_type
        <
            linestring_tag,
            typename boost::range_value<MultiLinestring>::type
        >::type type;
};


template <typename MultiPolygon>
struct point_type<multi_polygon_tag, MultiPolygon>
{
    typedef typename point_type
        <
            polygon_tag,
            typename boost::range_value<MultiPolygon>::type
        >::type type;
};


} // namespace core_dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
\brief \brief_meta{type, point_type, \meta_geometry_type}
\tparam Geometry \tparam_geometry
\ingroup core

\qbk{[include reference/core/point_type.qbk]}
*/
template <typename Geometry>
struct point_type
{
    typedef typename core_dispatch::point_type
        <
            typename tag<Geometry>::type,
            typename boost::geometry::util::bare_type<Geometry>::type
        >::type type;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_POINT_TYPE_HPP

/* point_type.hpp
182Bxzutu5USxvy7mpO6OJgULz+FfO1sNs7A3A77hHdY5TjgiEXFs/ZZy8F9f6wDbm8RINcWyLyl12hvqa2O7mu6NJIU30XYtsvwhRY4tTtV6DiHO8aBN+ulPYyz5tzghVxS3DWfFMM+LxGBEX9LXOdZzeJZueZgvz27XGQxX/bgj6fF/dCuYV5szj9LsAZxYeMrYEdNWO8YHkuKryNc1mmbsPhzMWMtYuxKm7gP8ndU7kWGjVH7H6wv8WucQ/rchfbX8lxuUvwN4dG31XJpWHS+tO75zPYG+3j/qbshe90zxjX7mHFz6tewLhJKi+aqcAbG/W2wphl1yLrnmsoQdjL8+qQ49oakOLBbl6EJM/kY+9lLfr/A2yf1+KTY+oSkeKrmo2EhPt372sWO6maxI7dJ7Ni7UezAOSXfQ7KPeLHn077YKr6I8dv7sVdz3Qid//Bb42DfU54FWoG+X1QPtrNDQbqVtelMv0Rn2XCeG+dP0Zud874pUTLPseW6xMLLk+Ker0iKZ/ayLiSfqx04xyz35a0n3KMQ3kh40pUNFuVD89Zo/8BHIB0BXn6cGDoq/7I+B6n9GuYmnw8fgnBgj9cvSIm0TMOCIxqcrd3xgqSoIkwQnNKMwPzvKNwcezWd2wjqmQT9P/dBdoieT6CdQfgA0TJ8760JtvuTSfENnY4NFqGnviD4CvDwcbXj85nrtaJ5XvcBnyrM74Rg/zXsdfbTSXHyM/DrqH8+7vIa9Ls7Cb7qc/B7hKN0rDCTR0NzddQ3QL8AuI2DNObR7bQ8M4G2euHDSfGQWfhdnY4Js/eN0PZ3/pbGZH6eCeG33z1ov29pbb9dKj9eD/wXe+cfZ9WYx/HnTNOYasqtppoSLtvSEm4JQ2EoTKSuSlq/Zqb50YymmWvunYotBiG7xSAVwiCEyiBExUWS3eIultayhg1ZrFkbBmHfzznfZ86duadJd/a/7b72s5/v5/nxOd/znOc859xzz+QFuXOQnOx/U4FcfT92UJvB4qNaPHf4xeXNfwff4MychL8D5p3VwHcd1HSwvdlLtS6T+Xdgi/mnrHifg1XgB84VMPxo16d1mTWgsxowIUsNGNqbfzOkT2OvWM9o95Av3/29hfe4OU79q1r/3pKhGrd1UOd+2kHVuf4JZRbvSnS1uns+k3XfTfO4Zp/NtZ2/cQvq7/v8jcD++ntzTOaJx7VJnv3u+t3crr/wGvlLWa5rv/g9nPZce43PgW1wW9dd8mu+h4ykqpXVqao8O26+epRb3TnXX0htTImpFt9d629IVX8FS+P77075bzL4HpKuBqzX/6ZNZ309Yn+778Qjw/k7Ytoq2jp/w0MZ7Vu3tQ7OUAdzT3hwEe9Vck99MHNK3q2MOudfR7azL+dglmJk3b/XbvFvNXVmzeIZV+Lf/MjfNvRS/R/z+NuGoe7flezsPcW2/hYo/nrW/L1cP1fgutU5srf9LCF0U6r6D/AdF/deIPWKeuVRb43srEby+2o24xfQ+TAm8q5T4hzO5Nlp1V7RAwIZKsA7DgO3duRvHvh9kv6dGW99X+U/N1WdAGrxd++Zu9plP4HFzXmphDKZC4keIL7MPU4TOE7B5uMUort7znTinIH57iHnjPu+4fxUdTzIHub6tyqT9257qoOrWr93m/ibyQGjUtWoInm3OTtVHQfqjHfHNO4d5J10r3oFt1mfslvl3uvaLr5HZnZUmZN53tMQd00blK4GsYb34/h2W9+Nceuq8vNS1XWgdLg7bq3LEuevvP9wcnqj8y+XqLh3MDLsv81rqElVv7kiVW20PeTvDrem6meGdvkp4F13m55l8R7uM4GuPBPI4JlAF77vo6tavlvQfF8=
*/