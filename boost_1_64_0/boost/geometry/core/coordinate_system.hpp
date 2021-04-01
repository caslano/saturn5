// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_COORDINATE_SYSTEM_HPP
#define BOOST_GEOMETRY_CORE_COORDINATE_SYSTEM_HPP


#include <boost/mpl/assert.hpp>

#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/util/bare_type.hpp>


namespace boost { namespace geometry
{


namespace traits
{

/*!
\brief Traits class defining the coordinate system of a point, important for strategy selection
\ingroup traits
\par Geometries:
    - point
\par Specializations should provide:
    - typedef CS type; (cs::cartesian, cs::spherical, etc)
*/
template <typename Point, typename Enable = void>
struct coordinate_system
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
    template <typename GeometryTag, typename G>
    struct coordinate_system
    {
        typedef typename point_type<GeometryTag, G>::type P;

        // Call its own specialization on point-tag
        typedef typename coordinate_system<point_tag, P>::type type;
    };


    template <typename Point>
    struct coordinate_system<point_tag, Point>
    {
        typedef typename traits::coordinate_system
            <
                typename geometry::util::bare_type<Point>::type
            >::type type;
    };


} // namespace core_dispatch
#endif


/*!
\brief \brief_meta{type, coordinate system (cartesian\, spherical\, etc), \meta_point_type}
\tparam Geometry \tparam_geometry
\ingroup core

\qbk{[include reference/core/coordinate_system.qbk]}
*/
template <typename Geometry>
struct coordinate_system
{
    typedef typename core_dispatch::coordinate_system
        <
            typename tag<Geometry>::type,
            typename geometry::util::bare_type<Geometry>::type
        >::type type;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_COORDINATE_SYSTEM_HPP

/* coordinate_system.hpp
dc1sW05MsX9y/kiLZtEcMLOIUqgye6eL+ZvO+NVBkFKhCbd6075y+LMOMk9tG7DSNijwFUVGPrLXoCaKcWwrDTPVEOPW36eFz8I5Z0alAwQIgz0Iwae4NhXqgcAQ4IyFyg78YOSml0dGY6gAF9Gah6WHXU2pBMBD75al8WliozfKclA/q7gWBTf36OV6ZKzlfRFMQdMAY6rv9h2VDKcT7zMxZ6AEz4mSgtgijGZn9sr4LDwU7RfzHvJg/QqfZ5VBvN7uZECZ880mBkGw/+7Ck6oqsEaydy86uT0R9Xan0d7qwIzTYWRPp0OQXTV4QKMBOHq81PYmc1UsT+dgD9iB2rovQ/7ECSLMnkwbN2ECznSU35oH+ayNrHRLXBA/UOXRo5Ps2oNrxLTFHi64j++wtH6j3VjaZ4RKcgYbzuDQT8HKd+z0RlMlVoocRS3RGed8AG7qssZIqt2U1MZzBVpbzJ1bzH04MFbqPEU6A/FRJH8NM5IQEeOnil/8rU2LiKdOxjSRSxa7rSUShnhjMB954u0DT27Vso3u3UZms5kmujxi1faC3o/mHKtSfw==
*/